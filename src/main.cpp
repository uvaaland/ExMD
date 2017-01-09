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
#include "boundary.h"
#include "write.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  /* Simulation parameters */
  // int nsteps = 100;
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 70;
  /* Make a particles object */
  const int nparticles = 4;
  double positions[nparticles][DIM]; //= {{10, 0, 0}, {-10, 0, 0}};
  double velocites[nparticles][DIM]; //= {{-1, 0, 0}, {1, 0, 0}};
  double masses[nparticles];// = {1, 1, 1, 1, 1 ,1, 1,1};
  double radii[nparticles]; // = {1, 1, 1, 1};

  int half = nparticles/2;

  for (int i = 0; i < nparticles; i++) {
    if (i < half) {
      positions[i][0] = 10;
      velocites[i][0] = -1;
    }
    else {
      positions[i][0] = -10;
      velocites[i][0] = 1;
    }

    positions[i][1] = 2*(i % half); // 3 *
    positions[i][2] = 0;
    velocites[i][1] = 0;
    velocites[i][2] = 0;

    masses[i] = 1;
    radii[i] = 1;

//    std::cout << positions[i][0] << ", " << positions[i][1] << ", " << positions[i][2] << std::endl;
//    std::cout << velocites[i][0] << ", " << velocites[i][1] << ", " << velocites[i][2] << std::endl;
//    std::cout << masses[i] << ", " << radii[i] << std::endl;
  }


  Particles *particles;
  particles = new Particles(nparticles, positions, \
          velocites, masses, radii);

  for (int i = 0; i < nparticles; i++) {
//    std::cout << particles->p[i][0] << ", " << particles->p[i][1] << ", " << particles->p[i][2] << std::endl;
//    std::cout << particles->v[i][0] << ", " << particles->v[i][1] << ", " << particles->v[i][2] << std::endl;
//    std::cout << particles->mass[i] << ", " << particles->radius[i] << std::endl;
  }


  /* Make force object (depending on user input) UPDATE THIS */
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);

  /* Make a boundary object */
  Boundary boundary = { reflecting, {{-100, 100}, {-100, 100}, {-100, 100}} };

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;
  
  std::cout << "BEFORE" << std::endl;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, nparticles, DIM, checkNaN, \
          particles, physics, &boundary);
  
  std::cout << "AFTER" << std::endl;

  WriteParametersCSV(nsteps, nparticles);

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
      WriteParticlesCSV(particles, nparticles, nt);
      simulation->Step();
  }

  printf("Simulation finished!\n");

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
