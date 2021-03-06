#include <iostream>
#include "gtest/gtest.h"

#include "physics.h"
#include "force.h"
#include "distance.h"
#include "gravity.h"
#include <math.h>


// test case at moment of collision, spheres touching on edges
TEST(ComputeCollisions, SpheresTouching1D) {
  int nparticles = 2;
  double positions[nparticles][3];
  double velocities[nparticles][3];
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  for (int i = 0; i < nparticles; i++) {
    for (size_t j = 0; j < 3; j++) {
      // positions don't matter for this test, initialize to zero
      positions[i][j] = 0.;
    }
  }
  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-1, 0, 0}, {1, 0, 0}};
  double nextpositions_expect[2][3] = {{-1, 0, 0}, {1, 0, 0}};
  double nextvelocities[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  double nextvelocities_expect[2][3] = {{-0.5, 0, 0}, {0.5, 0, 0}};

  Physics *physics = new Physics();
  physics->ComputeCollisions(*particles, nextpositions, nextvelocities);
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_EQ(nextpositions[1][i], nextpositions_expect[1][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }
}

// test case with spheres overlapping 50%, edges touching other sphere's
// center
TEST(ComputeCollisions, SpheresOverlapping1D) {
  int nparticles = 2;
  double positions[nparticles][3];
  double velocities[nparticles][3];
  double masses[2] = {1, 1};
  double radii[2] = {2, 2};

  for (int i = 0; i < nparticles; i++) {
    for (size_t j = 0; j < 3; j++) {
      // positions don't matter for this test, initialize to zero
      positions[i][j] = 0.;
    }
  }
  Particles *particles = new Particles(nparticles, positions, velocities, \
     masses, radii);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-1, 0, 0}, {1, 0, 0}};
  double nextpositions_expect[2][3] = {{-3., 0, 0}, {3., 0, 0}};
  double nextvelocities[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  double nextvelocities_expect[2][3] = {{-0.5, 0, 0}, {0.5, 0, 0}};
  // for (int i = 0; i < nparticles; i++) {
  //   EXPECT_EQ(masses[i],1);
  // }

  Physics *physics = new Physics();
  physics->ComputeCollisions(*particles, nextpositions, nextvelocities);
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_EQ(nextpositions[1][i], nextpositions_expect[1][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }
}

// test case with spheres overlapping 50%, edges touching other sphere's
// center
TEST(ComputeCollisions, SpheresTouching2D45Angle) {
  int nparticles = 2;
  double positions[nparticles][3];
  double velocities[nparticles][3];
  double masses[2] = {1, 1};
  double radii[2] = {2, 2};

  for (int i = 0; i < nparticles; i++) {
    for (size_t j = 0; j < 3; j++) {
      // positions don't matter for this test, initialize to zero
      positions[i][j] = 0.;
    }
  }
  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-1, 1, 0}, {1, -1, 0}};
  double nextpositions_expect[2][3] = \
    {{-1.8284271247461896, 1.8284271247461896, 0}, \
    {1.8284271247461896, -1.8284271247461896, 0}};
  double nextvelocities[2][3] = {{0.5, -0.5, 0}, {-0.5, 0.5, 0}};
  double nextvelocities_expect[2][3] = {{-0.5, 0.5, 0}, {0.5, -0.5, 0}};
  // for (int i = 0; i < nparticles; i++) {
  //   EXPECT_EQ(masses[i],1);
  // }

  Physics *physics = new Physics();
  physics->ComputeCollisions(*particles, nextpositions, nextvelocities);
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_DOUBLE_EQ(nextpositions[1][i], nextpositions_expect[1][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_DOUBLE_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }
}

// no collision, check that output is 1
TEST(ComputeCollisions, NoCollision) {
  int nparticles = 2;
  double positions[nparticles][3];
  double velocities[nparticles][3];
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  for (int i = 0; i < nparticles; i++) {
    for (size_t j = 0; j < 3; j++) {
      // positions don't matter for this test, initialize to zero
      positions[i][j] = 0.;
    }
  }
  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-2, 0, 0}, {2, 0, 0}};
  double nextpositions_expect[2][3] = {{-2, 0, 0}, {2, 0, 0}};
  double nextvelocities[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  double nextvelocities_expect[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  // for (int i = 0; i < nparticles; i++) {
  //   EXPECT_EQ(masses[i],1);
  // }

  Physics *physics = new Physics();
  int collision = physics->ComputeCollisions(*particles, nextpositions, \
    nextvelocities);
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_DOUBLE_EQ(nextpositions[1][i], nextpositions_expect[1][i]);
  }
  // velocities should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_DOUBLE_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_DOUBLE_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }
  // collision should be set to 1 if there are no collisions
  EXPECT_EQ(collision, 1);
}

