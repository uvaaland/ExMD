import sys
import numpy as np
try:
    from paraview.simple import *
except:
    pass


class Data:

    def __init__(self):
        self.nparticles = 0
        self.nsteps = 0
        self.space_width = 0.0
        self.space_height = 0.0
        self.outputfiles = []
        self.inputfiles = []
        self.particles = []

        self.coords = []


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
    
    inputfiles = ["params", "coords"]
    outputfiles = [sys.argv[1]]

    params = np.load(inputfiles[0] + '.npy')
    nparticles, nsteps, space_width, space_height = params[0]

    data.nparticles = nparticles
    data.nsteps = nsteps
    data.space_width = space_width
    data.space_height = space_height
    data.outputfiles = outputfiles
    data.inputfiles = inputfiles
    
    coords = np.atleast_2d(np.load(inputfiles[1] + '.npy'))
    data.coords = coords

    return data


def InitParticles(nt, data):
    for i in range(data.nparticles):
        data.particles.append(Particle())
        data.particles[i].coords = data.coords[nt][i]
        data.particles[i].radius = 1.0


def ResetParticles(data):
    data.particles = []


def ConvertToVTK(nt, data):
    spheres = []
    renderView = GetActiveViewOrCreate('RenderView')

    for i in range(data.nparticles):
        spheres.append(Sphere())
        spheres[i].Radius = 1.0
        spheres[i].ThetaResolution = 50
        spheres[i].PhiResolution = 50

        spheres[i].Center = list(data.particles[i].coords)

    dataset = GroupDatasets(Input=spheres)
    datasetDisplay = Show(dataset, renderView)

    filepath = data.outputfiles[0] + "/spheres.{}.vtm".format(nt)
    SaveData(filepath, proxy=dataset)


if __name__ == "__main__":
    data = InitData()
    InitParticles(0, data)

    for nt in range(data.nsteps):
        InitParticles(nt, data)

        ConvertToVTK(nt, data)

        ResetParticles(data)
