#ifndef SRC_DISTANCE_H_
#define SRC_DISTANCE_H_
#include "particles.h"

class Distance {
 public:
  explicit Distance(Particles const &particles);
  ~Distance();
  double getDistance(int i, int j);
  double getKDistance(int i, int j, int k);
  void updateDistances();
  //  int squareformToVectorIdx(int i, int j);
 private:
  int factorial(int n);
  int nchoose2(int n);
  int getIdx(int i, int j);
  Particles const &particles_;
  int ndist_;               // number of pairwise distances to consider
  int nparticles_;
  double (*distances_)[3];  // distance components
  double *euclideandist_;   // euclidean distance
};

#endif  // SRC_DISTANCE_H_
