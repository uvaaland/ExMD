/** @file   drag.cpp
 *  @brief  Implementation file for the drag sub-class
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2017-01-10
 *  @bug    No known bugs
 */

/* -- Includes -- */
#include "force.h"
#include "drag.h"
#include <math.h>


Drag::Drag(double gamma)
    : gamma_(gamma) {
}


Drag::~Drag() {}


void Drag::ComputeForce(Particles &particles, Distance const &distances,
        double (*forces)[3]) const {
    for (int i = 0; i < particles.nparticles; i++) {
        for (int j = 0; j < 3; j++) {
            forces[i][j] = - gamma_ * particles.v[i][j];
        }
    }
}
