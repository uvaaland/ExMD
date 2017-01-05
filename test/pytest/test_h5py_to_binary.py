import unittest
import numpy as np
from context import h5py_to_binary

class VisualizeTestCases(unittest.TestCase):

    def test_ReadOneParticle(self):
        """Test read one particle from HDF5 file."""
        with h5py_to_binary.h5py.File('../test/pytest/files/test_ReadOneParticle.h5', 'r') as hf:
            
            # Check input exists
            self.assertTrue(hf.keys())

            coords = np.array(hf.get('Coordinates'))

        x, y, z = coords[0]

        # Check coordinates
        self.assertEqual(x, 0.0)
        self.assertEqual(y, 1.0)
        self.assertEqual(z, 2.0)

    def test_ReadTwoParticles(self):
        """Test read two particles from HDF5 file."""
        with h5py_to_binary.h5py.File('../test/pytest/files/test_ReadTwoParticles.h5', 'r') as hf:
            
            # Check input exists
            self.assertTrue(hf.keys())

            coords = np.array(hf.get('Coordinates'))

        for i in range(2):
            x, y, z = coords[i]

            # Check coordinates
            self.assertEqual(x, 0.0 + i*3)
            self.assertEqual(y, 1.0 + i*3)
            self.assertEqual(z, 2.0 + i*3)

if __name__ == "__main__":
    unittest.main()
