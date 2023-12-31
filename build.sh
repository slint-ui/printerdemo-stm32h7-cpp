#!/bin/bash

set -o nounset 
set -o errexit

cmake -S . -B Debug -DCMAKE_TOOLCHAIN_FILE=${PWD}/cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Debug -GNinja
# Check the exit status of the last command
if [ $? -eq 0 ]; then
    echo "CMake config was successful."
else
    echo "CMake config failed."
    exit 1
fi

cmake --build Debug
