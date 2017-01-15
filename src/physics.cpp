/** @file   physics.cpp
 *  @brief  Implementation of the physics class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2016-01-11
 *  @bug    Does not support multiple simultaneous collisions.
 */

/* -- Includes -- */
#include "physics.h"
#include "particles.h"
#include "force.h"
#include "boundary.h"
#include <math.h>
#include <stdio.h>
#include <vector>
#include <assert.h>

Physics::Physics()
{}

Physics::~Physics() {
  // delete pointers to each
  for (int i = 0; i < static_cast<int>(forces_.size()); i++) {
    delete forces_[i];
  }
}

///
/// Physics::Collisions() takes a particles object and a set of predicted next
/// positions and determines if the updated positions reflect particle
/// collisions for any of the particles. In this version, purely elastic
/// collisions are implemented, and the function updates the provided array of
/// next positions to reflect the collisions if any occurred.
///
int Physics::ComputeCollisions(Particles &particles,  \
  double (*nextpositions)[3], double (*nextvelocities)[3]) {
  double dist, r1, r2, dt, dtIdx, dm, mpm;
  double dist2, distmin2, dxdv, dvdv;
  int curIdx;
  double dp[3], dv[3], p1[3], p2[3], n[3];
  double v1n, v1nnew, v1r[3], v2n, v2nnew, v2r[3];
  // threshold for velocity inner product for collision to occur
  double threshold = pow(10, -8);
  // compute pairwise distances and consider points in which centers of
  // particles are closer than their radii permit. For each point, find all
  // potential collisions, and back track the first collision. After
  // backtracking the first collision and updating particle positions and
  // trajectories, recheck to see if particle is still colliding with any other
  // particles.

  // vector containing indices of particles colliding with current particle
  std::vector<int> collisionIdx;
  // track if any collisions occur
  int anycollision = 0;
  // start loop over all particles
  for (int i = 0; i < particles.nparticles-1; i++) {
    // reset collisionIdx for each particle
    collisionIdx.clear();
    // check ith particle against all other particles
    for (int j = i+1; j < particles.nparticles; j++) {
      for (int k = 0; k < 3; k++) {
        dp[k] = nextpositions[i][k]-nextpositions[j][k];
      }
      // distance between particles 1(i) and 2(j)
      dist = sqrt(pow(dp[0], 2) + pow(dp[1], 2) + pow(dp[2], 2));

      // check if a collision occurred and save it in collisions
      if (dist <= (particles.radius[i]+particles.radius[j])) {
        collisionIdx.push_back(j);
      }
    }

    int ncollisions = collisionIdx.size();
    // if collisions have occurred, correct the first one
    if (ncollisions > 0) {
      // array of times for different collisions
      std::vector<double> dts(ncollisions);

      for (int j = 0; j < ncollisions; j++) {
        r1 = particles.radius[i];
        curIdx = collisionIdx[j];
        r2 = particles.radius[curIdx];
        // square of distance between particles at moment of collision
        distmin2 = pow(r1+r2, 2);
        // get distance between particles i and curIdx
        for (int k = 0; k < 3; k++) {
          dp[k] = nextpositions[i][k]-nextpositions[curIdx][k];
        }
        // distance between particles 1(i) and 2(curIdx)
        dist = sqrt(pow(dp[0], 2) + pow(dp[1], 2) + pow(dp[2], 2));
        dist2 = dist*dist;
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

        // if too small of velocity product, ignore collision
        if (dvdv < threshold) {
          dts.erase(dts.begin()+j);
          ncollisions--;
        } else {
          // time necessary to back track to moment of collision
          dts[j] = (dxdv + sqrt(pow(dxdv, 2)-dvdv*(dist2-distmin2))) / (dvdv);
        }
      }

      // pick largest dt (first collision)
      dt = 0.;
      for (int j = 0; j < ncollisions; j++) {
         if (dts[j] >= dt) {
           dtIdx = j;
           dt = dts[j];
         }
      }
      // get particle index corresponding to earliest collision
      curIdx = collisionIdx[dtIdx];

      // get particle locations at moment of impact
      for (int k = 0; k < 3; k++) {
        p1[k] = nextpositions[i][k] - dt*nextvelocities[i][k];
        p2[k] = nextpositions[curIdx][k] - \
         dt*nextvelocities[curIdx][k];
      }

      // get normal to impact plane
      for (int k = 0; k < 3; k++) {
        n[k] = (p2[k]-p1[k])/(r1+r2);
      }
      // project velocities onto normal
      v1n = 0.;
      v2n = 0.;
      for (int k = 0; k < 3; k++) {
        // magnitudes of particle velocities along normal to collision
        v1n += nextvelocities[i][k] * n[k];
        v2n += nextvelocities[curIdx][k] * n[k];
      }
      // get velocity residuals, which don't change with collision
      for (int k = 0; k < 3; k++) {
        v1r[k] = nextvelocities[i][k] - v1n*n[k];
        v2r[k] = nextvelocities[curIdx][k] - v2n*n[k];
      }
      // update normal velocities for collision
      dm = particles.mass[i]-particles.mass[curIdx];
      mpm = particles.mass[i]+particles.mass[curIdx];
      v1nnew = (v1n*(dm) + 2*particles.mass[curIdx]*v2n) / (mpm);
      v2nnew = (v2n*(-dm) + 2*particles.mass[i]*v1n) / (mpm);
      // add updated normals back to residuals to get collision corrected
      // updated velocities
      for (int k = 0; k < 3; k++) {
        nextvelocities[i][k] = v1r[k] + v1nnew*n[k];
        nextvelocities[curIdx][k] = v2r[k] + v2nnew*n[k];
      }
      // finally proceed in time dt to get collision corrected positions
      for (int k = 0; k < 3; k++) {
        nextpositions[i][k] = p1[k] + dt*nextvelocities[i][k];
        nextpositions[curIdx][k] = p2[k] + dt*nextvelocities[curIdx][k];
      }
      if (ncollisions > 0) {
        anycollision = 1;
      }
    }  // end collision if
  }  // end loop over i
  if (anycollision == 1) {
    return 0;
  } else {
    return 1;
  }
}  // end collisions

