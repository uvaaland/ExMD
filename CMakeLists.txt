cmake_minimum_required(VERSION 2.8)

# Options. Turn on with 'cmake -Dtest=ON -Dstyle=ON'.
option(test "Build all tests." OFF) 
option(style "Add Google C++ Style check." OFF)


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
if (test OR style)
  add_subdirectory(test)
  enable_testing()
  add_test(NAME UnitTests COMMAND runUnitTests)
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
             ${TEST_FILES}
    )
  endif()
endif()
