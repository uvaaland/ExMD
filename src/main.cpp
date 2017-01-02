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

int main() {
  std::cout << "working\n";

  #define DIM 3

  /* Make a particles object */
  int nparticles = 2;
  double positions[2][DIM] = {{-10, 0, 0}, {10, 0, 0}};
  double velocites[2][DIM] = {{1, 0, 0}, {-1, 0, 0}};
  double masses[DIM] = {1, 1, 1};
  double radii[DIM] = {1, 1, 1};

  Particles *particles;
  particles = new Particles(nparticles, positions, \
          velocites, masses, radii);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Make force object (depending on user input) UPDATE THIS */
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *force = new Gravity(G);

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, nparticles, DIM, \
          particles, physics, force);

  /* Step through time */
  simulation->SetParametersHDF5();
  for (int i = 0; i < 20; i++) {
      simulation->Step();
  }

  printf("Simulation finished!\n");

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
