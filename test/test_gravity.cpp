#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"
#include "force.h"
#include "gravity.h"
#include <math.h>

TEST(ComputeForce, twoParticles) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_gravity.txt";
  Particles *particles = new Particles(filename, 0);
  
  Distance *distance = new Distance(particles);
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);
  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  gravity->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[1][0], -G);
}
