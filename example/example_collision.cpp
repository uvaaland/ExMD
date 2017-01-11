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
#define DIM 3

  /* Simulation parameters */
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 70;
  /* Make a particles object */
  int kNparticles = 3;
  std::string filenameInput =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/example/"
      "data_example.txt";
  Particles *particles = new Particles(filenameInput, 0);

  /* Make force object (depending on user input) UPDATE THIS */
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);

  /* Make a boundary object */
  Boundary boundary = {reflecting, {{-100, 100}, {-100, 100}, {-100, 100}}};

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, kNparticles, DIM, checkNaN,
                              particles, physics, &boundary);

  /* Write simulation parameters to file */
  std::string filename = "collision";
  WriteParametersCSV(nsteps, kNparticles, filename);

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
    WriteParticlesCSV(particles, kNparticles, nt, filename);
    simulation->Step();
  }

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete simulation;

  return 0;
}
