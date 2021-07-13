#!/bin/sh
export CC=/usr/bin/clang-11
export CXX=/opt/intel/oneapi/compiler/2021.3.0/linux/bin/dpcpp

cd build
cmake ../
make VERBOSE=1
