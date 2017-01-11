import sys
try:
    from paraview.simple import *
except:
    pass


class Data:

    def __init__(self):
        self.filepath = ""
        self.nsteps = 0
        self.nparticles = 0
        self.box_x = 0.0
        self.box_y = 0.0
        self.box_z = 0.0


def InitData():
    data = Data()
    
    data.filepath = sys.argv[1]
    data.filename = sys.argv[2]

    with open(data.filepath + "/csv/{}_params.csv".format(data.filename), 'r') as f:
        keys = f.readline().rstrip().split(',')
        values = f.readline().split(',')
    
    params = dict(zip(keys, values))
    
    data.nsteps = int(params['nsteps'])
    data.nparticles = int(params['nparticles'])
    data.box_ox = float(params['box_ox'])
    data.box_oy = float(params['box_oy'])
    data.box_oz = float(params['box_oz'])
    data.box_lx = float(params['box_lx'])
    data.box_ly = float(params['box_ly'])
    data.box_lz = float(params['box_lz'])

    return data


def ConvertToVTK(data):
    infilepath = data.filepath + "/csv/" + data.filename
    filenames = [infilepath + ".csv.{}".format(it) for it in range(data.nsteps)]

    # create new csv reader
    viscsv = CSVReader(FileName=filenames)

    # create new 'Table To Points'
    tableToPoints = TableToPoints(Input=viscsv)
    tableToPoints.XColumn = 'x'
    tableToPoints.YColumn = 'y'
    tableToPoints.ZColumn = 'z'

    # create a new 'Glyph'
    glyph = Glyph(Input=tableToPoints, GlyphType='Sphere')
    glyph.Scalars = ['POINTS', 'radius']
    glyph.Vectors = ['POINTS', 'None']
    glyph.ScaleFactor = 2.0
    glyph.GlyphTransform = 'Transform2'
    glyph.ScaleMode = 'scalar'
    glyph.GlyphMode = 'All Points'
    
    # create view and display data
    renderView = GetActiveViewOrCreate('RenderView')
    glyphDisplay = Show(glyph, renderView)

    # get animation scene
    animationScene = GetAnimationScene()

    # update animation scene based on data timesteps
    animationScene.UpdateAnimationUsingDataTimeSteps()

    outfilepath = data.filepath + "/vtk/" + data.filename

    # save data
    for it in range(data.nsteps):
        SaveData(outfilepath + ".{}.vtp".format(it), proxy=glyph)
        animationScene.GoToNext()

        print "[{0}/{1}] Conversion from CSV to VTK complete!".format(it+1,data.nsteps)
        sys.stdout.flush()

    print "File conversion complete..."
    print "Output can be found in: {}".format(outfilepath)


def MakeFrame(data):
    box = Box()

    # set box properties
    box.XLength = data.box_lx
    box.YLength = data.box_ly
    box.ZLength = data.box_lz
    box.Center = [data.box_ox, data.box_oy, data.box_oz]

    # save data
    SaveData(data.filepath + "/vtk/" + data.filename + "_frame.vtp", proxy=box)


if __name__ == '__main__':

    data = InitData()
    ConvertToVTK(data)
    MakeFrame(data)
