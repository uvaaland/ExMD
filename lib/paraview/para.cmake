execute_process(COMMAND python2.7 ../lib/paraview/h5py_to_binary.py)
execute_process(COMMAND pvpython ../lib/paraview/visualize.py ${OUTPUT})
