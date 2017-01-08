import sys
from paraview.simple import *


class Data:

    def __init__(self):
        self.filepath = ""
        self.nsteps = 0
        self.nparticles = 0
        self.box_length = 0.0
        self.box_width = 0.0
        self.box_height = 0.0


def InitData():
    data = Data()
    
    data.filepath = sys.argv[1]

    with open(data.filepath + "/csv/params.csv", 'r') as f:
        keys = f.readline().rstrip().split(', ')
        values = f.readline().split(', ')
    
    params = dict(zip(keys, values))
    
    data.nsteps = int(params['nsteps'])
    data.nparticles = int(params['nparticles'])
    data.box_length = float(params['length'])
    data.box_width = float(params['width'])
    data.box_height = float(params['height'])

    return data


if __name__ == '__main__':

    data = InitData()

    infilepath = data.filepath + "/csv/"
    filenames = [infilepath + "vis.csv.{}".format(it) for it in range(data.nsteps)]

    # create new csv reader
    viscsv = CSVReader(FileName=filenames)

    # create new 'Table To Points'
    tableToPoints = TableToPoints(Input=viscsv)
    tableToPoints.XColumn = 'x'
    tableToPoints.YColumn = ' y'
    tableToPoints.ZColumn = ' z'

    # create a new 'Glyph'
    glyph = Glyph(Input=tableToPoints, GlyphType='Sphere')
    glyph.Scalars = ['POINTS', ' radius']
    glyph.Vectors = ['POINTS', 'None']
    glyph.ScaleFactor = 2.0
    glyph.GlyphTransform = 'Transform2'
    glyph.ScaleMode = 'scalar'
    
    # create view and display data
    renderView = GetActiveViewOrCreate('RenderView')
    glyphDisplay = Show(glyph, renderView)

    # get animation scene
    animationScene = GetAnimationScene()

    # update animation scene based on data timesteps
    animationScene.UpdateAnimationUsingDataTimeSteps()

    outfilepath = data.filepath + "/vtk/"

    # save data
    for it in range(data.nsteps):
        SaveData(outfilepath + "vis.{}.vtk".format(it), proxy=glyph)
        animationScene.GoToNext()

        print "[{0}/{1}] Conversion from CSV to VTK complete!".format(it+1,data.nsteps)
        sys.stdout.flush()

    print "File conversion complete..."
    print "Output can be found in: {}".format(outfilepath)
