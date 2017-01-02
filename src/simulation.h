/** @file   simulation.h
 *  @brief  Header for the simulation class
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-04
 *  @bug    No known bugs
 */

#ifndef SRC_SIMULATION_H_
#define SRC_SIMULATION_H_

/* -- Includes -- */

/* libc includes. */
#include <string>        /* for filename in WriteOutput */
#include <vector>        /* for handling position, force ...etc vectors */
#include <H5Cpp.h>       /* for writing to HDF5 file */

/* MD header files */
#include "physics.h"
#include "force.h"
#include "particles.h"
// Include something for kdtree

/* HDF5 Parameters */
const char DatasetName[] = "Coordinates";
const char member_x[] = "X";
const char member_y[] = "Y";
const char member_z[] = "Z";

/**
 *  @brief Coordinate structure
 *
 *  Structure used for storing parameters to be written to HDF5 file.
 **/
typedef struct {
    double x, y, z;
} Coordinates;


class Simulation {
 public:
    /** @brief Constructor function
     *
     *  Parameters will be filled in when header files for the objects are available
     *
     *  @param physics Physics object
     *  @param particles Particles object
     *  @param kdtree KDtree object
     *  @param dt simulation time step double
     *  @param output_period_ integer giving time steps between output
     *  @return Void
     */
    Simulation(double dt, int output_period, int nparticles, int dim, \
            Particles *particles, Physics *physics, Force *force);
    /** @brief Destructor function
     *
     *  @param No params
     *  @return Void
     */
    ~Simulation();
    /** @brief Simulation step function
     *
     * @params None
     * @return Void
     */
    void Step();
    /** @brief Check particle position and velocity values
     *
     *  Check the particle positions and velocities for NaNs
     *
     *  @params None
     *  @return Void
     */
    int CheckParticles();
    /** @brief Write output to file
     *
     * Write output to file (eventually HDF5) with user specified period
     *
     * @params filename
     * @return Void
     */
    void WriteOutput(std::string filename);
    /** @brief Write output to HDF5 file
     *
     * Write output to HDF5 file with user specified period
     *
     * @params filename
     * @return Void
     */
    void WriteHDF5(std::string filename);
    /** @brief Set constants for HDF5 file format
     *
     * Set constants determining datasize for writing to HDF5 files
     *
     * @return Void
     */
    void SetParametersHDF5();

 private:
    /** @brief Calculate the total acceleration of all particles
     *
     *  @params force pointer to a standard vector of doubles
     *  @return Void
     */
    void CalculateAccelerations();
    /** @brief Calculate the next velocity of all particles
     *
     *  @params Matrix of current velocities
     *  @params matrix of forces
     *  @return Void
     */
    void NextVelocities();
    /** @brief Calculate the next positions of all particles
     *
     *  @params Matrix of current positions
     *  @params Matrix of next velocities
     *  @params Matrix of current velocities
     *  @return Void
     */
    void NextPositions();
    /** @brief Update the position of all particles
     *
     *  @params particle positions
     *  @params next particles positions
     *  @return Void
     */
    void PositionUpdate();
    /** @brief Update the velocity of all particles
     *
     *  @params particle velocities
     *  @params next particle velocities
     *  @return Void
     */
    void VelocityUpdate();
    /** @brief Simulation time step
     */
    const double dt_;
    /** @brief User defined output period
     */
    const int output_period_;
    /** @brief Counter to keep track of when to output
     */
    int counter_;
    /** @brief number of particles in the simulation
     */
    int nparticles_;
    /** @brief dimensionality of the simulation, typically 3
     */
    int dim_;
    /** @brief matrix for holding the next particle positions
     */
    double (*next_positions_)[3];
    /** @brief matrix for holding the next particle velocities
     */
    double (*next_velocities_)[3];
    /** @brief matrix for holding the particle accelerations
     */
    double (*accelerations_)[3];
    /** @brief Particles object which holds information about the particles
     */
    Particles *particles_;
    /** @brief Physics object which holds particle interactions
     */
    Physics *physics_;
    /** @brief Force object specifying how particles exert forces on each other
     */
    Force *force_;
    /** @brief Array of the size of each data dimension
     */
    hsize_t hdf5_data_sizes_[1];
    /** @brief Number of dimensions of data
     */
    int hdf5_rank_;
    // KD tree object
};


#endif  // SRC_SIMULATION_H_
