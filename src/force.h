#ifndef SRC_FORCE_H_
#define SRC_FORCE_H_

class Force {
 public:
    Force();
    ~Force();
    virtual void computeForce();
};

#endif  // SRC_FORCE_H_
