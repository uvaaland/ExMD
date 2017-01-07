/** @file   write.cpp
 *  @brief  Implementation of the file-writing functions
 *
 *  @author Uno Brosten Vaaland (uvaaland@princeton.edu)
 *  @date   2017-01-06
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "write.h"


void WriteParametersHDF5(const int nsteps, const int nparticles) {
    hsize_t hdf5_data_sizes[1];
    int hdf5_rank;
    std::string filename = "../output/hdf5/params.h5";

    Parameters *params;
    params = new Parameters;
    params->nsteps = nsteps;
    params->nparticles = nparticles;
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
    hdf5_data_sizes[0] = 1;
    hdf5_rank = sizeof(hdf5_data_sizes) / sizeof(hsize_t);

    // Prepare dataset and file
    H5::DataSpace space(hdf5_rank, hdf5_data_sizes);
    H5::H5File *file = new H5::H5File(filename, H5F_ACC_TRUNC);
    H5::DataSet *dataset = new H5::DataSet(
            file->createDataSet(ParameterDatasetName, mtype, space));
    // Write
    dataset->write(params, mtype);

    delete dataset;
    delete file;
    delete params;
}


void WriteParticlesHDF5(Particles *particles,
                        const int nparticles,
                        const int nt) {
    hsize_t hdf5_data_sizes[1];
    int hdf5_rank;
    std::string filename = "../output/hdf5/vis.h5." + std::to_string(nt);

    Coordinates *coord_list;
    coord_list = new Coordinates[nparticles];
    for (int i = 0; i < nparticles; ++i) {
        coord_list[i].x = particles->p[i][0];
        coord_list[i].y = particles->p[i][1];
        coord_list[i].z = particles->p[i][2];
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
    hdf5_data_sizes[0] = nparticles;
    hdf5_rank = sizeof(hdf5_data_sizes) / sizeof(hsize_t);

    // Prepare dataset and file
    H5::DataSpace space(hdf5_rank, hdf5_data_sizes);
    H5::H5File *file = new H5::H5File(filename, H5F_ACC_TRUNC);
    H5::DataSet *dataset = new H5::DataSet(
            file->createDataSet(ParticleDatasetName, mtype, space));
    // Write
    dataset->write(coord_list, mtype);

    delete dataset;
    delete file;
    delete coord_list;
}
