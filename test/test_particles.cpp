#include <iostream>
#include <fstream>
#include "gtest/gtest.h"

#include "particles.h"

// test case at moment of collision, spheres touching on edges
TEST(fill, Input) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data.txt";
  Particles *particles;
  particles = new Particles(filename, 0);

  double positions_expect[2][3] = {{-1, 0, 0}, {1, 0, 0}};
  double velocities_expect[2][3] = {{0.5, 0, 0}, {-0.5, 0, 0}};
  double radius_expect[2] = {1, 1};
  double mass_expect[2] = {1, 1};
  printf("r1 = %1.2f", particles->p[0][0]);

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(particles->p[0][i], positions_expect[0][i]);
    EXPECT_EQ(particles->p[1][i], positions_expect[1][i]);
  }

  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(particles->v[0][i], velocities_expect[0][i]);
    EXPECT_EQ(particles->v[1][i], velocities_expect[1][i]);
  }

  EXPECT_EQ(particles->radius[0], radius_expect[0]);
  EXPECT_EQ(particles->mass[1], mass_expect[1]);
}
