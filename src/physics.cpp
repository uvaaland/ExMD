/** @file   physics.cpp
 *  @brief  Implementation of the physics class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-12-04
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "physics.h"
#include "kdtreeh.h"

Physics::Physics(int bc)
  : bc_(bc)
{}

Physics::~Physics()
{}

///
/// Physics::Collisions() takes a particles object and a set of predicted next
/// positions and determines if the updated positions reflect particle
/// collisions for any of the particles. In this version, purely elastic
/// collisions are implemented, and the function updates the provided array of
/// next positions to reflect the collisions if any occurred.
///
void Physics::Collisions(int nparticles, Particles particles, double nextpositions) {
  // // initialize distance matrix
  // double D[nparticles][nparticles];
  // for (int i = 0; i < nparticles; i++) {
  //   for (int j = 0; j < nparticles; j++) {
  //     D[i][j] = 0.;
  //   }
  // }
  // compute pairwise distances
  // consider points in which centers of particles
  // are closer than their radii permit
  double dist;
  for (int i = 0; i < nparticles-1; i++) {
    for (int j = 0; j < nparticles-1-i; j++) {
      dist = sqrt(pow(nextpositions[i][0]-nextpositions[j][0],2)+pow(nextpositions[i][1]-nextpositions[j][1],2)+pow(nextpositions[i][2]-nextpositions[j][2],2));
    }
  }
}

void Physics::ComputeAccelerations(KDTree kdtree, int nparticles, Particles particles, int nforces) {
  // for each particle
  for (int i = 0; i < nparticles; i++) {
    // for each force
    for (int j = 0; j < nforces; j++) {
      forces_[j]()
    }
  }
}
