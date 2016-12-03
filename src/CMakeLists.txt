set(SOURCE ${SOURCE} main.cpp)
set(LIBRARY ${LIBRARY} project1.cpp project1.h particle.h particle.cpp main.cpp)

add_library(project1_lib ${LIBRARY})
add_executable(project1 ${SOURCE})
target_link_libraries(project1 project1_lib)

# Global Variables
set(GLOBAL_SRC ${SOURCE} ${LIBRARY} PARENT_SCOPE)
