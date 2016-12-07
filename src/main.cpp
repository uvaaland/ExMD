#include "simulation.h"
#include <iostream>
#include "particles.h"
#include "physics.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  // Make a particles object
  int nparticles = 2;
  double positions[2][DIM] = {{-10, 0, 0}, {10, 0, 0}};
  double velocites[2][DIM] = {{1, 0, 0}, {-1, 0, 0}};
  double masses[DIM] = {1, 1, 1};
  double radii[DIM] = {1, 1, 1};

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
