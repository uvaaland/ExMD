#ifndef SRC_FORCE_H_
#define SRC_FORCE_H_
#include "distance.h"

class Force {
 public:
    virtual ~Force() {}
    virtual void ComputeForce(Particles &particles, Distance &distances, \
      double (*forces)[3]) const = 0;
};

#endif  // SRC_FORCE_H_
