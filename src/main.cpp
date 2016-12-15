#include <iostream>
#include <fstream>
#include <array>
#include "simulation.h"
#include <iostream>
#include "particles.h"
#include "physics.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  // Make a particles object
  std::string filename = "data.txt";
  Particles *particles;
  particles = new Particles(filename, 0);

  Particles *particles;
  particles = new Particles(nparticles, positions, \
          velocites, masses, radii);

  // Make a physics object
  Physics *physics;
  physics = new Physics();

  // Make a simulation object
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, nparticles, DIM, \
          particles, physics);

  for (int i = 0; i < 20; i++) {
      simulation->Step();
  }

  printf("Simulation finished!\n");

  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
