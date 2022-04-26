cmake_minimum_required(VERSION 3.21)
project(beep)

set(CMAKE_CXX_STANDARD 17)

option(BEEP "Enable the BEEP macros. If OFF, the macros do nothing." ON)
option(BUILD_TESTS OFF)
option(BUILD_EXAMPLES OFF)

add_subdirectory(dependencies)
add_subdirectory(beep)
add_subdirectory(beeppp)
add_subdirectory(beep_macros)

add_library(beep::beep_macros ALIAS beep_macros)
add_library(beep::beep ALIAS beep)
add_library(beep::beeppp ALIAS beeppp)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
