cmake_minimum_required(VERSION 3.9)
project(InvoluteSpurGear)

set(CMAKE_CXX_STANDARD 11)

add_executable(InvoluteSpurGear main.cpp SpurGear.h utils/AngleUtils.h utils/AngleUtils.cpp utils/VectorUtils.h SpurGear.cpp utils/Pair.h)