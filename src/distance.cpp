/** @file   distance.cpp
 *  @brief  Implementation of the distance class. stores inter-particle
 *          distances for usage in computing forces and checking for collisions.
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-12-12
 *  @bug    No known bugs.
 */

/* -- Includes -- */
#include "distance.h"
#include "particles.h"
#include <assert.h>
#include <cmath>

Distance::Distance(Particles *particles)
  : particles_(particles),
    nparticles_(particles->nparticles) {
  ndist_ = nchoose2(nparticles_);
  distances_ = new double[ndist_][3];
  euclideandist_ = new double[ndist_];
  updateDistances();
}

Distance::~Distance() {
  delete[] distances_;
  delete[] euclideandist_;
}

// returns linear index corresponding to particle pair, follows upper triangular
int Distance::getIdx(int i, int j) const {
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

// returns euclidean distance between particles i and j
double Distance::getDistance(int i, int j) const {
  // can't look for particles that aren't there
  assert(i < nparticles_);
  assert(j < nparticles_);
  // updateDistances();
  if (i == j) {
    return 0.;
  } else {
    int idx = getIdx(i, j);
    return euclideandist_[idx];
  }
}

// returns kth component of distance between particles i and j
// 0=x, 1=y, 2=z. respects polariy, i.e. if particle i is to the left of
// particle j in the x-axis, the distance between particle i and j is positive,
// while the distance between particle j and i is negative
double Distance::getKDistance(int i, int j, int k) const {
  // can't look for particles that aren't there
  assert(i < nparticles_);
  assert(j < nparticles_);
  // only 3 distance components
  assert(k < 3 && k >= 0);
  // updateDistances();
  if (i == j) {
    return 0.;
  } else {
    int idx = getIdx(i, j);
    // if referencing lower diagonal, switch polarity of direction
    if (i > j) {
      return -distances_[idx][k];
    } else {
      return distances_[idx][k];
    }
  }
}

// computes the distances between particles
void Distance::updateDistances() {
  int curIdx;
  for (int i = 0; i < nparticles_; i++) {
    for (int j = i+1; j < nparticles_; j++) {
      // update coordinate component distances
      curIdx = getIdx(i, j);
      for (int k = 0; k < 3; k++) {
        distances_[curIdx][k] =  \
          particles_->p[j][k] - particles_->p[i][k];
      }
      // compute euclidean distance
      euclideandist_[curIdx] = sqrt(pow(distances_[curIdx][0], 2) + \
       pow(distances_[curIdx][1], 2) + pow(distances_[curIdx][2], 2));
    }
  }
}

int Distance::nchoose2(int n) {
  // need at least one particle
  assert(n >= 1);
  if (n == 1) {
    return 1;
  } else {
    return n*(n-1)/2;
  }
}
