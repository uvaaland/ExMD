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
#include <iostream>
#include <fstream>

/* -- Definitions -- */
#define DIM 3

Simulation::Simulation(double dt, int output_period)
    : dt_(dt),
      output_period_(output_period) {
      int counter = 0;
      printf("Simulation object: successful construction");
      }


Simulation::~Simulation() {
    // Call destructors for the particles, kdtree, and physics objects
}


void Simulation::Step() {
    // Loop over particles
        std::vector<double> force(DIM);
        CalculateForce(force);
        // NextVelocity( particle_ind, force ) - works on member attribute
        // nextVelocities
        // NextPosition( particle_ind ) - works on member attribute
        // nextPositions
        // Physics.Collision
        // Physics.BoundaryCheck
        // PositionUpdate()
        // VelocityUpdate()
        // KDTreeUpdate
}


int Simulation::CheckParticles() {
    // Check to see if any NaNs in particle positions or velocities
    // Yes - return 1;
    // No - return 0;
    return 0;
}


void Simulation::WriteOutput(std::string filename) {
    // Write output to file
    std::ofstream myfile;
    myfile.open (filename);
    myfile << "x coord, y coord, z coord\n";
    for (int i = 0; i < nparticles; ++i){
        myfile << p[i][0];
        myfile << ",";
        myfile << p[i][1];
        myfile << ",";
        myfile << p[i][2];
        myfile << "\n";
    }
    myfile.close();
}


void Simulation::CalculateForce(std::vector<double> force) {
    // Calculate the total force on a particle and store in force
}
