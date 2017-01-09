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

/* MD header files */
#include "physics.h"
#include "distance.h"
#include "particles.h"
#include "boundary.h"


class Simulation {
 public:
    /** @brief Constructor function
     *
     *  Parameters will be filled in when header files for the objects are available
     *
     *  @param physics Physics object
     *  @param particles Particles object
     *  @param Force object
     *  @param dt simulation time step double
     *  @param output_period_ integer giving time steps between output
     *  @return Void
     */
    Simulation(double dt, int output_period, int nparticles, int dim, \
            bool checkNaN, Particles *particles, Physics *physics, \
            Boundary *boundary);
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

 private:
    // friend class SimulationTest;
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
    /** @brief Switch on/off NaN checking
     *
     *  Switch on/off checking for NaNs in the particle positions and velocities
     */
    bool checkNaN_;
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
    /** @brief Boundary object which contains the boundary condition and boundary limits
     */
    Boundary *boundary_;
    /** @brief Distance object containing inter-particle distances
     */
    Distance *distances_;
};


#endif  // SRC_SIMULATION_H_
