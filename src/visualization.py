#!/usr/bin/env python2
# -*- coding: utf-8 -*-
"""
Created on Sun Dec  4 11:46:33 2016

@author: christy
"""
import time
import numpy as np
from paraview.simple import *


def readInputPositions(nt, num_particles, path):
    positions = np.zeros((nt, num_particles, 3))
    for j in range(nt):
        fileName = path+'test.csv.'+str(j)
        f = open(fileName, 'r')
        lines = f.readlines()
        for i in range(num_particles):
            line = lines[i+1]
            values = line.split(',')
            positions[j, i, 0] = values[0]
            positions[j, i, 1] = values[1]
            positions[j, i, 2] = values[2]
        f.close()
    return positions


def readInputRadius(nt, num_particles, path):
    radius = np.zeros((num_particles, 1))
    fileName = path+'test_radius.csv'
    f = open(fileName, 'r')
    lines = f.readlines()
    for i in range(num_particles):
        radius[i] = lines[i+1]
    f.close()
    return radius


def stepPlot(particles, positions, time_index):
    particle_index = 0
    for particle in particles:
        particle.Center = positions[time_index+1, particle_index]
        particle_index += 1
        Show(particle)
    return


def deleteObjects(particles, domain):
    for particle in particles:
        Delete(particle)
    Delete(domain)
    return


num_particles = 10  # number of particles
nt = 5  # number of time steps
boundary = [1, 1, 1]  # domain size
x = boundary[0]
y = boundary[1]
z = boundary[2]
pause_time = 0.5  # amount of time to pause between time steps

"""Draw Domain"""
domain = Box(Center=[x/2.0, y/2.0, z/2.0], XLength=x, YLength=y, ZLength=z)
dp = GetDisplayProperties(domain)
dp.Representation = 'Outline'
Show(domain)
Render()
time.sleep(pause_time)

path = '/home/christy/Documents/Scientific_Computing/Project/'
particles = []

positions = readInputPositions(nt, num_particles, path)
radius = readInputRadius(nt, num_particles, path)

"""Draw Initial Particles"""
for i in range(num_particles):
    particle = Sphere(Center=positions[0, i], Radius=radius[i])
    particles.append(particle)
    Show(particle)
Render()
time.sleep(pause_time)

"""Update Over Time"""
for i in range(nt-1):
    stepPlot(particles, positions, i)
    Render()
    time.sleep(pause_time)

"""Delete Objects"""
deleteObjects(particles, domain)
Render()
