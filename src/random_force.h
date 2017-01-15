/** @file   random_force.h
 *  @brief  Header for the random_force sub-class
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2017-1-9
 *  @bug    No known bugs
 */

#ifndef SRC_RANDOM_FORCE_H_
#define SRC_RANDOM_FORCE_H_

/* -- Includes -- */
#include "force.h"

class Random_Force : public Force {
 public:
  /** @brief Constructor function
  *
  * @param mu mean of normally distributed forces
  * @param sigma standard deviation of normally distributed forces
  * @param force_threshold maximum force
  * @return void
  */
  Random_Force(double mu, double sigma, double force_threshold);
  /** @brief Destructor function
  *
  * @return void
  */
  ~Random_Force();
  /** @brief Calculates forces that are Normal(0,1) in each coordinate
  *
  * Particles are independent of each other.
  *
  * @param particles Particles object with one or more particles
  * @param distances Distance object for considering inter-particle distances
  * @param forces 2-D array for each component of the random_force acting
  *   on each particle.
  * @return void
  */
  void ComputeForce(Particles &particles, Distance const &distances, \
    double (*forces)[3]) const;

 private:
   /** @brief mean
   */
  const double mu_;
   /** @brief standard deviation
   */
  const double sigma_;
   /** @brief maximum force
   */
  const double force_threshold_;
   /** @brief Array to temporarily hold forces acting on each particle as they
   *    are summed.
   */
  double *force_;
   /** @brief Double to temporarily hold the norm of the force.
   */
  double force_norm_;
};

#endif  // SRC_RANDOM_FORCE_H_
