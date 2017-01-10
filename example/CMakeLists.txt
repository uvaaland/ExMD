# Include source directory
include_directories(${PROJECT_SOURCE_DIR}/src)

#############################################
# EXAMPLES
#############################################
set(EXAMPLE ${EXAMPLE} example_collision.cpp)

add_executable(example_collision ${EXAMPLE})

# Extra linking for the project
target_link_libraries(example_collision exmd_lib)

# Global Variables
set(GLOBAL_EXAMPLE ${EXAMPLE} PARENT_SCOPE)
