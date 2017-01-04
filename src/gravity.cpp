/** @file   gravity.cpp
 *  @brief  Implementation of the gravity class as an example force.
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-12-12
 *  @bug
 */

/* -- Includes -- */
#include "force.h"
#include "gravity.h"
#include <math.h>

Gravity::Gravity(double G)
  : G_(G) {
  force_ = new double[3];
  for (int j = 0; j < 3; j++) {
    force_[j] = 0.;
  }
}

Gravity::~Gravity() {
  delete force_;
}

void Gravity::ComputeForce(Particles &particles, Distance &distances, \
  double (*forces)[3]) const {
  for (int i = 0; i < particles.nparticles; i++) {
    // reset force after each particle
    for (int j = 0; j < 3; j++) {
      force_[j] = 0.;
    }
    // compute forces resulting from all other particles
    for (int j = 0; j < particles.nparticles; j++) {
      // ignore case when particles are the same
      if (i != j) {
        // calculate kth component of force between particles i and j
        for (int k = 0; k < 3; k++) {
          force_[k] = force_[k] + \
            distances.getKDistance(i, j, k) * \
            (G_ * particles.mass[i] * particles.mass[j]) / \
            pow(distances.getDistance(i, j), 3);
        }
      }
    }
    // after computing total forces update force array
    for (int j = 0; j < 3; j++) {
      forces[i][j] = force_[j];
    }
  }
}
