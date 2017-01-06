/* -- Includes -- */
#include <iostream>
#include "gtest/gtest.h"

#include "simulation.h"

/*
// Creat SimulationTest fixture
class SimulationTest : public testing::Test {
 protected:
     virtual void SetUp() {
        // Make a particles object 
        int nparticles = 2;
        double positions[2][3] = {{-10, 0, 0}, {10, 0, 0}};
        double velocites[2][3] = {{1, 0, 0}, {-1, 0, 0}};
        double masses[3] = {1, 1, 1};
        double radii[3] = {1, 1, 1};
      
        Particles *particles;
        particles = new Particles(nparticles, positions, \
                velocites, masses, radii);
      
        // Make a physics object 
        Physics *physics;
        physics = new Physics();
      
        // Make a simulation object 
        double dt = 0.5;
        int output_period = 1;
      
        Simulation *simulation;
        simulation = new Simulation(dt, output_period, nparticles, 3, \
                particles, physics);
     }

     virtual void TearDown() {
         // Delete Simulation Objects 
         delete physics;
         delete particles;
         delete simulation;
     }

}


// Test 
//TEST(SimulationTest, Constructor) {




    //ASSERT_EQ(nparticles, simulation->nparticles_);
}
*/
