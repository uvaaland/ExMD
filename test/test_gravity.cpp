#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"
#include "force.h"
#include "gravity.h"
#include <math.h>

TEST(ComputeForce, twoParticles) {
  int nparticles = 2;
  double positions[2][3] = {{0, 0, 0}, {1, 0, 0}};
  double velocities[2][3] = {{0, 0, 0}, {0, 0, 0}};
  double masses[2] = {1, 1};
  double radii[2] = {1, 1};

  Particles *particles =
      new Particles(nparticles, positions, velocities, masses, radii);

  Distance *distance = new Distance(particles);
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);
  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  gravity->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[1][0], -G);
}
