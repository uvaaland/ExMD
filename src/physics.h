#ifndef SRC_PHYSICS_H_
#define SRC_PHYSICS_H_
#include "particles.h"
#include "force.h"

class Physics {
 public:
    Physics();
    ~Physics();
    void Collisions(Particles &particles, \
       double (*nextpositions)[3], double (*nextvelocities)[3]);
    void ComputeAccelerations(Particles &particles, \
       Force const &force, Distance &distances, \
       double (*accelerations)[3]);
    void BoundaryCheck();
};

#endif  // SRC_PHYSICS_H_
