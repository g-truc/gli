#!/bin/bash

export CC=gcc
export CXX=g++

# make clean build dir
[ -d build ] && rm -r build && mkdir build

# prep the sources
cmake -S . -B build

# run build
cmake --build build -j4 -v

# run tests
cd build && ctest
cd ../
