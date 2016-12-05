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

Physics::Physics()
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
void Physics::Collisions(int nparticles, Particles particles, double nextpositions, double nextvelocities) {
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
  double dx,dy,dz,dist,r1,r2,dvx,dvy,dvz,dt,dm,mpm;
  double dist2,distmin2,dxdv,dvdv;
  double p1[3],p2[3],n[3],v1n,v1nnew,v1r[3],v2n,v2nnew,v2r[3];
  for (int i = 0; i < nparticles-1; i++) {
    for (int j = 0; j < nparticles-1-i; j++) {
      dx = nextpositions[i][0]-nextpositions[j][0];
      dy = nextpositions[i][1]-nextpositions[j][1];
      dz = nextpositions[i][2]-nextpositions[j][2];
      dist = sqrt(pow(dx,2)+pow(dy,2)+pow(dz,2));

      // check if a collision occurred and correct it
      if (dist <= (particles.radius[i]+particles.radius[j]) {
        // first we need to back track to the approximate moment of collision
        r1 = particles.radius[i];
        r2 = particles.radius[j];
        // square of distance between particles at moment of collision
        distmin2 = pow(r1+r2,2);
        dist2 = pow(dist,2);
        // different in velocities
        dvx = nextvelocities[i][0]-nextvelocities[j][0];
        dvy = nextvelocities[i][1]-nextvelocities[j][1];
        dvz = nextvelocities[i][2]-nextvelocities[j][2];
        // inner product of delta position and delta velocity
        dxdv = dx*dvx + dy*dvy + dz*dvz;
        // inner product of delta velocity with itself
        dvdv = pow(dvx,2) + pow(dvy,2) + pow(dvz,2);
        // time necessary to back track to moment of collision
        dt = ( dxdv + sqrt(pow(dxdv,2)-dvdv*(dist2-distmin2)) ) / (dvdv);
        // get particle locations at moment of impact
        for (int k = 0; k < 3; k++) {
          p1[k] = nextpositions[i][k] - dt*nextvelocities[i][k];
          p2[k] = nextpositions[j][k] - dt*nextvelocities[j][k];
        }
        // get normal to impact plane
        for (int k = 0; k < 3; k++) {
          n[k] = (p1[k]-p2[k])/(r1+r2);
        }
        // project velocities onto normal
        for (int k = 0; k < 3; k++) {
          // magnitudes of particle velocities along normal to collision
          v1n = nextvelocities[i][k] * n[k];
          v2n = nextvelocities[j][k] * n[k];
        }
        // get velocity residuals, which don't change with collision
        for (size_t k = 0; k < 3; k++) {
          v1r[k] = nextvelocities[i][k] - v1n*n[k];
          v2r[k] = nextvelocities[j][k] - v2n*n[k];
        }
        // update normal velocities for collision
        dm = particles.mass[i]-particles.mass[j];
        mpm = particles.mass[i]+particles.mass[j]
        v1nnew = (v1n*(dm) + 2*particles.mass[j]*v2n) / (mpm);
        v2nnew = (v2n*(-dm) + 2*particles.mass[i]*v1n) / (mpm);
        // add updated normals back to residuals to get collision corrected
        // updated velocities
        for (size_t k = 0; k < 3; k++) {
          nextvelocities[i][k] = v1r[k] + v1nnew*n[k];
          nextvelocities[j][k] = v2r[k] + v2nnew*n[k];
        }
        // finally proceed in time dt to get collision corrected positions
        for (size_t k = 0; k < 3; k++) {
          nextpositions[i][k] = dt*nextvelocities[i][k];
          nextpositions[j][k] = dt*nextvelocities[j][k];
        }
      } // end if
    }
  }
}

void Physics::ComputeAccelerations(KDTree kdtree, int nparticles, Particles particles, int nforces) {
  // // for each particle
  // for (int i = 0; i < nparticles; i++) {
  //   // for each force
  //   for (int j = 0; j < nforces; j++) {
  //     forces_[j]()
  //   }
  // }
}
