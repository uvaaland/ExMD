# Function for running the example script
function(generate_output filename)
  SET(EXECUTABLE ./example_${filename})
  message(STATUS "Generating example output files")
  execute_process(COMMAND ${EXECUTABLE} OUTPUT_QUIET)
  message(STATUS "Done generating example output files!")
endfunction(generate_output)

# Function for converting CSV files to VTK for example
function(generate_visualization filename)
  message(STATUS "Generating visualization files")
  execute_process(COMMAND pvpython ${PARA_SRC_DIR}/visualize.py
                  ${PARA_OUTPUT_DIR} ${filename} OUTPUT_QUIET)
              message(STATUS "Done generating visualization files!")
endfunction(generate_visualization)

#############################
# EXAMPLE 1: Collision
#############################

# Run example_collision
generate_output(collision)
# Generate visualization files for example_collision
generate_visualization(collision)


#############################
# EXAMPLE 2: Gravity
#############################

# Run example_collision
#execute_process(COMMAND ./example_collision)
# Generate visualization files for example_collision
#execute_process(COMMAND pvpython ${PARA_SRC_DIR}/visualize.py ${PARA_OUTPUT_DIR})

#############################
