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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data.txt";
  Particles *particles = new Particles(filename, 0);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data2.txt";
  Particles *particles = new Particles(filename, 0);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data2.txt";
  Particles *particles = new Particles(filename, 0);

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


TEST(ComputeCollisions, NoCollision) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data.txt";
  Particles *particles = new Particles(filename, 0);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-2, 0, 0}, {2, 0, 0}};
  double nextpositions_expect[2][3] = {{-2, 0, 0}, {2, 0, 0}};
  double nextvelocities[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  double nextvelocities_expect[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
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

// test case with spheres overlapping 50%, edges touching other sphere's
// center
TEST(ComputeAccelerations, twoParticlesGravity) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_twoParticlesGravity.txt";
  Particles *particles = new Particles(filename, 0);


  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  Distance *distance = new Distance(particles);
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);
  double accelerations[2][3] = {{0, 0, 0}, {0, 0, 0}};

  physics->ComputeAccelerations(*particles, *gravity, *distance, accelerations);

  // particle 1 is left of particle 2, so acceleration should be positive
  EXPECT_EQ(accelerations[0][0], G);
  // particle 2 is right of particle 1, so acceleration should be negative
  EXPECT_EQ(accelerations[1][0], -G);
}

// particle just touching boundary, only velocities update
TEST(BoundaryCheck, oneParticleReflecting1) {
  int nparticles = 1;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_oneParticleReflecting1.txt";
  Particles *particles = new Particles(filename, 0);

  double nextpositions[1][3] = {{1, 0, 0}};
  double nextvelocities[1][3] = {{1, 0, 0}};

  double geometry[3][2] = {{-2, 2}, {-2, 2}, {-2, 2}};
  double boundarytype = 1;  // reflecting

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  physics->BoundaryCheck(boundarytype, geometry, *particles, nextpositions, \
    nextvelocities);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_oneParticleReflecting1.txt";
  Particles *particles = new Particles(filename, 0);
  
  double nextpositions[1][3] = {{3, 0, 0}};
  double nextvelocities[1][3] = {{1, 0, 0}};

  double geometry[3][2] = {{-3, 3}, {-3, 3}, {-3, 3}};
  double boundarytype = 1;  // reflecting


  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  physics->BoundaryCheck(boundarytype, geometry, *particles, nextpositions, \
    nextvelocities);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_oneParticleReflecting1.txt";
  Particles *particles = new Particles(filename, 0);
  
  // should bounce off of +y wall first, so wallIdx should be 3
  double nextpositions[1][3] = {{2.5, 3, 0}};
  double nextvelocities[1][3] = {{1, 1, 0}};

  double geometry[3][2] = {{-3, 3}, {-3, 3}, {-3, 3}};
  double boundarytype = 1;  // reflecting

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  physics->BoundaryCheck(boundarytype, geometry, *particles, nextpositions, \
    nextvelocities);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_twoParticlesReflecting.txt";
  Particles *particles = new Particles(filename, 0);
  
  // should bounce off of +y wall first, so wallIdx should be 3
  double nextpositions[2][3] = {{3, 0, 0}, {0, 3, 0}};
  double nextvelocities[2][3] = {{1, 0, 0}, {0, 1, 0}};

  double geometry[3][2] = {{-3, 3}, {-3, 3}, {-3, 3}};
  double boundarytype = 1;  // reflecting

  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Physics *physics = new Physics();

  physics->BoundaryCheck(boundarytype, geometry, *particles, nextpositions, \
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

// need another test for the resolution of a system by iteratively calling
// ComputeCollisions and then BoundaryCheck
