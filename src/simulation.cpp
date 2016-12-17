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
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>


/* -- Definitions -- */

Simulation::Simulation(double dt, int output_period, int nparticles, int dim, \
        Particles *particles, Physics *physics)
    : dt_(dt),
      output_period_(output_period),
      nparticles_(nparticles),
      dim_(dim),
      particles_(particles),
      physics_(physics) {
      counter_ = 0;
      next_positions_ = new double[nparticles_][3];
      next_velocities_ = new double[nparticles_][3];
      accelerations_ = new double[nparticles_][3];

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
    // std::vector<double> force(dim);
    CalculateAccelerations();
    NextVelocities();
    NextPositions();
    physics_->Collisions(nparticles_, *particles_, next_positions_, \
            next_velocities_);
    // Physics.BoundaryCheck
    PositionUpdate();
    VelocityUpdate();
    printf("counter = %d\n", counter_);
    std::string filename = std::to_string(counter_);
    filename = "../output/csv/vis.csv." + filename;
    WriteOutput(filename);
    counter_ += 1.0;
    printf("counter = %d\n", counter_);
    // KDTreeUpdate - not for prototype
    printf("Execution of simulation step\n");
}


int Simulation::CheckParticles() {
    // Check to see if any NaNs in particle positions or velocities
    // Yes - return 1;
    // No - return 0;
    return 0;
}


void Simulation::WriteOutput(std::string filename) {
    std::ofstream myfile;
    myfile.open(filename);
    myfile << "x coord, y coord, z coord\n";
    for (int i = 0; i < nparticles_; ++i) {
        myfile << particles_->p[i][0];
        myfile << ",";
        myfile << particles_->p[i][1];
        myfile << ",";
        myfile << particles_->p[i][2];
        myfile << "\n";
    }
    myfile.close();
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
