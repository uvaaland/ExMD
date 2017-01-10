/** @file   main.cpp
 *  @brief  Main driving program for ExMD simlation
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-28
 *  @bug    No known bugs
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
#include "boundary.h"
#include "write.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  /* Simulation parameters */
  // int nsteps = 100;
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 100;
  /* Make a particles object */
  const int kNparticles = 4;
  double positions[kNparticles][DIM];
  double velocites[kNparticles][DIM];
  double masses[kNparticles];
  double radii[kNparticles];

  int half = kNparticles/2;

  for (int i = 0; i < kNparticles; i++) {
    if (i < half) {
      positions[i][0] = 10;
      velocites[i][0] = -1;
    } else {
      positions[i][0] = -10;
      velocites[i][0] = 1;
    }

    positions[i][1] = 2*(i % half);
    positions[i][2] = 0;
    velocites[i][1] = 0;
    velocites[i][2] = 0;

    masses[i] = 1;
    radii[i] = 1;
  }

  velocites[0][1]=-1;
  velocites[2][1]=-1;
  velocites[1][1]=1;
  velocites[3][1]=1;

  Particles *particles;
  particles = new Particles(kNparticles, positions, \
          velocites, masses, radii);


  /* Make force object (depending on user input) UPDATE THIS */
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);

  Force *random_force = new Random_Force();

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(random_force);

  /* Make a boundary object */
  Boundary boundary = { none, {{-12, 12}, {-10, 12}, {-12, 12}} };

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, kNparticles, DIM, checkNaN, \
          particles, physics, &boundary);

  WriteParametersCSV(nsteps, kNparticles);

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
      WriteParticlesCSV(particles, kNparticles, nt);
      simulation->Step();
  }

  printf("Simulation finished!\n");

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
