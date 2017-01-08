/** @file parse.cpp
 *  @brief Initial configuration
 *  reads in the simulation parameters
 @author Betul Uralcan (buralcan@princeton.edu)
 @date 2016-12-12
 @bug No known bugs
 */

/* -- Includes -- */

/* --  Header files -- */
#include "parse.h"

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
 *  @return void
 */
Parse::Parse(std::string filename) {
  fill(filename);      //  method to instantiate attribute arrays
}

/** @brief function to create attribute arrays
 *  instantiates and fills in particles attributes from a file
 *  @param filename input file name
 *  @return void
 */
void Parse::load(std::string filename) {
  // open the input file
  std::ifstream inputFile;
  inputFile.open(filename);
  // std::cout << filename << std::endl;

  // parameters
  int nsteps;
  double dt;
  int output_period;
  double xlow, ylow, zlow, xhigh, yhigh, zhigh;
  
  // reads in the data and fills the attribute arrays
  while (i < nparticles) {
    inputFile >> nsteps;
    inputFile >> dt;
    inputFile >> output_period;
    inputFile >> xlow >> ylow >> zlow;
    inputFile >> xhigh >> yhigh >> zhigh;
  }
}
