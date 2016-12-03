/** @file main.cpp
 *  @brief Main routine for dummy project.
 *  
 *  This file contains the main() function for the dummy project.
 *  
 *  @author Betul Uralcan (buralcan@princeton.edu)
 *  @date   11/28/2016
 *  @bug    No known bugs.
 */         
#include <iostream>
#include <fstream>
#include <vector>
#include "particle.h"
using namespace std;

/** @brief main
 * main driver
 *@return return 0
 */
int main() {

/* initialization */
ifstream inputFile("data.txt");
double posx = 0;
double posy = 0;
double posz = 0;
double velx = 0;
double vely = 0;
double velz = 0;
double lowx, lowy, lowz;
double upx, upy, upz;
double rad;
int numAtoms;

/* particle class instantiated */
Particle *assignParticles = new Particle();

/*read in number of atoms, radius, boundaries */
inputFile >> numAtoms >> rad;
inputFile >> lowx >> lowy >> lowz;
inputFile >> upx >> upy >> upz;
/* number of atoms */
assignParticles->insertNumberAtoms(&numAtoms);
/* radius */
assignParticles->insertRadius(&rad);
/*boundaries of the rectangular box */
assignParticles->setBoundary(&lowx, &lowy, &lowz, &upx, &upy, &upz);

/* read in the data and create a vector for positions and a vector for velocities */
while (inputFile >> posx >> posy >> posz >> velx >> vely >> velz)
{
  assignParticles->insertRow(&posx, &posy, &posz, &velx, &vely, &velz);
  assignParticles->insertMatrix();
}
inputFile.close();

delete assignParticles;
return 0;
}