// test case with spheres overlapping 50%, edges touching other sphere's
// center
TEST(ComputeAccelerations, twoParticlesGravity) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {1, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  Distance *distance = new Distance(particles);
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);
  double accelerations[2][3] = {{0, 0, 0}, {0, 0, 0}};

  physics->AddForce(gravity);

  physics->ComputeAccelerations(*particles, *distance, accelerations);

  // particle 1 is left of particle 2, so acceleration should be positive
  EXPECT_EQ(accelerations[0][0], G);
  // particle 2 is right of particle 1, so acceleration should be negative
  EXPECT_EQ(accelerations[1][0], -G);
}

// particle just touching boundary, only velocities update
TEST(BoundaryCheck, oneParticleReflecting1) {
  int nparticles = 1;
  double positions[1][3] = {{0, 0, 0}};
  double velocities[1][3] = {{0, 0, 0}};
  double masses[1] = {1};
  double radii[1] = {1};
  double nextpositions[1][3] = {{1, 0, 0}};
  double nextvelocities[1][3] = {{1, 0, 0}};

  Boundary boundary = {reflecting, {{-2, 2}, {-2, 2}, {-2, 2}}};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();
  physics->AddBoundary(&boundary);

  physics->BoundaryCheck(*particles, nextpositions, nextvelocities);

  double nextpositions_expect[1][3] = {{1, 0, 0}};
  double nextvelocities_expect[1][3] = {{-1, 0, 0}};
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
  }
}

// particle having gone past boundary, velocity and position should update
TEST(BoundaryCheck, oneParticleReflecting2) {
  int nparticles = 1;
  double positions[1][3] = {{0, 0, 0}};
  double velocities[1][3] = {{0, 0, 0}};
  double masses[1] = {1};
  double radii[1] = {1};
  double nextpositions[1][3] = {{3, 0, 0}};
  double nextvelocities[1][3] = {{1, 0, 0}};

  Boundary boundary = {reflecting, {{-3, 3}, {-3, 3}, {-3, 3}}};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();
  physics->AddBoundary(&boundary);

  physics->BoundaryCheck(*particles, nextpositions, nextvelocities);

  double nextpositions_expect[1][3] = {{1, 0, 0}};
  double nextvelocities_expect[1][3] = {{-1, 0, 0}};
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
  }
}

// particle having gone past corner, so violating 2 boundaries
TEST(BoundaryCheck, oneParticleReflecting3) {
  int nparticles = 1;
  double positions[1][3] = {{0, 0, 0}};
  double velocities[1][3] = {{0, 0, 0}};
  double masses[1] = {1};
  double radii[1] = {1};
  // should bounce off of +y wall first, so wallIdx should be 3
  double nextpositions[1][3] = {{2.5, 3, 0}};
  double nextvelocities[1][3] = {{1, 1, 0}};

  Boundary boundary = {reflecting, {{-3, 3}, {-3, 3}, {-3, 3}}};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();
  physics->AddBoundary(&boundary);

  physics->BoundaryCheck(*particles, nextpositions, nextvelocities);

  // still colliding with boundary, would need to run again to resolve, but
  // would also need to check for collisions with other particles
  double nextpositions_expect[1][3] = {{2.5, 1, 0}};
  double nextvelocities_expect[1][3] = {{1, -1, 0}};
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
  }
}

// 2 particles reflecting
TEST(BoundaryCheck, twoParticlesReflecting1) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {0.5, 0.5};
  // should bounce off of +y wall first, so wallIdx should be 3
  double nextpositions[2][3] = {{3, 0, 0}, {0, 3, 0}};
  double nextvelocities[2][3] = {{1, 0, 0}, {0, 1, 0}};

  Boundary boundary = {reflecting, {{-3, 3}, {-3, 3}, {-3, 3}}};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();
  physics->AddBoundary(&boundary);

  physics->BoundaryCheck(*particles, nextpositions, \
    nextvelocities);

  // still colliding with boundary, would need to run again to resolve, but
  // would also need to check for collisions with other particles
  double nextpositions_expect[2][3] = {{2, 0, 0}, {0, 2, 0}};
  double nextvelocities_expect[2][3] = {{-1, 0, 0}, {0, -1, 0}};
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_EQ(nextpositions[1][i], nextpositions_expect[1][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }
}

