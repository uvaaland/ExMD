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
#include <string>           /* for WriteOutput */
#include <stdio.h>          /* for WriteOutput */
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>


/* -- Definitions -- */

Simulation::Simulation(double dt, int output_period, int nparticles, int dim, \
        Particles *particles, Physics *physics, Force *force, \
        Boundary *boundary)
    : dt_(dt),
      output_period_(output_period),
      nparticles_(nparticles),
      dim_(dim),
      particles_(particles),
      physics_(physics),
      force_(force),
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
    // std::vector<double> force(dim);
    // Example of how to access elements of boundary
    // printf("Value of boundary type, %d, and first element of limits, %f\n", \
            boundary_->type, boundary_->limits[2][0]);
    // need to update distances in distance object before computing forces
    physics_->ComputeAccelerations(*particles_, *force_, *distances_, \
       accelerations_);
    NextVelocities();
    NextPositions();

    physics_->ComputeCollisions(*particles_, next_positions_, \
            next_velocities_);
    // physics_->BoundaryCheck(boundarytype_, geometry_, *particles_, \
      // next_positions_, next_velocities_);

    PositionUpdate();
    VelocityUpdate();
    printf("counter = %d\n", counter_);
    std::string filename = std::to_string(counter_);
    filename = "../output/hdf5/vis.h5." + filename;
    WriteParticlesHDF5(filename);
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


void Simulation::WriteParametersHDF5() {
    std::string filename = "../output/hdf5/params.h5";

    Parameters *params;
    params = new Parameters;
    params->nparticles = nparticles_;
    params->nsteps = 100;
    params->height = 10;
    params->width = 10;

    // Define the datatype to be written
    H5::CompType mtype(sizeof(Parameters));
    mtype.insertMember(member_nparticles, HOFFSET(Parameters, nparticles),
            H5::PredType::NATIVE_INT);
    mtype.insertMember(member_nsteps, HOFFSET(Parameters, nsteps),
            H5::PredType::NATIVE_INT);
    mtype.insertMember(member_height, HOFFSET(Parameters, height),
            H5::PredType::NATIVE_INT);
    mtype.insertMember(member_width, HOFFSET(Parameters, width),
            H5::PredType::NATIVE_INT);

    // Compute data sizes
    hdf5_data_sizes_[0] = 1;
    hdf5_rank_ = sizeof(hdf5_data_sizes_) / sizeof(hsize_t);

    // Prepare dataset and file
    H5::DataSpace space(hdf5_rank_, hdf5_data_sizes_);
    H5::H5File *file = new H5::H5File(filename, H5F_ACC_TRUNC);
    H5::DataSet *dataset = new H5::DataSet(
            file->createDataSet(ParameterDatasetName, mtype, space));
    // Write
    dataset->write(params, mtype);

    delete dataset;
    delete file;
    delete params;
}


void Simulation::WriteParticlesHDF5(std::string filename) {
    Coordinates *coord_list;
    coord_list = new Coordinates[nparticles_];
    for (int i = 0; i < nparticles_; ++i) {
        coord_list[i].x = particles_->p[i][0];
        coord_list[i].y = particles_->p[i][1];
        coord_list[i].z = particles_->p[i][2];
    }

    // Define the datatype to be written
    H5::CompType mtype(sizeof(Coordinates));
    mtype.insertMember(member_x, HOFFSET(Coordinates, x),
            H5::PredType::NATIVE_DOUBLE);
    mtype.insertMember(member_y, HOFFSET(Coordinates, y),
            H5::PredType::NATIVE_DOUBLE);
    mtype.insertMember(member_z, HOFFSET(Coordinates, z),
            H5::PredType::NATIVE_DOUBLE);

    // Compute data sizes
    hdf5_data_sizes_[0] = nparticles_;
    hdf5_rank_ = sizeof(hdf5_data_sizes_) / sizeof(hsize_t);

    // Prepare dataset and file
    H5::DataSpace space(hdf5_rank_, hdf5_data_sizes_);
    H5::H5File *file = new H5::H5File(filename, H5F_ACC_TRUNC);
    H5::DataSet *dataset = new H5::DataSet(
            file->createDataSet(ParticleDatasetName, mtype, space));
    // Write
    dataset->write(coord_list, mtype);

    delete dataset;
    delete file;
    delete coord_list;
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
