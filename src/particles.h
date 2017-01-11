#ifndef SRC_PARTICLES_H_
#define SRC_PARTICLES_H_
#include <string>  // for input

class Particles {
 public:
    explicit Particles(std::string filename, int npart = 0);
    ~Particles();
    int nparticles;
    double (*p)[3];
    double (*v)[3];
    double *mass;
    double *radius;
    void fill(std::string filename);
};

#endif  // SRC_PARTICLES_H_
