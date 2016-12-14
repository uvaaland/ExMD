#ifndef SRC_FORCE_H_
#define SRC_FORCE_H_

class Force {
 public:
    Force();
    ~Force();
    virtual void ComputeForce(Particles &particles, Distance &distances, \
      double (*forces)[3]);
};

#endif  // SRC_FORCE_H_
