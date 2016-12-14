#ifndef SRC_DISTANCE_H_
#define SRC_DISTANCE_H_

class Distance{
 public:
   Distance(Particles &particles);
   ~Distance();
   double getDistance(int i, int j);
   void updateDistances();
   int squareformToVectorIdx(int i, int j);
 private:
   int factorial(int n);
   int nchoose2(int n);
   int getIdx(int i, int j);
   Particles &particles_;
   int nparticles_;
   double (*distances_)[3];  // distance components
   double *euclideandist_;   // euclidean distance
}

#endif  // SRC_DISTANCE_H_
