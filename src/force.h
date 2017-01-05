/** @file   force.h
 *  @brief  Header for the force class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_FORCE_H_
#define SRC_FORCE_H_

/* -- Includes -- */
#include "distance.h"

class Force {
 public:
   /** @brief Destructor function
    *  @return void
    */
    virtual ~Force() {}
   /** @brief Virtual function for computation of forces acting on particles
    *
    * @param particles Particles object with one or more particles
    * @param distances Distance object for considering inter-particle distances
    * @param forces 2-D array for storing the computed forces. As many rows as
    *   particles and 3 columns for each component of the force.
    * @return void
    */
    virtual void ComputeForce(Particles &particles, Distance &distances, \
      double (*forces)[3]) const = 0;
};

#endif  // SRC_FORCE_H_
