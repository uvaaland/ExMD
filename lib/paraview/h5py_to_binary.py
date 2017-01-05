import h5py
import numpy as np

with h5py.File('../test/pytest/files/test_InitOneParticle.h5.0', 'r') as hf:
    coords = np.array(hf.get('Coordinates'))

np.save('test_InitOneParticle', coords)
