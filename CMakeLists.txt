cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dtest=ON -Dstyle=ON'.
option(test "Build all tests." OFF) 
option(style "Add Google C++ Style check." OFF)
option(example "Generate examples." ON)


############################################
# PROJECT VARIABLES
############################################
set(PROJECT_NAME ExMD)
project(${PROJECT_NAME})

# Create output folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output/csv)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output/vtk)

# Set compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall")


############################################
# SOURCE LIBRARIES AND EXECUTABLES
############################################
add_subdirectory(src)


############################################
# DOXYGEN DOCUMENTATION
############################################
add_subdirectory(doc)


############################################
# VISUALIZATION
############################################
set(PARA_SRC_DIR ${PROJECT_SOURCE_DIR}/lib/paraview)
set(PARA_OUTPUT_DIR ${PROJECT_BINARY_DIR}/output)
set(OUTPUT_FILENAME exmd)

add_custom_target(vtk
    COMMAND pvpython ${PARA_SRC_DIR}/visualize.py
    ${PARA_OUTPUT_DIR} ${OUTPUT_FILENAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating files for visualizing with paraview"
    VERBATIM)


############################################
# TESTING
############################################
if (test OR style)
  add_subdirectory(test)
  enable_testing()
  add_test(NAME CppUnitTests COMMAND runUnitTests)
  add_test(NAME PyUnitTests COMMAND python2.7
           -m unittest discover 
           ${PROJECT_SOURCE_DIR}/test/pytest)
  if (style)
    # Add path to files in src/
    FOREACH(SRC ${GLOBAL_SRC})
      LIST(APPEND SRC_FILES "${PROJECT_SOURCE_DIR}/src/${SRC}")
    ENDFOREACH()
    
    # Add path to files in test/
    FOREACH(TEST ${GLOBAL_TEST})
      LIST(APPEND TEST_FILES "${PROJECT_SOURCE_DIR}/test/${TEST}")
    ENDFOREACH()

    # Add test for Google C++ Style
    add_test(NAME GoogleStyle COMMAND python2.7 
             ${PROJECT_SOURCE_DIR}/lib/cpplint/cpplint.py
             --filter=-legal,-build/include
             ${SRC_FILES}
             ${TEST_FILES})
  endif()
endif()


############################################
# EXAMPLES
############################################
if (example)
  add_subdirectory(example)
  set(EXAMPLE_SRC_DIR ${PROJECT_SOURCE_DIR}/example)

  # Add path to dependencies
  FOREACH(EXAMPLE ${GLOBAL_EXAMPLE})
    STRING(REPLACE ".cpp" "" EXE ${EXAMPLE})
    LIST(APPEND EXAMPLE_EXE "${CMAKE_CURRENT_BINARY_DIR}/bin/${EXE}")
  ENDFOREACH()

  add_custom_target(example
      COMMAND ${CMAKE_COMMAND} 
      -DPARA_SRC_DIR=${PARA_SRC_DIR}
      -DPARA_OUTPUT_DIR=${PARA_OUTPUT_DIR}
      -P ${EXAMPLE_SRC_DIR}/example.cmake
      DEPENDS ${EXAMPLE_EXE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
      COMMENT "Generating project examples"
      VERBATIM)
endif()

