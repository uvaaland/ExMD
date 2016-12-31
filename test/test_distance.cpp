#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"

TEST(getDistance,twoParticles) {
  int nparticles = 2;
  double positions[2][3] = {{1, 0, 0}, {0, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  double distance_expect = 1.;

  Particles *particles = new Particles(nparticles, positions, velocities, \
  masses, radii);

  Distance *distance = new Distance(*particles);

  EXPECT_EQ(distance_expect,distance->getDistance(0,1));

}