// one particle completely inside domain
TEST(BoundaryCheck, oneParticleInside) {
  int nparticles = 1;
  double positions[1][3] = {{0, 0, 0}};
  double velocities[1][3] = {{0, 0, 0}};
  double masses[1] = {1};
  double radii[1] = {1};
  // should bounce off of +y wall first, so wallIdx should be 3
  double nextpositions[1][3] = {{0, 0, 0}};
  double nextvelocities[1][3] = {{1, 1, 0}};

  Boundary boundary = {reflecting, {{-3, 3}, {-3, 3}, {-3, 3}}};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();
  physics->AddBoundary(&boundary);

  int inside = physics->BoundaryCheck(*particles, nextpositions, \
    nextvelocities);

  // still colliding with boundary, would need to run again to resolve, but
  // would also need to check for collisions with other particles
  double nextpositions_expect[1][3] = {{0, 0, 0}};
  double nextvelocities_expect[1][3] = {{1, 1, 0}};
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
  }
  // velocities should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
  }
  // if inside, then function should return 1
  EXPECT_EQ(inside, 1);
}

// test 4 particles
TEST(ComputeCollisions, 4Particles) {
  const int nparticles = 4;

  double positions[nparticles][3] = {{2, 0, 0}, {-2, 0, 0}, \
  {0, 2 , 0}, {0, -2, 0}};
  double velocities[nparticles][3] = {{-1, 0, 0}, {1, 0, 0}, \
  {0, 0, 0}, {0, 0, 0}};
  double masses[nparticles] = {1, 1, 1, 1};
  double radii[nparticles] = {1, 1, 1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  double nextpositions[nparticles][3] = {{2, 0, 0}, {-2, 0, 0}, {0, 2, 0}, \
  {0, -2, 0}};
  double nextvelocities[nparticles][3] = {{-1, 0, 0}, {1, 0, 0}, {0, 0, 0}, \
  {0, 0, 0}};
  double nextpositions_expect[nparticles][3] = \
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double nextvelocities_expect[nparticles][3] = \
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  // simple time loop modeling a step of simulation
  int nt = 4;
  double dt = 0.5;
  for (int i = 1; i < nt+1; i++) {
    // particles 1, 2 should collide after one second
    if ((i-1)*dt == 1) {
      for (int j = 0; j < nparticles; j++) {
        for (int k = 0; k < 3; k++) {
          // before collision, velocities should stay the same
          nextvelocities_expect[j][k] = -nextvelocities[j][k];
          nextpositions_expect[j][k] = nextpositions[j][k];
        }
      }
    } else {
      for (int j = 0; j < nparticles; j++) {
        for (int k = 0; k < 3; k++) {
          // after collision, velocities should reverse
          nextvelocities_expect[j][k] = nextvelocities[j][k];
          nextpositions_expect[j][k] = nextpositions[j][k];
        }
      }
    }

    physics->ComputeCollisions(*particles, nextpositions, nextvelocities);

    // next positions stay the same, velocities reverse
    for (int j = 0; j < nparticles; j++) {
      for (int k = 0; k < 3; k++) {
        EXPECT_EQ(nextpositions[j][k], nextpositions_expect[j][k]);
        EXPECT_EQ(nextvelocities[j][k], nextvelocities_expect[j][k]);
      }
    }

    // compute next positions
    for (int j = 0; j < nparticles; j++) {
      for (int k = 0; k < 3; k++) {
        nextpositions[j][k] = nextpositions[j][k] + dt * nextvelocities[j][k];
      }
    }
  }  // end time loop
}

// test that accelerations are zero when no forces have been added to physics
TEST(ComputeAccelerations, NoForces) {
  const int nparticles = 2;

  double positions[nparticles][3] = {{2, 0, 0}, {-2, 0, 0}};
  double velocities[nparticles][3] = {{-1, 0, 0}, {1, 0, 0}};
  double masses[nparticles] = {1, 1};
  double radii[nparticles] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);
  Distance *distances = new Distance(particles);
  Physics *physics = new Physics();

  double accelerations[nparticles][3];

  physics->ComputeAccelerations(*particles, *distances, accelerations);
  for (int i = 0; i < nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(0.0, accelerations[i][j]);
    }
  }
}
