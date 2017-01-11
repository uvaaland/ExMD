#include "gtest/gtest.h"

#include "particles.h"
#include "force.h"
#include "drag.h"

TEST(DragTest, directionTest) {
    int nparticles = 2;
    double positions[2][3] = {{0, 0, 0}, {0, 3, 0}};
    double velocities[2][3] = {{10, 0, 0}, {0, 0, 0}};
    double masses[2] = {1, 1};
    double radii[2] = {1, 1};

    Particles *particles = new Particles(nparticles, positions, velocities, 
            masses, radii);

    Distance *distance = new Distance(particles);

    double gamma = 2;  // drag coefficient 

    Force *drag = new Drag(gamma);
    
    double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

    drag->ComputeForce(*particles, *distance, forces);

    EXPECT_EQ(forces[0][0], -gamma*velocities[0][0]);
}


TEST(DragTest, directionTest3D) {
    int nparticles = 2;
    double positions[2][3] = {{0, 0, 0}, {0, 3, 0}};
    double velocities[2][3] = {{10, 8, 6}, {0, 0, 0}};
    double masses[2] = {1, 1};
    double radii[2] = {1, 1};

    Particles *particles = new Particles(nparticles, positions, velocities, 
            masses, radii);

    Distance *distance = new Distance(particles);

    double gamma = 2;  // drag coefficient 

    Force *drag = new Drag(gamma);
    
    double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

    drag->ComputeForce(*particles, *distance, forces);

    EXPECT_EQ(forces[0][0], -gamma*velocities[0][0] );
    EXPECT_EQ(forces[0][1], -gamma*velocities[0][1] );
    EXPECT_EQ(forces[0][2], -gamma*velocities[0][2] );
}


TEST(DragTest, zeroGamma) {
    int nparticles = 2;
    double positions[2][3] = {{0, 0, 0}, {0, 3, 0}};
    double velocities[2][3] = {{10, 8, 6}, {0, 0, 0}};
    double masses[2] = {1, 1};
    double radii[2] = {1, 1};

    Particles *particles = new Particles(nparticles, positions, velocities, 
            masses, radii);

    Distance *distance = new Distance(particles);

    double gamma = 0;  // drag coefficient 

    Force *drag = new Drag(gamma);
    
    double forces[2][3] = {{0, 0, 0}, {0, 0, 0}};

    drag->ComputeForce(*particles, *distance, forces);

    EXPECT_EQ(forces[0][0], 0 );
    EXPECT_EQ(forces[0][1], 0 );
    EXPECT_EQ(forces[0][2], 0 );
}

