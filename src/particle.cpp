/** @file particle.cpp
  *  @brief header file for Particles class.
  *
  *  This file contains the Particle class.
  *
  *  @author Betul Uralcan (buralcan@princeton.edu)
  *  @date   12/01/2016
  *  @bug    No known bugs. */
#include "particle.h"
#include <iostream>
using namespace std;

Particle::Particle(){}

Particle::~Particle(){}

void Particle::insertRow(double* posx, double* posy, double* posz, double* velx, double* vely, double* velz) {
  atomPosRow_.push_back(posx);
  atomPosRow_.push_back(posy);
  atomPosRow_.push_back(posz);
  atomVelRow_.push_back(velx);
  atomVelRow_.push_back(vely);
  atomVelRow_.push_back(velz);
}

void Particle::insertMatrix() {
  atomPosMatrix_.push_back(atomPosRow_);
  atomVelMatrix_.push_back(atomVelRow_);
} 

void Particle::insertRadius(double *radius) {
  radius_ = radius;
}

void Particle::insertNumberAtoms(int *numberAtoms) {
  numberAtoms_ = numberAtoms;
}

void Particle::setBoundary(double* lowx, double* lowy, double* lowz, double* upx, double* upy, double* upz) {
  boundaryLow_.push_back(lowx);
  boundaryLow_.push_back(lowy);
  boundaryLow_.push_back(lowz);
  boundaryUp_.push_back(upx);
  boundaryUp_.push_back(upy);
  boundaryUp_.push_back(upz);
}
