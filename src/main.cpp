/** @file main.cpp
 *  @brief Main routine for dummy project.
 *
 *  This file contains the main() function for the dummy project.
 *
 *  @author Jon Doe (doe@gmail.com)
 *  @date   11/28/2016
 *  @bug    No known bugs.
 */

#include <iostream>
#include "project1.h"
#include <fstream>
#include <vector>
#include "particle.h"
using namespace std;

/** @brief Main routine for dummy project
 *
 *  Does some stuff
 *
 *  @return 0
 */
int main() {
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

Particle *assignParticles = new Particle();

inputFile >> numAtoms >> rad;
inputFile >> lowx >> lowy >> lowz;
inputFile >> upx >> upy >> upz;

assignParticles->insertNumberAtoms(&numAtoms);
assignParticles->insertRadius(&rad);
assignParticles->setBoundary(&lowx, &lowy, &lowz, &upx, &upy, &upz);

while (inputFile >> posx >> posy >> posz >> velx >> vely >> velz)
{
  assignParticles->insertRow(&posx, &posy, &posz, &velx, &vely, &velz);
  assignParticles->insertMatrix();
  //cout << posx << posy << posz << velx << vely << velz << endl; 
}
inputFile.close();

assignParticles->getFirstRow();
assignParticles->getFirstMatrix();
delete assignParticles;
return 0;
}
