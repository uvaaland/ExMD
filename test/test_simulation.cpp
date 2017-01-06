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
        std::string filename =
      "/home/uvaaland/jenkins/workspace/uvaaland/jenkins_ExMD/test/data_simulation.txt";
        Particles *particles = new Particles(filename, 0);
        
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
