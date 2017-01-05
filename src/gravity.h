/** @file   gravity.h
 *  @brief  Header for the gravity sub-class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_GRAVITY_H_
#define SRC_GRAVITY_H_

/* -- Includes -- */
#include "force.h"

class Gravity : public Force {
 public:
  /** @brief Constructor function
  *
  * @param G gravitational constant
  * @return void
  */
  Gravity(double G);
  /** @brief Destructor function
  *
  * @return void
  */
  ~Gravity();
  /** @brief Calculates gravitational force between given particles
  *
  * Forces acting on each particle as a result of all of the other particles
  * are computed.
  *
  * @param particles Particles object with one or more particles
  * @param distances Distance object for considering inter-particle distances
  * @param forces 2-D array for each component of the gravitational force acting
  *   on each particle.
  * @return void
  */
  void ComputeForce(Particles &particles, Distance &distances, \
    double (*forces)[3]) const;
 private:
   /** @brief Gravitational constant
   */
   const double G_;
   /** @brief Array to temporarily hold forces acting on each particle as they
   *    are summed.
   */
   double *force_;
};

#endif  // SRC_GRAVITY_H_
