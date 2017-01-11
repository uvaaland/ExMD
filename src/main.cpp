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
#include "drag.h"
#include "boundary.h"
#include "write.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  /* Simulation parameters */
  // int nsteps = 100;
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 250;
  double G = pow(10,-5);      //6.67408 * pow(10, -11);  // gravitational constant
  double gamma = 50;

  /* Make a particles object */
  const int kNparticles = 9;
  double positions[kNparticles][DIM];
  double velocites[kNparticles][DIM];
  double masses[kNparticles];
  double radii[kNparticles];


  // Define attributes of the center particle 
  radii[0] = 10;
  masses[0] = 1 * pow(10,15);
  for (int i = 0; i < DIM; i++) {
      positions[0][i] = 0;
      velocites[0][i] = 0;
  }
  
  // Define attributes for the orbiting particles
  for(int k=1; k<kNparticles; k++) {
      radii[k] = 1;
      masses[k] = 1;
      for (int i = 0; i < DIM-1; i++) {
          positions[k][i+1] = 0;
          velocites[k][i] = 0;
      }
      positions[k][0] = 5*k + 10;
      double GM_r = (G*masses[0]) / (positions[k][0] - positions[0][0]);
      velocites[k][2] = sqrt(GM_r);
  }
  
  Particles *particles;
  particles = new Particles(kNparticles, positions, \
          velocites, masses, radii);


  /* Make force object (depending on user input) UPDATE THIS */
  Force *gravity = new Gravity(G);
  Force *drag = new Drag(gamma);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);
  physics->AddForce(drag);


  /* Make a boundary object */
  Boundary boundary = { reflecting, {{-100, 100}, {-100, 100}, {-100, 100}} };

  /* Make a simulation object */
  double dt = 0.0001;
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
