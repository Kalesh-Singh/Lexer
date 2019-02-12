cmake_minimum_required(VERSION 3.13)
project(ThompsonVM)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThompsonVM main.cpp helper.h types.h types.cpp helper.cpp thompson_vm.h thompson_vm.cpp tests.cpp)