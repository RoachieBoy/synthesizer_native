cmake_minimum_required(VERSION 3.26)
project(synthesizer_native C)

set(CMAKE_C_STANDARD 17)

add_library(shared_synthesizer_native SHARED library.c)

add_library(synthesizer_native STATIC library.c)

if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS=1)
endif ()
