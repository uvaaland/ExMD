import unittest
import numpy as np
from context import visualize

class VisualizeTestCases(unittest.TestCase):

    def test_ReadOneParticle(self):
        """Test read one particle from binary npy file."""
        coords = np.load('../test/pytest/files/test_ReadOneParticle.npy')

        x, y, z = coords[0]

        # Check coordinates
        self.assertEqual(x, 0.0)
        self.assertEqual(y, 1.0)
        self.assertEqual(z, 2.0)

    def test_ReadTwoParticles(self):
        """Test read two particles from binary npy file."""
        coords = np.load('../test/pytest/files/test_ReadTwoParticles.npy')

        for i in range(2):
            x, y, z = coords[i]

            # Check coordinates
            self.assertEqual(x, 0.0 + i*3)
            self.assertEqual(y, 1.0 + i*3)
            self.assertEqual(z, 2.0 + i*3)

    def test_InitOneParticle(self):
        """Test initialize one particle read from binary npy file."""
        data = visualize.Data()
        data.nparticles = 1
        data.filenames.append('../test/pytest/files/test_InitOneParticle')

        # Initialize particles
        visualize.InitParticles(0, data)

        # Check coordinates
        x, y, z = data.particles[0].coords
        
        self.assertEqual(x, 0.0)
        self.assertEqual(y, 1.0)
        self.assertEqual(z, 2.0)
    
    def test_InitTwoParticles(self):
        """Test initialize two particles read from binary npy file."""
        data = visualize.Data()
        data.nparticles = 2
        data.filenames.append('../test/pytest/files/test_InitTwoParticles')

        # Initialize particles
        visualize.InitParticles(0, data)
        
        for i in range(data.nparticles):
            x, y, z = data.particles[i].coords

            # Check coordinates
            self.assertEqual(x, 0.0 + i*3)
            self.assertEqual(y, 1.0 + i*3)
            self.assertEqual(z, 2.0 + i*3)

    def test_InitTwoParticlesTwoTimesteps(self):
        """Test initialize two particles read from binary npy file, two
        timesteps.
        """
        data = visualize.Data()
        data.nparticles = 2
        data.filenames.append('../test/pytest/files/test_InitTwoParticlesTwoTimesteps')

        for nt in range(2):
            # Initialize particles
            visualize.InitParticles(nt, data)

            for i in range(data.nparticles):
                x, y, z = data.particles[i].coords

                # Check coordinates
                self.assertEqual(x, 0.0 + i*3 + nt*data.nparticles*3)
                self.assertEqual(y, 1.0 + i*3 + nt*data.nparticles*3)
                self.assertEqual(z, 2.0 + i*3 + nt*data.nparticles*3)

    def test_ResetParticles(self):
        """Test reset particle list after one iteration."""
        data = visualize.Data()

        # Add one particle
        data.particles.append(visualize.Particle())
        self.assertTrue(data.particles)

        # Reset particle list
        visualize.ResetParticles(data)
        self.assertFalse(data.particles)

if __name__ == "__main__":
    unittest.main()
