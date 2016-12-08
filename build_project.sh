#!/bin/bash
function header {
    echo
    echo "##############################################"
    echo "# $1                                          "
    echo "##############################################"
    echo
}


# Stop script if any command fails
set -e

# Delete build directory if it exists
if [ -d "build" ]; then
    rm -rf ./build
fi

# Create and change to build directory
mkdir build && cd ./build

# CMake with testing
header "CMAKE WITH TESTING AND STYLE CHECK"
cmake -Dtest=ON -Dstyle=ON ..

# Execute Makefile
header "EXECUTE MAKEFILE"
make

# Run tests
header "RUN TESTS"
make test

# Create documentation
header "CREATE DOCUMENTATION"
make doc
