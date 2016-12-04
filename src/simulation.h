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
// Include physics header file 
// Include particles header file 
// Include something for kdtree 

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
    Simulation( double dt, int output_period );
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
  private:
    /** @brief Calculate the total force on one particle 
     *
     *  @params force pointer to a standard vector of doubles
     *  @return Void 
     */ 
    void CalculateForce( std::vector<double>& force );
    /** @brief Simulation time step 
     */
    const double dt_;
    /** @brief User defined output period
     */
    const int output_period_;
    /** @brief Counter to keep track of when to output 
     */
    int counter;
    /** @brief matrix for holding the next particle positions
     */ 
    std::vector< std::vector<double*> > nextPosMatrix_;
    /** @brief matrix for holding the next particle velocities
     */
    std::vector< std::vector<double*> > nextVelMatrix_;
    // Particle object
    // Physics object
    // KD tree object
};


#endif /* SRC_SIMULATION_H_ */
