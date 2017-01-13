#include "gtest/gtest.h"

#include "particles.h"
#include "force.h"
#include "drag.h"

TEST(DragTest, directionTest) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_directionTest.txt";
  Particles *particles = new Particles(filename, 0);

  Distance *distance = new Distance(particles);

  double gamma = 2;  // drag coefficient

  Force *drag = new Drag(gamma);

  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  drag->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], -gamma * particles->v[0][0]);
}

TEST(DragTest, directionTest3D) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_directionTest3D.txt";
  Particles *particles = new Particles(filename, 0);

  Distance *distance = new Distance(particles);

  double gamma = 2;  // drag coefficient

  Force *drag = new Drag(gamma);

  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  drag->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], -gamma * particles->v[0][0]);
  EXPECT_EQ(forces[0][1], -gamma * particles->v[0][1]);
  EXPECT_EQ(forces[0][2], -gamma * particles->v[0][2]);
}

TEST(DragTest, zeroGamma) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_directionTest3D.txt";
  Particles *particles = new Particles(filename, 0);

  Distance *distance = new Distance(particles);

  double gamma = 0;  // drag coefficient

  Force *drag = new Drag(gamma);

  double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

  drag->ComputeForce(*particles, *distance, forces);

  EXPECT_EQ(forces[0][0], 0);
  EXPECT_EQ(forces[0][1], 0);
  EXPECT_EQ(forces[0][2], 0);
}
