/** @file   simulation.cpp
 *  @brief  Implementation of the simulation class
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-04
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "simulation.h"
#include "force.h"
#include "distance.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>


/* -- Definitions -- */

Simulation::Simulation(double dt, int nparticles, int dim, \
        bool checkNaN, Particles *particles, Physics *physics)
    : dt_(dt),
      nparticles_(nparticles),
      dim_(dim),
      checkNaN_(checkNaN),
      particles_(particles),
      physics_(physics) {
      counter_ = 0;
      next_positions_ = new double[nparticles_][3];
      next_velocities_ = new double[nparticles_][3];
      accelerations_ = new double[nparticles_][3];
      distances_ = new Distance(particles_);

//      printf("counter = %d\n", counter_);
//      printf("Simulation object: successful construction\n");
      }


Simulation::~Simulation() {
    delete [] accelerations_;
    delete [] next_positions_;
    delete [] next_velocities_;
    // Call destructors for the particles, kdtree, and physics objects
}


void Simulation::Step() {
//    printf("Execution of simulation step\n");
    if (checkNaN_) {
        CheckParticles();
    }
    distances_->updateDistances();
    physics_->ComputeAccelerations(*particles_, *distances_, \
       accelerations_);
    NextVelocities();
    NextPositions();

    int maxcounts = 100;
    int counter = 0;
    int particlecollisions = 0;  // checks if no particle collisions occurred
    int boundarycheck = 0;       // checks if boundary conditions are satisfied
    while (!(particlecollisions && boundarycheck) && counter < maxcounts) {
      particlecollisions = physics_->ComputeCollisions(*particles_, \
         next_positions_, next_velocities_);
      boundarycheck = physics_->BoundaryCheck(*particles_, next_positions_, \
         next_velocities_);
      counter++;
    }

    PositionUpdate();
    VelocityUpdate();
}


int Simulation::CheckParticles() {
    // Check to see if any NaNs in particle positions or velocities
    // Yes - return 1;
    // No - return 0;
    char buffer[50];
    for (int i=0; i < nparticles_; ++i) {
        for (int j=0; j < 3; ++j) {
            if (isnan(particles_->p[i][j])) {
                snprintf(buffer, sizeof(buffer), \
                        "NAN in particle positions\n");
                std::cerr << buffer << std::endl;
            }
            if (isnan(particles_->v[i][j])) {
                snprintf(buffer, sizeof(buffer), \
                        "NAN in particle velocities\n");
                std::cerr << buffer << std::endl;
            }
        }
    }
    return 0;
}


void Simulation::CalculateAccelerations() {
//    printf("Start calculate accelerations\n");
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            accelerations_[0][0] = 0.0;
        }
    }
//    printf("Calculate Accelerations complete\n");
    // Calculate the total acceleration of each particle
}


void Simulation::NextVelocities() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            next_velocities_[i][j] = particles_->v[i][j] + \
                                     dt_ * accelerations_[i][j];
        }
    }
//    printf("Next velocities complete\n");
}


void Simulation::NextPositions() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            next_positions_[i][j] = particles_->p[i][j] + \
                                     dt_ * next_velocities_[i][j];
        }
    }
//    printf("Next positions complete\n");
}


void Simulation::PositionUpdate() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            particles_->p[i][j] = next_positions_[i][j];
        }
    }
//    printf("Position update complete\n");
}


void Simulation::VelocityUpdate() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            particles_->v[i][j] = next_velocities_[i][j];
        }
    }
//    printf("Velocity update complete\n");
}
