#!/bin/bash
#
# CLEAN BUILD
#
#
rm -rf build && mkdir build && cd build
#
# RELEASE BUILD & INSTALL
#
mkdir Release && cd Release
#
# Resolve dependencies using conan
#
conan install ../.. -s build_type=Release
#
# CMake generate, build and install
#
cmake ../.. -DCMAKE_BUILD_TYPE=Release
cmake --build   . --verbose
cmake --install . --verbose
cd ..

#
# DEBUG BUILD & INSTALL
#
mkdir Debug && cd Debug
#
# Resolve dependencies using conan
#
conan install ../.. -s build_type=Debug
#
# CMake generate, build and install
#
cmake ../.. -DCMAKE_BUILD_TYPE=Debug
cmake --build   . --verbose
cmake --install . --verbose
cd ../..
