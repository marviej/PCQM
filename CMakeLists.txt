cmake_minimum_required(VERSION 2.6)
project(PCQM)


if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /openmp /std:c++17")
endif(MSVC)

if (NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -fopenmp -std=c++17")
endif(NOT MSVC)

add_executable(PCQM pcqm.cpp main.cpp )

include_directories(eigen3/)

include_directories(include/)

install(TARGETS PCQM RUNTIME DESTINATION bin)
