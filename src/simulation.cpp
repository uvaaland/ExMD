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

Simulation::Simulation(double dt, int output_period, int nparticles, int dim, \
        bool checkNaN, Particles *particles, Physics *physics, \
        Boundary *boundary)
    : dt_(dt),
      output_period_(output_period),
      nparticles_(nparticles),
      dim_(dim),
      checkNaN_(checkNaN),
      particles_(particles),
      physics_(physics),
      boundary_(boundary) {
      counter_ = 0;
      next_positions_ = new double[nparticles_][3];
      next_velocities_ = new double[nparticles_][3];
      accelerations_ = new double[nparticles_][3];
      distances_ = new Distance(particles_);

      printf("counter = %d\n", counter_);
      printf("Simulation object: successful construction\n");
      }


Simulation::~Simulation() {
    delete [] accelerations_;
    delete [] next_positions_;
    delete [] next_velocities_;
    // Call destructors for the particles, kdtree, and physics objects
}


void Simulation::Step() {
    printf("Execution of simulation step\n");
    if (checkNaN_) {
        CheckParticles();
    }
    // std::vector<double> force(dim);
    // Example of how to access elements of boundary
    // printf("Value of boundary type, %d, and first element of limits, %f\n", \
            // boundary_->type, boundary_->limits[2][0]);
    // need to update distances in distance object before computing forces
    physics_->ComputeAccelerations(*particles_, *distances_, \
       accelerations_);
    NextVelocities();
    NextPositions();

    physics_->ComputeCollisions(*particles_, next_positions_, \
            next_velocities_);
    // physics_->BoundaryCheck(boundarytype_, geometry_, *particles_, \
       //  next_positions_, next_velocities_);

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
    printf("Start calculate accelerations\n");
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            accelerations_[0][0] = 0.0;
        }
    }
    printf("Calculate Accelerations complete\n");
    // Calculate the total acceleration of each particle
}


void Simulation::NextVelocities() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            next_velocities_[i][j] = particles_->v[i][j] + \
                                     dt_ * accelerations_[i][j];
        }
    }
    printf("Next velocities complete\n");
}


void Simulation::NextPositions() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            next_positions_[i][j] = particles_->p[i][j] + \
                                     dt_ * next_velocities_[i][j];
        }
    }
    printf("Next positions complete\n");
}


void Simulation::PositionUpdate() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            particles_->p[i][j] = next_positions_[i][j];
        }
    }
    printf("Position update complete\n");
}


void Simulation::VelocityUpdate() {
    for (int i = 0; i < nparticles_; i++) {
        for (int j = 0; j < dim_; j++) {
            particles_->v[i][j] = next_velocities_[i][j];
        }
    }
    printf("Velocity update complete\n");
}
