#ifndef PHYSICS_H_
#define PHYSICS_H_

class Physics {
  public:
    Physics();
    ~Physics();
    void collision(Particle *particles);
    void bodyForce(Particle *particles);
  private:
    const int bc_;
};

#endif // PHYSICS_H_
