set(SOURCE ${SOURCE} main.cpp)
set(LIBRARY ${LIBRARY} simulation.cpp simulation.h physics.cpp physics.h particles.cpp particles.h)

add_library(exmd_lib ${LIBRARY})
add_executable(exmd ${SOURCE})
target_link_libraries(exmd exmd_lib)

# Global Variables
set(GLOBAL_SRC ${SOURCE} ${LIBRARY} PARENT_SCOPE)
