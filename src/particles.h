#ifndef SRC_PARTICLES_H_
#define SRC_PARTICLES_H_

class Particles {
 public:
    Particles(int nparticles, double (*positions)[3], \
    double (*velocities)[3], double *masses, double *radii);
    ~Particles();
    const int nparticles;
    double (*p)[3];
    double (*v)[3];
    double *mass;
    double *radius;
};

#endif  // SRC_PARTICLES_H_
