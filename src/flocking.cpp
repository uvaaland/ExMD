/** @file   flocking.cpp
 *  @brief  Implementation of the flocking sub-class of force.
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2016-1-5
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "force.h"
#include "flocking.h"
#include <math.h>
#include <cmath>

Flocking::Flocking(double beta)
  : beta_(beta) {
  force_ = new double[3];
  for (int j = 0; j < 3; j++) {
    force_[j] = 0.;
  }
}

Flocking::~Flocking() {
  delete force_;
}

void Flocking::ComputeForce(Particles &particles, Distance const &distances, \
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
            (particles.v[j][k]-particles.v[i][k]) / \
            pow(1 + pow(distances.getDistance(i, j), 2), beta_);
        }
      }
    }
    // after computing total forces update force array
    for (int j = 0; j < 3; j++) {
      forces[i][j] = force_[j];
    }
  }
}
