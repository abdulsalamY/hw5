cmake_minimum_required(VERSION 3.15)
project(hw5)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw5 abstract_class.cpp abstract_class.hpp utilities.cpp utilities.hpp BoolManager.cpp BoolManager.hpp local_vars.cpp local_vars.hpp handler.cpp handler.hpp StatementManager.cpp StatementManager.hpp FunctionManager.cpp FunctionManager.hpp)