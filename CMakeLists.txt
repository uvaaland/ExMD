cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dtest=ON'.
option(test "Build all tests." OFF) # Makes boolean 'test' available.


############################################
# PROJECT VARIABLES
############################################
set(PROJECT_NAME ExMD)
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-g -Wall")


############################################
# SOURCE LIBRARIES AND EXECUTABLES
############################################
add_subdirectory(src)


############################################
# DOXYGEN DOCUMENTATION
############################################
add_subdirectory(doc)

############################################
# TESTING
############################################
if (test)
  add_subdirectory(test)
  enable_testing()
  add_test(NAME MyTest COMMAND runUnitTests)
endif()
