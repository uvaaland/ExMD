/** @file particle.h
 *  @brief header file for Particles class.
 *
 *  This file contains the Particle class.
 *
 *  @author Betul Uralcan (buralcan@princeton.edu)
 *  @date   12/01/2016
 *  @bug    No known bugs.
 */

#ifndef SRC_PARTICLE_H_
#define SRC_PARTICLE_H_

#include <vector>

/** @brief creates the particle class, stores particle attributes in std::vectors
 * @param no paramaters
 * @return does not return */
class Particle {
 public:
  Particle();
  ~Particle();
  /** @brief reads positions and velocities per atom
   * @param posx
   * @param posy
   * @param posz
   * @param velx
   * @param vely
   * @param velz
   * @return void */
  void insertRow(double* posx, double* posy, double* posz, double* velx,
                 double* vely, double* velz);
  /** @brief combines to make a multidim std::vector of pos and velocity
   * @return Void */
  void insertMatrix();
  /** @brief combines to make a multidim std::vector of pos and velocity
    * @param  radius
    * @return Void */
  void insertRadius(double* radius);
  /** @brief combines to make a multidim std::vector of pos and velocity
   * @param  numberAtoms
   * @return Void */
  void insertNumberAtoms(int* numberAtoms);
  /** @brief combines to make a multidim std::vector of pos and velocity
   * @param lowx boundary
   * @param lowy
   * @param lowz
   * @param upx
   * @param upy
   * @param upz
   * @return Void */
  void setBoundary(double* lowx, double* lowy, double* lowz, double* upx,
                   double* upy, double* upz);

 private:
  std::vector<double*> atomPosRow_;
  std::vector<std::vector<double*> > atomPosMatrix_;
  std::vector<double*> atomVelRow_;
  std::vector<std::vector<double*> > atomVelMatrix_;
  double* radius_;
  int* numberAtoms_;
  std::vector<double*> boundaryLow_;
  std::vector<double*> boundaryUp_;
};

#endif  // SRC_PARTICLE_H_
