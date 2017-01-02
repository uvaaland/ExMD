#ifndef SRC_GRAVITY_H_
#define SRC_GRAVITY_H_

#include "force.h"

class Gravity : public Force {
 public:
   Gravity(double G);
   ~Gravity();
   void ComputeForce(Particles &particles, Distance &distances, \
    double (*forces)[3]) const;
 private:
   const double G_;  // gravitational constant
   double *force_;   // temporary force
};

#endif  // SRC_GRAVITY_H_
