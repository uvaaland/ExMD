# Include source directory
include_directories(${PROJECT_SOURCE_DIR}/src)

#############################################
# EXAMPLES
#############################################
set(EXAMPLE example_collision.cpp)
set(EXAMPLE example_collision_wave_effect.cpp)

add_executable(example_collision example_collision.cpp)
add_executable(example_collision_wave_effect example_collision_wave_effect.cpp)

# Extra linking for the project
target_link_libraries(example_collision exmd_lib)
target_link_libraries(example_collision_wave_effect exmd_lib)

# Global Variables
set(GLOBAL_EXAMPLE ${EXAMPLE} PARENT_SCOPE)
