/** @file   main.cpp
 *  @brief  Main driving program for ExMD simlation
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-28
 *  @bug    Does not support when velocities are too large for a given time step
 *  @bug    Does not support only 1 particle
 */

/* -- Includes -- */

/* libc includes */
#include <iostream>
#include <math.h>
#include <stdlib.h>

/* MD header files */
#include "simulation.h"
#include "particles.h"
#include "physics.h"
#include "force.h"
#include "gravity.h"
#include "flocking.h"
#include "random_force.h"
#include "drag.h"
#include "boundary.h"
#include "write.h"
#include "parse.h"

int main(int argc, char *argv[]) {
  #define DIM 3

  if (argc != 2) {
    printf("Usage: ./exmd <particles_file>\n");
    exit(EXIT_FAILURE);
  }


  /* PRE-PROCESSING */


  printf("Starting pre-processing...\n");

  /* Simulation parameters */
  bool checkNaN = false;
  std::string infile = argv[1];
  std::string full_infile = "../../input/" + infile + ".csv";

  // Create parameter structure
  Parameters params;

  // Read parameters from file
  ParseParams(&params);

  // Unpack parameters
  int nparticles = params.nparticles;
  int nsteps = params.nsteps;
  double dt = params.dt;

  // Gravity parameters
  bool include_gravity = params.include_gravity;
  double G = params.G;

  // Drag parameters
  bool include_drag = params.include_drag;
  double gamma = params.gamma;

  // Flocking parameters
  bool include_flocking = params.include_flocking;
  double beta = params.beta;

  // Boundary
  Boundary boundary = params.boundary;


  // Allocating arrays for particle attributes
  double (*positions)[DIM];
  positions = new double[nparticles][DIM];

  double (*velocities)[DIM];
  velocities = new double[nparticles][DIM];

  double *masses;
  masses = new double[nparticles];

  double *radii;
  radii = new double[nparticles];


  // Read particles
  ParseParticles(nparticles, full_infile, positions, velocities, masses, radii);

  Particles *particles;
  particles = new Particles(nparticles, positions, \
          velocities, masses, radii);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();


  // Add forces
  if (include_gravity) {
    Force *gravity = new Gravity(G);
    physics->AddForce(gravity);
    std::cout << "Gravity on" << std::endl;
  }

  if (include_drag) {
    Force *drag = new Drag(gamma);
    physics->AddForce(drag);
    std::cout << "Drag on" << std::endl;
  }

  if (include_flocking) {
    Force *flocking = new Flocking(beta);
    physics->AddForce(flocking);
    std::cout << "Flocking on" << std::endl;
  }


  /* Add boundary to physics */
  physics->AddBoundary(&boundary);


  /* Make a simulation object */
  Simulation *simulation;
  simulation = new Simulation(dt, nparticles, DIM, checkNaN, \
          particles, physics);

  /* Write simulation parameters to file */
  std::string filename = "exmd";
  WriteParametersCSV(nsteps, nparticles, &boundary, filename);

  printf("Pre-processing finished!\n");


  /* PROCESSING */


  printf("Starting simulation...\n");

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
      WriteParticlesCSV(particles, nparticles, nt, filename);
      simulation->Step();
      printf("[%d/%d] Simulation iteration done!\n", nt+1, nsteps);
  }

  printf("Simulation finished!\n");
  printf("Program ends...\n");


  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;


  delete [] positions;
  delete [] velocities;
  delete [] masses;
  delete [] radii;
  return EXIT_SUCCESS;
}
