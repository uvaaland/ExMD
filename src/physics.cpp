/** @file   physics.cpp
 *  @brief  Implementation of the physics class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-12-07
 *  @bug    Does not support multiple collisions or forces yet
 */

/* -- Includes -- */
#include "physics.h"
#include "particles.h"
#include "force.h"
#include <math.h>
#include <stdio.h>
#include <vector>

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
void Physics::Collisions(Particles &particles,  \
  double (*nextpositions)[3], double (*nextvelocities)[3]) {
  double dist, r1, r2, dt, dm, mpm;
  double dist2, distmin2, dxdv, dvdv;
  int curIdx;
  double dp[3], dv[3], p1[3], p2[3], n[3];
  double v1n, v1nnew, v1r[3], v2n, v2nnew, v2r[3];
  // compute pairwise distances and consider points in which centers of
  // particles are closer than their radii permit. For each point, find all
  // potential collisions, and back track the first collision. After
  // backtracking the first collision and updating particle positions and
  // trajectories, recheck to see if particle is still colliding with any other
  // particles.

  // vector containing indices of particles colliding with current particle
  std::vector<int> collisionIdx;

  // start loop over all particles
  for (int i = 0; i < particles.nparticles-1; i++) {
    for (int j = i+1; j < particles.nparticles; j++) {
      for (int k = 0; k < 3; k++) {
        dp[k] = nextpositions[i][k]-nextpositions[j][k];
        printf("p1[%d] = %1.2f, p2[%d] = %1.2f, dp[%d] = %1.2f\n", \
        k, nextpositions[i][k], k, nextpositions[j][k], k, dp[k]);
      }
      // distance between particles 1(i) and 2(j)
      dist = sqrt(pow(dp[0], 2) + pow(dp[1], 2) + pow(dp[2], 2));
      printf("dist = %1.2f\n", dist);

      // check if a collision occurred and save it in collisions
      if (dist <= (particles.radius[i]+particles.radius[j])) {
        collisionIdx.push_back(j);
      }
    }

    // if collisions have occurred, correct the first one
    for (int j = 0; j < collisionIdx.size(); j++) {
      r1 = particles.radius[i];
      curIdx = collisionIdx[j];
      r2 = particles.radius[curIdx];
      printf("r1 = %1.2f, r2 = %1.2f\n", r1, r2);
      // square of distance between particles at moment of collision
      distmin2 = pow(r1+r2, 2);
      printf("distmin2 = %1.2f\n", distmin2);
      dist2 = dist*dist;
      printf("dist2 = %1.2f\n", dist2);
      // difference in velocities
      dxdv = 0.;
      dvdv = 0.;
      // compute differences in velocities and relevant inner products
      for (int k = 0; k < 3; k++) {
        dv[k] = nextvelocities[i][k]-nextvelocities[curIdx][k];
        // inner product of delta position and delta velocity
        dxdv += dp[k]*dv[k];
        // inner product of delta velocity with itself
        dvdv += dv[k]*dv[k];
      }
      // time necessary to back track to moment of collision
      dt = (dxdv + sqrt(pow(dxdv, 2)-dvdv*(dist2-distmin2))) / (dvdv);
      printf("dt = %1.2f\n", dt);
      // get particle locations at moment of impact
      for (int k = 0; k < 3; k++) {
        p1[k] = nextpositions[i][k] - dt*nextvelocities[i][k];
        p2[k] = nextpositions[curIdx][k] - \
         dt*nextvelocities[curIdx][k];
        printf("p1[%d] = %1.2f, p2[%d] = %1.2f\n", k, p1[k], k, p2[k]);
      }
      // get normal to impact plane
      for (int k = 0; k < 3; k++) {
        n[k] = (p2[k]-p1[k])/(r1+r2);
        printf("n[%d] = %1.2f\n", k, n[k]);
      }
      // project velocities onto normal
      v1n = 0.;
      v2n = 0.;
      for (int k = 0; k < 3; k++) {
        // magnitudes of particle velocities along normal to collision
        v1n += nextvelocities[i][k] * n[k];
        v2n += nextvelocities[curIdx][k] * n[k];
      }
      printf("v1 along n = %1.2f\n", v1n);
      printf("v2 along n = %1.2f\n", v2n);
      // get velocity residuals, which don't change with collision
      for (int k = 0; k < 3; k++) {
        v1r[k] = nextvelocities[i][k] - v1n*n[k];
        v2r[k] = nextvelocities[curIdx][k] - v2n*n[k];
        printf("v1r[%d] = %1.2f, v2r[%d] = %1.2f\n", k, v1r[k], k, v2r[k]);
      }
      // update normal velocities for collision
      dm = particles.mass[i]-particles.mass[curIdx];
      mpm = particles.mass[i]+particles.mass[curIdx];
      v1nnew = (v1n*(dm) + 2*particles.mass[curIdx]*v2n) / (mpm);
      v2nnew = (v2n*(-dm) + 2*particles.mass[i]*v1n) / (mpm);
      printf("v1 new = %1.2f\n", v1nnew);
      printf("v2 new = %1.2f\n", v2nnew);
      // add updated normals back to residuals to get collision corrected
      // updated velocities
      for (int k = 0; k < 3; k++) {
        nextvelocities[i][k] = v1r[k] + v1nnew*n[k];
        nextvelocities[curIdx][k] = v2r[k] + v2nnew*n[k];
        printf("v1[%d] = %1.2f, v2[%d] = %1.2f\n", \
         k, nextvelocities[i][k], k, nextvelocities[curIdx][k]);
      }
      // finally proceed in time dt to get collision corrected positions
      for (int k = 0; k < 3; k++) {
        nextpositions[i][k] = p1[k] + dt*nextvelocities[i][k];
        nextpositions[curIdx][k] = p2[k] + dt*nextvelocities[curIdx][k];
        printf("p1[%d] = %1.2f, p2[%d] = %1.2f\n", \
        k, nextpositions[i][k], k, nextpositions[curIdx][k]);
      }
    }  // end loop over collisions
  }  // end loop over i
}  // end collisions

void Physics::ComputeAccelerations(Particles &particles, \
  Force const &force, Distance &distances, double (*accelerations)[3]) {
  // compute forces and store in accelerations array
  // will need to add a temporary array when considering multiple forces
  force.ComputeForce(particles, distances, accelerations);

  // convert forces to accelerations for each particle
  for (int i = 0; i < particles.nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      accelerations[i][j] = accelerations[i][j] / particles.mass[i];
    }
  }
}

void Physics::BoundaryCheck() {
}
