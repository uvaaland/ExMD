#############################
# EXAMPLE 1: Collision
#############################

# Run example_collision
execute_process(COMMAND ./example_collision OUTPUT_QUIET)
# Generate visualization files for example_collision
execute_process(COMMAND pvpython ${PARA_SRC_DIR}/visualize.py
                ${PARA_OUTPUT_DIR} collision OUTPUT_QUIET)


#############################
# EXAMPLE 2: Gravity
#############################

# Run example_collision
#execute_process(COMMAND ./example_collision)
# Generate visualization files for example_collision
#execute_process(COMMAND pvpython ${PARA_SRC_DIR}/visualize.py ${PARA_OUTPUT_DIR})

#############################
