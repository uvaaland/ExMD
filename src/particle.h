/** @file particle.h
 *  @brief header file for Particles class.
 *
 *  This file contains the Particle class.
 *
 *  @author Betul Uralcan (buralcan@princeton.edu)
 *  @date   12/01/2016
 *  @bug    No known bugs.
 */

#include <vector>
using namespace std;

/** @brief creates the particle class, stores particle attributes in vectors
 * @param no paramaters
 * @return does not return */
class Particle {
  public:
    Particle();
    ~Particle();
    /** @brief reads positions and velocities per atom 
     * @param x
     * @param y
     * @param z
     * @param x 
     * @param y
     * @param z
     * @reutn void */
    void insertRow(double* posx, double* posy, double* posz, double* velx, double* vely, double* velz);
    /** @brief combines to make a multidim vector of pos and velocity
     * @return Void */ 
    void insertMatrix();
    /** @brief combines to make a multidim vector of pos and velocity
      * @param  radius 
      * @return Void */
    void insertRadius(double* radius);
    /** @brief combines to make a multidim vector of pos and velocity
     * @param  number of atoms
     * @return Void */
    void insertNumberAtoms(int* numberAtoms);
    /** @brief combines to make a multidim vector of pos and velocity
     * @param lower x boundary
     * @param lower y
     * @param lower z
     * @param upper x
     * @param upper y
     * @param upper z
     * @return Void */
    void setBoundary(double* lowx, double* lowy, double* lowz, double* upx, double* upy, double* upz);
  private:
    vector<double*> atomPosRow_;
    vector< vector<double*> > atomPosMatrix_;
    vector<double*> atomVelRow_;
    vector< vector<double*> > atomVelMatrix_;
    double *radius_;
    int *numberAtoms_;
    vector<double*> boundaryLow_;
    vector<double*> boundaryUp_; 
};
