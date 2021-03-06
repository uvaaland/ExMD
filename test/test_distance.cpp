#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"

TEST(getDistance, twoParticles) {
  int nparticles = 2;
  double positions[2][3] = {{1, 0, 0}, {0, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  double distance_expect = 1.;

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);

  EXPECT_EQ(distance_expect, distance->getDistance(0, 1));
}

// test that Distances doesn't break with only one particle
TEST(getDistance, oneParticle) {
  const int nparticles = 1;
  double positions[nparticles][3] = {{1, 0, 0}};
  double velocities[nparticles][3] = {{0, 0, 0}};
  double masses[nparticles] = {1};
  double radii[nparticles] = {1};
  Particles *particles = new Particles(nparticles, positions, velocities, \
    masses, radii);

  Distance *distance = new Distance(particles);

  EXPECT_DOUBLE_EQ(0.0, distance->getDistance(0, 0));
}

TEST(getDistance, updatedPositions) {
  int nparticles = 2;
  double positions[2][3] = {{1, 0, 0}, {0, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  // double distance_expect = 1.;

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);
  // EXPECT_EQ(distance_expect, distance->getDistance(0, 1));

  particles->p[0][0] = 2;
  distance->updateDistances();
  EXPECT_EQ(2, distance->getDistance(0, 1));
}

TEST(getKDistance, DistancePolarity) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {1, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(particles);

  EXPECT_EQ(1, distance->getKDistance(0, 1, 0));
  EXPECT_EQ(-1, distance->getKDistance(1, 0, 0));
}
