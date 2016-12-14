/** @file   distance.cpp
 *  @brief  Implementation of the distance class. stores inter-particle
 *          distances for usage in computing forces and checking for collisions.
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-12-12
 *  @bug    Does not support multiple collisions yet
 */

/* -- Includes -- */
#include "distance.h"
#include <assert.h>

Distance::Distance(Particles &particles)
  : particles_(particles),
    nparticles_(particles.nparticles) {
  int n = nchoose2(nparticles_);
  distances_ = new double[n][3];
  euclideandist_ = new double[n];
  updateDistances();
}

Distance::~Distance() {
  delete distances_;
  delete euclideandist_;
}

// returns euclidean distance between particles i and j
double Distance::getDistance(int i, int j) {
  if (i == j) {
    return 0.;
  } else {
    idx = getIdx(int i, int j);
    return euclideandist_[idx];
  }
}

// returns linear index corresponding to particle pair, follows upper triangular
double Distance::getIdx(int i, int j) {
  assert(i != j);
  int idx = 0;
  if (i > j) {
    // switch variables to stick to upper triangular
    int tmp = i;
    i = j;
    j = tmp;
  }
  for (int k = 1; k < i+1; k++) {
    idx += nparticles_-k;
  }
  idx += j-(i+1);
  return idx;
}

// returns kth component of distance between particles i and j
// 1=x, 2=y, 3=z
double Distance::getKDistance(int i, int j, int k) {
  if (i == j) {
    return 0.;
  } else {
    idx = getIdx(int i, int j);
    return distances_[idx][k];
  }
}

void Distance::updateDistances() {

}

int Distance::squareformToVectorIdx(int i, int j) {

}

int Distance::factorial(int n) {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int Distance::nchoose2(int n) {
  return factorial(n)/(2*factorial(n-2));
}
