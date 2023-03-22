cmake_minimum_required(VERSION 3.24)
project(Complex)

set(CMAKE_CXX_STANDARD 17)

add_executable(Complex ComplexNumber.cpp ComplexNumber.h Mandelbrot.cpp)

#find_package(SFML COMPONENTS graphics window REQUIRED)
#target_link_libraries(Complex PRIVATE sfml-graphics sfml-window)