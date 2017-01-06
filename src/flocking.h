/** @file   flocking.h
 *  @brief  Header for the flocking sub-class
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_FLOCKING_H_
#define SRC_FLOCKING_H_

/* -- Includes -- */
#include "force.h"

class Flocking : public Force {
 public:
  /** @brief Constructor function
  *
  * @param beta flocking constant
  * @return void
  */
  Flocking(double beta);
  /** @brief Destructor function
  *
  * @return void
  */
  ~Flocking();
  /** @brief Calculates forces for particles that are flocking (trying to align their velocities)
  *
  * Forces are calculated considering all other particles.
  *
  * @param particles Particles object with one or more particles
  * @param distances Distance object for considering inter-particle distances
  * @param forces 2-D array for each component of the flocking force acting
  *   on each particle.
  * @return void
  */
  void ComputeForce(Particles &particles, Distance &distances, \
    double (*forces)[3]) const;
 private:
   /** @brief Flocking constant
   */
   const double beta_;
   /** @brief Array to temporarily hold forces acting on each particle as they
   *    are summed.
   */
   double *force_;
};

#endif  // SRC_FLOCKING_H_
