from paraview.simple import *
import h5py
import numpy as np


class Data:

    def __init__(self):
        self.nparticles = 0
        self.ntimesteps = 0
        self.space_width = 0.0
        self.space_height = 0.0
        self.filename = ''
        self.particles = []


class Particle:

    def __init__(self):
        self.coords = (0, 0, 0)
        self.radius = 0.0

    def GetCoordX(self):
        return self.coords[0]

    def GetCoordY(self):
        return self.coords[1]
    
    def GetCoordZ(self):
        return self.coords[2]

    def GetRadius(self):
        return self.radius


def InitData():
    data = Data()

    nparticles = 2
    ntimesteps = 1
    space_width = 10.0
    space_height = 10.0
    filename = "../../build/output/hdf5/vis.h5."
    
    data.nparticles = nparticles
    data.ntimesteps = ntimesteps
    data.space_width = space_width
    data.space_height = space_height
    data.filename = filename

    return data


def InitParticles(nt, data):
    with h5py.File(data.filename + str(nt), 'r') as hf:
        coords = np.array(hf.get('Coordinates'))
        for i in range(data.nparticles):
            data.particles.append(Particle())
            data.particles[i].coords = coords[i]
            data.particles[i].radius = 1.0


def ResetParticles(data):
    data.particles = []


def ConvertToVTK:
    pass


if __name__ == "__main__":
    data = InitData()

    for nt in range(data.ntimesteps):
        InitParticles(nt, data)

        ConvertToVTK(data)

        ResetParticles(data)
