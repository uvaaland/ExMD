import unittest
import numpy as np
from context import visualize

class VisualizeTestCases(unittest.TestCase):

    def test_ReadParameterFile(self):
        """Test read csv parameter file."""
        filepath = "../test/pytest/files/test_ReadParameterFile.csv"
        with open(filepath, 'r') as f:
            keys = f.readline().rstrip().split(',')
            values = f.readline().rstrip().split(',')

        params = dict(zip(keys, values))

        # Check parameters
        self.assertEqual(int(params['nsteps']), 100)
        self.assertEqual(int(params['nparticles']), 3)
        self.assertEqual(float(params['width']), 10.0)
        self.assertEqual(float(params['length']), 11.0)
        self.assertEqual(float(params['height']), 12.0)

if __name__ == "__main__":
    unittest.main()
