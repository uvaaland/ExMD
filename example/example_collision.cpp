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

int main() {
  #define DIM 3

  printf("Starting pre-processing...\n");

  /* Simulation parameters */
  // int nsteps = 100;
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 250;
  double G = 0;//6.67408 * pow(10, -11);  // gravitational constant

  /* Make a particles object */
  const int kNparticles = 64;
  double positions[kNparticles][DIM];
  double velocites[kNparticles][DIM];
  double masses[kNparticles];
  double radii[kNparticles];
  
  std::string infile = "../../example/files/input_collision.csv";
  ParseParticles(infile, positions, velocites, masses, radii);

  Particles *particles;
  particles = new Particles(kNparticles, positions, \
          velocites, masses, radii);


  /* Make force object */
  Force *gravity = new Gravity(G);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);

  /* Make a boundary object */
  Boundary boundary = { reflecting, {{-20, 20}, {-20, 20}, {-20, 20}} };

  /* Add boundary to physics */
  physics->AddBoundary(&boundary);

  /* Make a simulation object */
  double dt = 0.5;

  Simulation *simulation;
  simulation = new Simulation(dt, kNparticles, DIM, checkNaN, \
          particles, physics);

  /* Write simulation parameters to file */
  std::string filename = "collision";
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

  return 0;
}
