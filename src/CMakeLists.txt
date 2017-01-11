set(SOURCE ${SOURCE} main.cpp)
set(LIBRARY ${LIBRARY} simulation.cpp simulation.h physics.cpp physics.h
    particles.cpp particles.h distance.cpp distance.h force.h gravity.cpp
    boundary.h write.cpp write.h flocking.cpp flocking.h random_force.cpp random_force.h)

add_library(exmd_lib ${LIBRARY})
add_executable(exmd ${SOURCE})
target_link_libraries(exmd exmd_lib)

# Global Variables
set(GLOBAL_SRC ${SOURCE} ${LIBRARY} PARENT_SCOPE)
