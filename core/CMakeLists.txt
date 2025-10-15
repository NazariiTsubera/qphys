cmake_minimum_required(VERSION 3.11)

file(GLOB_RECURSE CORE_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

add_library(qphys_core STATIC ${CORE_SOURCES}
        src/engine.cpp)

target_include_directories(qphys_core
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(qphys_core PRIVATE cxx_std_20)