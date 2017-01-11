/** @file   drag.h 
 *  @brief  Header file for the drag sub-class 
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2017-01-10
 *  @bug    No known bugs
 */

#ifndef SRC_DRAG_H_ 
#define SRC_DRAG_H_

/* -- Includes -- */
#include "force.h"

class Drag : public Force {
 public:
     /** @brief Constructor 
      *  @params gamma : the coefficient of drag, F = -gamma v
      */
     Drag(double gamma);
     /** @brief Destructor
      */
     ~Drag();
     /** @brief Force calculating function
      *  @params &particles - address of a Particles object
      *  @params (*forces)[3] - array of forces on the particles
      *  @return void
      */
     void ComputeForce(Particles &particles, Distance const &distances,
             double (*forces)[3]) const;

 private:
     /** @brief coefficient of drag, i.e. F = - gamma v
      */
     const double gamma_;
};

#endif  // SRC_DRAG_H_
