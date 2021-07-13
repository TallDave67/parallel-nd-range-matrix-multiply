cmake_minimum_required(VERSION 3.16)
project(nd-range-matrix-multiply)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(nd-range-matrix-multiply
  nd-range-matrix-multiply.cpp
)

target_compile_options(nd-range-matrix-multiply PRIVATE 
  -std=c++20 -stdlib=libstdc++
)

