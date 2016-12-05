#ifndef PHYSICS_H_
#define PHYSICS_H_

class Physics {
  public:
    Physics();
    ~Physics();
    void Collisions(KDTree kdtree);
    void ComputeAccelerations(Particles *particles);
  private:
    const int bc_;
    const Force forces_;
};

#endif // PHYSICS_H_
