#include "particles.h"

Particles::Particles(int nparticles, double (*positions)[3], \
double (*velocities)[3], double *masses, double *radii)
  : nparticles(nparticles) {
  p = new double[nparticles][3];
  v = new double[nparticles][3];
  mass = new double[nparticles];
  radius = new double[nparticles];
  for (int i = 0; i < nparticles; i++) {
    for (int j = 0; j < 3; j++) {
      p[i][j] = positions[i][j];
      v[i][j] = velocities[i][j];
    }
    mass[i] = masses[i];
    radius[i] = radii[i];
  }
}

Particles::~Particles() {
  delete [] p;
  delete [] v;
  delete [] mass;
  delete [] radius;
}
