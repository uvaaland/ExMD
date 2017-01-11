/** @file   physics.h
 *  @brief  Header for the physics class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_PHYSICS_H_
#define SRC_PHYSICS_H_

/* -- Includes -- */
#include "particles.h"
#include "force.h"
#include "boundary.h"
#include <vector>

class Physics {
 public:
   /** @brief Constructor function
    *  @return void
    */
    Physics();
    /** @brief Destructor function
     *  @return void
     */
    ~Physics();
    /** @brief Checks given predictions for updated particle positions and
     *          corrects overlapping particles that have collided.
     *
     *  Backtracking collisions uses the given velocities and does not account
     *  for changing acceleration over the collision correction interval. Too
     *  high of particle density for a given time step will produce inaccurate
     *  results. This function does not yet account for multiple collisions.
     *
     *  @param particles Particles object with one or more particles
     *  @param nextpositions 2-D array with particles in rows and predicted
     *    coordinates in columns.
     *  @param nextvelocities 2-D array with partcles in rows and predicted
     *    velocity components in columns.
     *  @return void
     */
    int ComputeCollisions(Particles &particles, \
       double (*nextpositions)[3], double (*nextvelocities)[3]);
    /** @brief Generates accelerations for particles given forces acting on them
    *
    * Accelerations are computed from the forces in force, but this does not yet
    * consider multiple forces.
    *
    * @param particles Particles object with one or more particles
    * @param force Force array object with one or more forces
    * @param distances Distance object for considering inter-particle distances
    * @param accelerations 2-D array with particles in rows and 3-D components
    *   of acceleration in columns.
    * @return 1 if no collisions occurred, 0 if collisions occurred
    */
    void ComputeAccelerations(Particles &particles, \
        Distance const &distances, double (*accelerations)[3]);
    /** @brief Imposes user-defined boundary conditions on a set of particles.
    *
    *
    *
    * @param boundarytype Enum specifying particle behavior at boundaries
    *   0: none 1: reflecting 2: periodic
    * @param geometry 3x2 array specifying xmin-xmax, ymin-ymax, and zmin-zmax
    *   boundaries on the simulation space, creating a rectangular domain
    * @param particles Particles object with one or more particles
    * @param nextpositions 2-D array with particles in rows and predicted
    *   coordinates in columns.
    * @param nextvelocities 2-D array with partcles in rows and predicted
    *   velocity components in columns.
    * @return void
    */
    int BoundaryCheck( Particles const &particles, double (*nextpositions)[3], \
      double (*nextvelocities)[3]);
    /** @brief Add a force to the vector of forces for computing accelerations
    *
    * @param force Force to add to the vector
    */
    void AddForce(Force *force);
    /** @brief Add boundaries defining a domain and behavior at the boundaries
    *
    * @param boundary Boundary structure defining limits and behavior
    */
    void AddBoundary(Boundary *boundary);

 private:
    /** @brief Empty vector of forces for ComputeAccelerations
    */
    std::vector<Force *> forces_;
    /** @brief Boundary object which contains the boundary condition and boundary limits
     */
    Boundary *boundary_;
};

#endif  // SRC_PHYSICS_H_
