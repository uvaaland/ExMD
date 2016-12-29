#include "simulation.h"
#include <iostream>
#include "particles.h"
#include "physics.h"

int main() {
  std::cout << "working\n";

#define DIM 3

  // Make a particles object
  int nparticles = 2;

  std::string filename =
      "https://github.com/APC524/ExMD/blob/master/test/data.txt";
  Particles* particles;
  particles = new Particles(filename, 0);

  // Make a physics object
  Physics* physics;
  physics = new Physics();

  // Make a simulation object
  double dt = 0.5;
  int output_period = 1;

  Simulation* simulation;
  simulation =
      new Simulation(dt, output_period, nparticles, DIM, particles, physics);

  // simulation->SetParametersHDF5();
  for (int i = 0; i < 1; i++) {
    simulation->Step();
  }

  printf("Simulation finished!\n");

  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
