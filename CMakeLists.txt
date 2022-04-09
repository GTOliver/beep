cmake_minimum_required(VERSION 3.21)
project(beep)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(beep)

option(BUILD_EXAMPLES "Build some test example apps")

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
