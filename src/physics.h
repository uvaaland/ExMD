#ifndef SRC_PHYSICS_H_
#define SRC_PHYSICS_H_
#include "particles.h"

class Physics {
 public:
    Physics();
    ~Physics();
    void Collisions(int nparticles, Particles &particles, \
       double (*nextpositions)[3], double (*nextvelocities)[3]);
    void ComputeAccelerations();
};

#endif  // SRC_PHYSICS_H_
