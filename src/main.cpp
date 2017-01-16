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

  /* Simulation parameters */
  int nsteps = 10;
  double G = pow(10, -8);  // 6.67408 * pow(10, -11);  // gravitational constant
  double gamma = 0;
  double beta = 1;
  const int kNparticles = 149;

  ParseParams();

  /* Make a particles object */
  double positions[kNparticles][DIM];
  double velocites[kNparticles][DIM];
  double masses[kNparticles];
  double radii[kNparticles];

  ParseParticles(full_infile, positions, velocites, masses, radii);

  Particles *particles;
  particles = new Particles(kNparticles, positions, \
          velocites, masses, radii);


  /* Make force object */
  Force *gravity = new Gravity(G);
//  Force *drag = new Drag(gamma);
//  Force *flocking = new Flocking(beta);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);
//  physics->AddForce(drag);
//  physics->AddForce(flocking);

  /* Make a boundary object */
  Boundary boundary = { none, {{-100, 100}, {-100, 100}, {-100, 100}} };

  /* Add boundary to physics */
  physics->AddBoundary(&boundary);

  /* Make a simulation object */
  double dt = 0.01;


  Simulation *simulation;
  simulation = new Simulation(dt, kNparticles, DIM, checkNaN, \
          particles, physics);

  /* Write simulation parameters to file */
  std::string filename = "exmd";
  WriteParametersCSV(nsteps, kNparticles, &boundary, filename);

  printf("Pre-processing finished!\n");

  /* PROCESSING */

  printf("Starting simulation...\n");

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
      WriteParticlesCSV(particles, kNparticles, nt, filename);
      simulation->Step();
      printf("[%d/%d] Simulation iteration done!\n", nt+1, nsteps);
  }

  printf("Simulation finished!\n");
  printf("Program ends...\n");

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;

  return EXIT_SUCCESS;
}
