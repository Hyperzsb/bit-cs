cmake_minimum_required(VERSION 3.15)
project(exp_15)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp_15 main.cpp vehicle.h plane.cpp plane.h ship.cpp ship.h car.cpp car.h)