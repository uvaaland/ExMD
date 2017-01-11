#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"
#include "force.h"
#include "flocking.h"
#include <math.h>

TEST(ComputeForce, BetaZero) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_flocking1.txt";
  Particles *particles = new Particles(filename, 0);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_flocking2.txt";
  Particles *particles = new Particles(filename, 0);

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
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_flocking3.txt";
  Particles *particles = new Particles(filename, 0);

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
  double l = pow(2, 0.5) / 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_flocking4.txt";
  Particles *particles = new Particles(filename, 0);

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
