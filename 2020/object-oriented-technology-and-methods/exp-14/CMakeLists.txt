cmake_minimum_required(VERSION 3.15)
project(exp_14)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp_14 main.cpp employee.cpp employee.h technician.cpp technician.h manager.cpp manager.h salesman.cpp salesman.h salesmanager.cpp salesmanager.h)