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
        self.assertEqual(float(params['box_ox']), 10.0)
        self.assertEqual(float(params['box_oy']), 11.0)
        self.assertEqual(float(params['box_oz']), 12.0)
        self.assertEqual(float(params['box_lx']), 100.0)
        self.assertEqual(float(params['box_ly']), 200.0)
        self.assertEqual(float(params['box_lz']), 300.0)

if __name__ == "__main__":
    unittest.main()
