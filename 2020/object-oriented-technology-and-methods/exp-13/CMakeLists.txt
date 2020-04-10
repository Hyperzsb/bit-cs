cmake_minimum_required(VERSION 3.15)
project(exp_13)

set(CMAKE_CXX_STANDARD 14)

add_executable(exp_13 main.cpp employee.cpp employee.h manager.cpp manager.h technician.cpp technician.h salesman.cpp salesman.h salesmanager.cpp salesmanager.h)