void Physics::ComputeAccelerations(Particles &particles, \
  Distance const &distances, double (*accelerations)[3]) {
  // make sure acclerations begin as zero
  for (int i = 0; i < particles.nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      accelerations[i][j] = 0.;
    }
  }
  // create temporary array for general case of arbitrarily many forces
  double tmp_accelerations[particles.nparticles][3];
  for (int i = 0; i < static_cast<int>(forces_.size()); i++) {
    forces_[i]->ComputeForce(particles, distances, tmp_accelerations);
    // update accelerations for each force
    for (int j = 0; j < particles.nparticles; j++) {
      for (int k = 0; k < 3; k++) {
        accelerations[j][k] = accelerations[j][k] + tmp_accelerations[j][k];
      }
    }
  }

  // convert forces to accelerations for each particle
  for (int i = 0; i < particles.nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      accelerations[i][j] = accelerations[i][j] / particles.mass[i];
    }
  }
}

int Physics::BoundaryCheck(Particles const &particles, \
  double (*nextpositions)[3], double (*nextvelocities)[3]) {
  // consider each boundary type
  switch (boundary_->type) {
    // no boundaries
    case 0:
      return 1;  // do nothing

    // reflecting boundaries
    case 1:
      double dist, radius, vn, vnnew, vr[3], dt, dts[6];
      int curIdx, wallIdx, whichdt;
      double pcollision[3];
      // normals to walls
      double n[6][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, \
                        {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
      // points on walls, coords in rows,
      // [xmin, xmax, ymin, ymax, zmin, zmax]
      double onwall[6][3];
      // initialize to zero
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
          onwall[i][j] = 0.;
        }
      }

      // generate points on each of the 6 walls
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
          onwall[2*i+j][i] = boundary_->limits[i][j];
        }
      }

      // vector containing indices of particles colliding with boundary
      std::vector<int> collisionIdx;

      // check if any particles are outside of the rectangular domain
      for (int i = 0; i < particles.nparticles; i++) {
        radius = particles.radius[i];
        // check each of the 6 walls
        for (int j = 0; j < 3; j++) {
          if (nextpositions[i][j]-radius <= boundary_->limits[j][0] ||  \
              nextpositions[i][j]+radius >= boundary_->limits[j][1]) {
              collisionIdx.push_back(i);
              break;
          }
        }
      }

      int ncollisions = static_cast<int>(collisionIdx.size());
      if (ncollisions > 0) {
        std::vector<int> dtIdx;
        // correct particles that collided with boundary
        for (int i = 0; i < ncollisions; i++) {
          dtIdx.clear();

          curIdx = collisionIdx[i];
          radius = particles.radius[curIdx];
          // check each of the six walls and find the smallest time increment to
          // backtrack velocity such that the particle is inside the box and
          // also touching some boundary
          for (int j = 0; j < 6; j++) {
            // distance from wall to particle
            dist = 0.;
            vn = 0.;
            for (int k = 0; k < 3; k++) {
              dist += (nextpositions[curIdx][k] - onwall[j][k]) * n[j][k];
              vn += nextvelocities[curIdx][k] * n[j][k];
            }
            dts[j] = (dist - radius) / vn;
          }
          // check time steps and pick smallest time with particle in domain
          for (int j = 0; j < 6; j++) {
            // ignore negative times
            if (dts[j] >= 0) {
              // generate position at moment of collision
              for (int k = 0; k < 3; k++) {
                pcollision[k] = nextpositions[curIdx][k] - \
                 dts[j]*nextvelocities[curIdx][k];
              }
              // check each coordinate
              whichdt = 0;
              for (int k = 0; k < 3; k++) {
                // if outside domain, reject
                if (pcollision[k] - radius < boundary_->limits[k][0] || \
                    pcollision[k] + radius > boundary_->limits[k][1]) {
                  whichdt = 1;
                }
              }
              if (whichdt == 0) {
                dtIdx.push_back(j);
              }
            }
          }
          // printf("%d\n",curIdx);
          // at least one time step must work, otherwise something is wrong
          assert(static_cast<int>(dtIdx.size()) > 0);
          dt = dts[dtIdx[0]];
          wallIdx = dtIdx[0];
          // find smallest dt
          for (int j = 1; j < static_cast<int>(dtIdx.size()); j++) {
            if (dts[dtIdx[j]] < dt) {
              wallIdx = dtIdx[j];  // index of boundary to reflect off of
              dt = dts[wallIdx];
            }
          }
          for (int j = 0; j < 3; j++) {
            pcollision[j] = nextpositions[curIdx][j] - \
             dt*nextvelocities[curIdx][j];
          }

          // now correct nextpositions and nextvelocities for collision
          // project velocities onto normal
          vn = 0.;
          for (int j = 0; j < 3; j++) {
            // magnitudes of particle velocities along normal to collision
            vn += nextvelocities[curIdx][j] * -n[wallIdx][j];
          }
          // get velocity residuals, which don't change with collision
          for (int j = 0; j < 3; j++) {
            vr[j] = nextvelocities[curIdx][j] + vn*n[wallIdx][j];
          }
          // update normal velocity for collision
          vnnew = -vn;
          // add updated normal back to residual to get collision corrected
          // updated velocity
          for (int j = 0; j < 3; j++) {
            nextvelocities[curIdx][j] = vr[j] - vnnew*n[wallIdx][j];
          }
          // finally proceed in time dt to get collision corrected positions
          for (int j = 0; j < 3; j++) {
            nextpositions[curIdx][j] = pcollision[j] + \
             dt*nextvelocities[curIdx][j];
          }
        }
        return 0;
      } else {
        return 1;
      }

    // periodic boundaries
    // case 2:
    //   // first, resolve collisions involving particles that reach out beyond
    // the
    //   // domain
    //   // vector containing indices of particles extending beyond boundary
    //   std::vector<int> outsideIdx;
    //   // vector of vector of arrays containing offsets of boundaries that
    //   // particle is violating, one set of offsets for each boundary for a
    // max
    //   // of 3 arrays. Each array has two zero entries and one non-zero entry.
    //   std::vector<std::vector<double[3]>> offsets;
    //   // array for offsets on each axis
    //   double offsetsAxis[3];
    //   // vector holding arrays for offsets on each axis for each particle
    //   std::vector<double[3]> offsetsParticle;
    //
    //   // check if any particles are outside of the rectangular domain
    //   for (int i = 0; i < particles.nparticles; i++) {
    //     radius = particles.radius[i];
    //     // initialize offsets to zero
    //     for (int j = 0; j < 3; j++) {
    //       offsetsAxis[j] = 0.;
    //     }
    //     offsetsParticle.clear();
    //     // check each of the 6 walls
    //     int outside = 0;  // records if particle is outside at any point
    //     for (int j = 0; j < 3; j++) {
    //       for (int k = 0; k < 2; k++) {
    //         if (pow(-1,k) * (nextpositions[i][j] - pow(-1,k)*radius) <= \
    //             pow(-1,k) * boundary_.limits[j][k]) {
    //           outside = 1;
    //           // offset is the width of the domain in the jth direction,
    //           // positive if k=0, negative if k=1
    //           offsetsAxis[j] = pow(-1,k)*(boundary_.limits[j][1] -
    //  boundary_.limits[j][0]);
    //           offsetsParticle.push_back(offsetsAxis);
    //           // reset offsetsAxis for next j
    //           for (int l = 0; l < 3; l++) {
    //             offsetsAxis[l] = 0.;
    //           }
    //         }
    //       }
    //     }
    //     if (outside == 1) {
    //       outsideIdx.push_back(i);
    //       offsets.push_back(offsetsParticle);
    //     }
    //   }
    //   // having identified particles extending beyond the domain, consider
    // each
    //   // particle and each of its (up to three) periodic equivalent
    // positions in
    //   // terms of collisions that might have occurred with other particles
    // not
    //   // violating boundary conditions or other particles also
    //   const int kOutside = outsideIdx.size();
    //   if (kOutside > 0) {
    //     double periodicpositions[kOutside][3];
    //     // array of offsets to nextpositions to compute periodicpositions
    //     double offsets[3][2];
    //     int curIdx;
    //     // consider each particle outside the boundaries
    //     for (int i = 0; i < kOutside; i++) {
    //       curIdx = outsideIdx[i];
    //       // compute offsets
    //       for (int j = 0; j < 3; j++) {
    //         for (int k = 0; k < 2; k++) {
    //           offsets[j][k] = ;
    //         }
    //       }
    //       for (int j = 0; j < 3; j++) {
    //         periodicpositions[i][j] = nextpositions[curIdx]
    //       }
    //     }
    //
    //     // then, update particle locations whose centers have passed a domain
    //     // edge
    //
    //     return 0;
    //   } else {
    //     return 1;
    //   }
  }
}

// void Collision(double *normal, double dt, double mass1, double mass2, \
//   double (*nextposition1)[3], double (*nextposition2)[3], \
//   double (*nextvelocity1)[3], double (*nextvelocity2)[3]) {
// }

void Physics::AddForce(Force *force) {
  forces_.push_back(force);
}

void Physics::AddBoundary(Boundary *boundary) {
  boundary_ = boundary;
}
