/** @file   random_force.cpp
 *  @brief  Implementation of the random_force sub-class of force.
 *
 *  @author Christy Graves (cjvaughn@princeton.edu)
 *  @date   2016-1-9
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "force.h"
#include "random_force.h"
#include <random>

Random_Force::Random_Force() {
  force_ = new double[3];
  for (int j = 0; j < 3; j++) {
    force_[j] = 0.;
  }
}

Random_Force::~Random_Force() {
  delete force_;
}

void Random_Force::ComputeForce(Particles &particles, Distance const &distances, \
  double (*forces)[3]) const {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::normal_distribution<double> distribution(0, 1); // mean 0, standard deviation 1
  for (int i = 0; i < particles.nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      forces[i][j] = distribution(generator); // generate numbers;
    }
  }
}
