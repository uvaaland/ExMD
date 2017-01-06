find_package(HDF5)
if(HDF5_FOUND)
    include_directories(${HDF5_INCLUDE_DIR})
    set(hdf5_libs hdf5 hdf5_cpp)
endif()

set(SOURCE ${SOURCE} main.cpp)
set(LIBRARY ${LIBRARY} simulation.cpp simulation.h physics.cpp physics.h
    particles.cpp particles.h distance.cpp distance.h force.h gravity.cpp
    boundary.h write.cpp write.h)

add_library(exmd_lib ${LIBRARY})
add_executable(exmd ${SOURCE})
target_link_libraries(exmd exmd_lib ${hdf5_libs})

# Global Variables
set(GLOBAL_SRC ${SOURCE} ${LIBRARY} PARENT_SCOPE)
