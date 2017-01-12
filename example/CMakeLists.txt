# Include source directory
include_directories(${PROJECT_SOURCE_DIR}/src)

#############################################
# EXAMPLES
#############################################
set(EXAMPLE ${EXAMPLE} example_collision.cpp example_gravity.cpp
                       example_flocking.cpp)

add_executable(example_collision example_collision.cpp)
add_executable(example_gravity example_gravity.cpp)
add_executable(example_flocking example_flocking.cpp)

# Extra linking for the project
target_link_libraries(example_collision exmd_lib)
target_link_libraries(example_gravity exmd_lib)
target_link_libraries(example_flocking exmd_lib)

# Global Variables
set(GLOBAL_EXAMPLE ${EXAMPLE} PARENT_SCOPE)
