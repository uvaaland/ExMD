/** @file   distance.h
 *  @brief  Header for the physics class
 *
 *  @author Adrian Tasistro-Hart (adriant@princeton.edu)
 *  @date   2017-1-5
 *  @bug    No known bugs
 */

#ifndef SRC_DISTANCE_H_
#define SRC_DISTANCE_H_

/* -- Includes -- */
#include "particles.h"

class Distance {
 public:
 /** @brief Constructor function
  *  @param particles Particles object with one or more particles
  *  @return void
  */
  explicit Distance(Particles *particles);
 /** @brief Destructor function
  *  @return void
  */
  ~Distance();
 /** @brief Retrieves euclidean distance between particles i and j
  *
  * @param i first particle to consider
  * @param j second particle to consider
  * @return euclidean distance between particles
  */
  double getDistance(int i, int j) const;
  /** @brief Retrieves desired component of the distance between two particles
  *
  * Distance is computed as the second (j) minus the first (i) and preserves
  * the sign of the difference.
  *
  * @param i first particle to consider
  * @param j second particle to consider
  * @param k component of distance to return (0:x 1:y 2:z)
  * @return kth component of inter-particle distance
  */
  double getKDistance(int i, int j, int k) const;
  /** @brief Updates distances to reflect updates particle positions
  *
  * @return void
  */
  void updateDistances();

 private:
  /** @brief Computes the factorial of an integer
  *
  * @param n integer to compute factorial of
  * @return n!
  */
  int factorial(int n);
  /** @brief Computes the number of combinations of two of a given integer
  *
  * @param n integer to combine
  * @return number of combinations
  */
  int nchoose2(int n);
  /** @brief Returns the linear index corresponding to particle pair
  *
  * Follows row-wise the upper triangular of a distance matrix, with i indexing
  * rows and j indexing columns.
  *
  * @param i first particle's index
  * @param j second particle's index
  * @return linear index
  */
  int getIdx(int i, int j) const;
  /** @brief Particles for which to keep record of distances
  */
  Particles *particles_;
  /** @brief Total number of interparticle distances
  */
  int ndist_;
  /** @brief Total number of particles
  */
  int nparticles_;
  /** @brief 2-D array with ndist_ rows and 3 columns, recording each component
  *   of inter-particle distances.
  */
  double (*distances_)[3];
  /** @brief Array of length ndist_ recording euclidean distances between
  *   particles
  */
  double *euclideandist_;   // euclidean distance
};

#endif  // SRC_DISTANCE_H_
