/** @file   simulation.cpp 
 *  @brief  Implementation of the simulation class
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-04
 *  @bug    No known bugs
 */ 

/* -- Includes -- */
#include "simulation.h"
#include <string>           /* for WriteOutput */
#include <stdio.h>          /* for WriteOutput */
#include <vector>           /* for position, force vector handling */

/* -- Definitions -- */

Simulation::Simulation(double dt, int output_period, int nparticles, int dim)
    : dt_(dt),
      output_period_(output_period),
      nparticles_(nparticles),
      dim_(dim) {
      int counter_ = 0;
      double next_positions_[nparticles][dim];
      double next_velocities_[nparticles][dim];
      printf("Simulation object: successful construction\n");
      }


Simulation::~Simulation() {
    // Call destructors for the particles, kdtree, and physics objects
}


void Simulation::Step() {
    printf("Execution of simulation step\n");
        // std::vector<double> force(dim);
        CalculateForce();
        NextVelocities();
        NextPositions();
        // Physics.Collision
        // Physics.BoundaryCheck
        PositionUpdate();
        VelocityUpdate();
        // KDTreeUpdate - not for prototype
}


int Simulation::CheckParticles() {
    // Check to see if any NaNs in particle positions or velocities
    // Yes - return 1;
    // No - return 0;
    return 0;
}


void Simulation::WriteOutput(std::string filename) {
    // Write output to file
}


void Simulation::CalculateForce() {
    printf("Calculate Force\n");
    // Calculate the total force on a particle and store in force
}


void Simulation::NextVelocities() {
    printf("Next velocities\n");
}


void Simulation::NextPositions() {
    printf("Next positions\n");
}


void Simulation::PositionUpdate() {
    printf("Position update\n");
}


void Simulation::VelocityUpdate() {
    printf("Velocity update\n");
}
