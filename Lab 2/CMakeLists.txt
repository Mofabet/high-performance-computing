cmake_minimum_required(VERSION 3.17)
project(Lab 2)

enable_language(Fortran)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI COMPONENTS Fortran REQUIRED)

add_executable(main.cpp)

target_link_libraries(???)