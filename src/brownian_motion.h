/** @file   brownian_motion.h
 *  @brief  Header for the brownian_motion sub-class
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2017-1-6
 *  @bug    No known bugs
 */

#ifndef SRC_BROWNIAN_MOTION_H_
#define SRC_BROWNIAN_MOTION_H_

/* -- Includes -- */
#include "force.h"

class Brownian_Motion : public Force {
 public:
  /** @brief Constructor function
  *
  * @param dt time step
  * @return void
  */
  Brownian_Motion(double dt);
  /** @brief Destructor function
  *
  * @return void
  */
  ~Brownian_Motion();
  /** @brief Calculates forces for particles that are moving with brownian motion
  *
  * Particles are independent of each other.
  *
  * @param particles Particles object with one or more particles
  * @param distances Distance object for considering inter-particle distances
  * @param forces 2-D array for each component of the brownian_motion force acting
  *   on each particle.
  * @return void
  */
  void ComputeForce(Particles &particles, Distance &distances, \
    double (*forces)[3]) const;
 private:
   /** @brief time step
   */
   const double dt_;
   /** @brief Array to temporarily hold forces acting on each particle as they
   *    are summed.
   */
   double *force_;
};

#endif  // SRC_BROWNIAN_MOTION_H_
