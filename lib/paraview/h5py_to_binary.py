import sys
import h5py
import numpy as np


if __name__ == "__main__":
    
    filepath = "output/hdf5/"

    # Check that HDF5 files have been generated
    try:
        h5py.File(filepath + 'params.h5', 'r')
    except IOError:
        print ("ERROR: Output file cannot be opened!"
               "Make sure to generate output by excecuting ./exmd in the ./bin folder before executing 'make vtk'.")
        sys.exit(1)

    # Read Parameters from HDF5 file
    with h5py.File(filepath + 'params.h5', 'r') as hf:
        params = np.array(hf.get('Parameters'))

    nsteps = params[0][1]

    # Read Particles from HDF5 files
    coords = []
    for i in range(nsteps):
        with h5py.File(filepath + 'vis.h5.' + str(i), 'r') as hf:
            coords.append(np.array(hf.get('Coordinates')))

    np.save('params', params)
    np.save('coords', np.vstack(coords))
