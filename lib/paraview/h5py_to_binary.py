import sys
import h5py
import numpy as np


if __name__ == "__main__":
    
    N = 20
    filepath = "output/hdf5/"
    coords = []

    try:
        h5py.File(filepath + 'vis.h5.0', 'r')
    except IOError:
        print ("Output file cannot be opened! Make sure to generate output by excecuting "
               "./exmd in the ./bin folder before executing 'make vtk'.")
        sys.exit(1)


    for i in range(N):
        with h5py.File(filepath + 'vis.h5.' + str(i), 'r') as hf:
            coords.append(np.array(hf.get('Coordinates')))


    np.save('coords', np.vstack(coords))
