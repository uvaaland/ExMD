#include <iostream>
#include "gtest/gtest.h"

#include "distance.h"
#include "particles.h"

TEST(getDistance, twoParticles) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_distance.txt";
  Particles *particles = new Particles(filename, 0);

  double distance_expect = 1.;

  Distance *distance = new Distance(particles);

  EXPECT_EQ(distance_expect, distance->getDistance(0, 1));
}

TEST(getDistance, updatedPositions) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_distance.txt";
  Particles *particles = new Particles(filename, 0);

  // double distance_expect = 1.;

  Distance *distance = new Distance(particles);
  // EXPECT_EQ(distance_expect, distance->getDistance(0, 1));

  particles->p[0][0] = 2;
  distance->updateDistances();
  EXPECT_EQ(2, distance->getDistance(0, 1));
}

TEST(getKDistance, DistancePolarity) {
  int nparticles = 2;
  std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/"
      "data_distance2.txt";
  Particles *particles = new Particles(filename, 0);

  Distance *distance = new Distance(particles);

  EXPECT_EQ(1, distance->getKDistance(0, 1, 0));
  EXPECT_EQ(-1, distance->getKDistance(1, 0, 0));
}
