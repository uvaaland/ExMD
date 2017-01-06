#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"
#include "force.h"
#include "flocking.h"
#include <math.h>

TEST(ComputeForce, BetaZero) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {1.5, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {1.5, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);
  double beta = 0;  // flocking constant
  Force *flocking = new Flocking(beta);
  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  flocking->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], 1.5);
  EXPECT_EQ(forces[1][0], -1.5);
  EXPECT_EQ(forces[0][1], 0);
  EXPECT_EQ(forces[1][1], 0);
  EXPECT_EQ(forces[0][2], 0);
  EXPECT_EQ(forces[1][2], 0);
}

TEST(ComputeForce, BetaNonZero) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {2, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {1, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);
  double beta = 1;  // flocking constant
  Force *flocking = new Flocking(beta);
  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  flocking->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], 0.2);
  EXPECT_EQ(forces[1][0], -0.2);
  EXPECT_EQ(forces[0][1], 0);
  EXPECT_EQ(forces[1][1], 0);
  EXPECT_EQ(forces[0][2], 0);
  EXPECT_EQ(forces[1][2], 0);
}

TEST(ComputeForce, ThreeParticles) {
  int nparticles = 3;
  double positions[3][3] = {{-1, 0, 0}, {0, 0, 0}, {1, 0, 0}};
  double velocities[3][3] = {{-1, 0, 0}, {0, 0, 0}, {1, 0, 0}};
  double masses[3] = {1, 1, 1};
  double radii[3] = {1, 1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);
  double beta = 1;  // flocking constant
  Force *flocking = new Flocking(beta);
  double forces[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

  flocking->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], 0.9);
  EXPECT_EQ(forces[1][0], 0);
  EXPECT_EQ(forces[2][0], -0.9);
  EXPECT_EQ(forces[0][1], 0);
  EXPECT_EQ(forces[1][1], 0);
  EXPECT_EQ(forces[2][1], 0);
  EXPECT_EQ(forces[0][2], 0);
  EXPECT_EQ(forces[1][2], 0);
  EXPECT_EQ(forces[2][2], 0);
}

TEST(ComputeForce, TwoDimensions) {
  int nparticles = 2;
  double positions[2][3] = {{-1, -1, 0}, {1, 1, 0}};
  double velocities[2][3] = {{-1, -1, 0}, {1, 1, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);
  double beta = 1;  // flocking constant
  Force *flocking = new Flocking(beta);
  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  flocking->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], 0.4);
  EXPECT_EQ(forces[1][0], -0.4);
  EXPECT_EQ(forces[0][1], 0.4);
  EXPECT_EQ(forces[1][1], -0.4);
  EXPECT_EQ(forces[0][2], 0);
  EXPECT_EQ(forces[1][2], 0);
}
