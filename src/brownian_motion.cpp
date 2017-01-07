/** @file   brownian_motion.cpp
 *  @brief  Implementation of the brownian_motion sub-class of force.
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2016-1-6
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "force.h"
#include "brownian_motion.h"
#include <math.h>
#include <cmath>
#include <random>

Brownian_Motion::Brownian_Motion(double dt)
  : dt_(dt) {
  force_ = new double[3];
  for (int j = 0; j < 3; j++) {
    force_[j] = 0.;
  }
}

Brownian_Motion::~Brownian_Motion() {
  delete force_;
}

void Brownian_Motion::ComputeForce(Particles &particles, Distance &distances, \
  double (*forces)[3]) const {
  std::default_random_engine de(time(0)); // seed
  std::normal_distribution<int> nd(0, 1); // mean 0, standard deviation 1
  double rand_normals[particles.nparticles];
  for(int i = 0; i < particles.nparticles; i++) {
      rand_normals[i] = nd(de); // generate numbers;
  }
  for (int i = 0; i < particles.nparticles; i++) {
    // reset force after each particle
    for (int j = 0; j < 3; j++) {
      force_[j] = 0.;
    }
    // calculate kth component of force
    for (int k = 0; k < 3; k++) {
      force_[k] = force_[k] + \
        particles.mass[i] * \
        (rand_normals[i] / pow(dt_, 0.5) - particles.v[i][k]) / dt_;
    }
    // after computing total forces update force array
    for (int j = 0; j < 3; j++) {
      forces[i][j] = force_[j];
    }
  }
}
