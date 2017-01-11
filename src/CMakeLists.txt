set(SOURCE ${SOURCE} main.cpp)
set(LIBRARY ${LIBRARY} simulation.cpp simulation.h physics.cpp physics.h
<<<<<<< HEAD
    particles.cpp particles.h distance.cpp distance.h force.h gravity.cpp
    boundary.h write.cpp write.h flocking.cpp flocking.h random_force.cpp random_force.h)
=======
    particles.cpp particles.h distance.cpp distance.h force.h gravity.h gravity.cpp
    boundary.h write.cpp write.h flocking.h flocking.cpp drag.h drag.cpp)
>>>>>>> 6123eee69a72a9e220d887a1ae8736399a4955d9

add_library(exmd_lib ${LIBRARY})
add_executable(exmd ${SOURCE})
target_link_libraries(exmd exmd_lib)

# Global Variables
set(GLOBAL_SRC ${SOURCE} ${LIBRARY} PARENT_SCOPE)
