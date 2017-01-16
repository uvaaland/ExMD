# Run the example script
function(generate_output filename)
  SET(EXECUTABLE ./example_${filename})
  message(STATUS "Generating output files for the example")
  execute_process(COMMAND ${EXECUTABLE} OUTPUT_QUIET)
  message(STATUS "Done generating output files!")
endfunction(generate_output)

# Convert CSV files to VTK for example
function(generate_visualization filename)
  message(STATUS "Generating visualization files for the example")
  execute_process(COMMAND pvpython ${PARA_SRC_DIR}/visualize.py
                  ${PARA_OUTPUT_DIR} ${filename} OUTPUT_QUIET)
  message(STATUS "Done generating visualization files!")
endfunction(generate_visualization)

# Print header
function(print_header title number)
  message(STATUS "")
  message(STATUS "###########################")
  message(STATUS "EXAMPLE ${number}: ${title}")
  message(STATUS "###########################")
  message(STATUS "")
endfunction(print_header)

#############################
# EXAMPLE 1: Collision
#############################

print_header(Collision 1)
# Run example_collision
generate_output(collision)
# Generate visualization files for example_collision
generate_visualization(collision)


#############################
# EXAMPLE 2: Gravity
#############################

print_header(Gravity 2)
# Run example_gravity
generate_output(gravity)
# Generate visualization files for example_gravity
generate_visualization(gravity)


#############################
# EXAMPLE 3: Flocking
#############################

print_header(Flocking 3)
# Run example_flocking
generate_output(flocking)
# Generate visualization files for example_flocking
generate_visualization(flocking)

#############################
