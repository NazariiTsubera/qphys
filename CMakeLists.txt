cmake_minimum_required(VERSION 3.11)

project(Qphys
        VERSION 0.1.0
        DESCRIPTION "Quantum physics simulation engine"
        LANGUAGES CXX)

option(QPHYS_BUILD_RENDERER "Build renderer" ON)

add_subdirectory(core)
if (BUILD_RENDERER)
    add_subdirectory(renderer)
endif()