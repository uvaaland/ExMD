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

/* MD header files */
#include "simulation.h"
#include "particles.h"
#include "physics.h"

int main() {
  std::cout << "working\n";

#define DIM 3

  /* Make a particles object */
  std::string filename =
      "https://github.com/APC524/ExMD/blob/master/test/data.txt";
  Particles *particles;
  particles = new Particles(filename, 0);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, particles->nparticles, DIM,
                              particles, physics);

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
