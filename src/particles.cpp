/** @file particle.cpp
 *  @brief Initial configuration
 *  reads in the particle attributes and instantiate the particles class
 @author Betul Uralcan (buralcan@princeton.edu)
 @date 2016-12-12
 @bug No known bugs
 */

/* -- Includes -- */

/* --  Header files -- */
#include "particles3.h"

/* Libraries */
#include <fstream>
#include <array>
#include <cassert>
#include <iostream>

/* -- Definitions -- */

/** @brief Particles class
 *  This object stores the particle attributes in arrays
 */

/** @brief Constructor function
 *  @param filename Input file name
 *  @param npart Number of particles
 *  @return void
 */
Particles::Particles(std::string filename, int npart){
  nparticles = npart; // number of particles
  fill(filename);    //  method to instantiate attribute arrays
}


/** @brief Deconstructor function
 *  @param no parameters
 *  @return void
 */
Particles::~Particles() {
  delete [] p; // positions array of [nparticles][3]
  delete [] v; // velocities array of [nparticles][3]
  delete [] mass; // massess array of [nparticles]
  delete [] radius; // radii array  of [nparicles]
}


/** @brief function to create attribute arrays
 *  instantiates and fills in particles attributes from a file
 *  @param filename input file name
 *  @return void
 */
void Particles::fill(std::string filename) {
  // open the input file
  std::ifstream inputFile;
  inputFile.open(filename);
  std::cout << filename << std::endl;

  // parameters
  double x, y, z, vx, vy, vz, m, r;
  int i = 0;

  // read the number of particles from data file
  if (nparticles == 0) inputFile>>nparticles;
  std::cout << nparticles << std::endl;
  assert(nparticles > 0);
  
  // instantiate the attribute arrays
  p = new double[nparticles][3];
  v = new double[nparticles][3];
  mass = new double[nparticles];
  radius = new double[nparticles];

  // reads in the data and fills the attribute arrays
  while (i<nparticles) {
    inputFile>>x>>y>>z;
    p[i][0]=x;
    std::cout << p[i][0] << std::endl;
    p[i][1]=y;
    p[i][2]=z;
    inputFile>>vx>>vy>>vz;
    v[i][0]=vx;
    std::cout << v[i][0] << std::endl;
    v[i][1]=vy;
    v[i][2]=vz;
    inputFile>>m;
    mass[i]=m;
    inputFile>>r;
    radius[i]=r;
    std::cout << radius[i] << std::endl;
    i++;
  }
}

