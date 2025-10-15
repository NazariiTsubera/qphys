cmake_minimum_required(VERSION 3.11)
project(qphys_renderer LANGUAGES C CXX)

# Let older subprojects (GLAD) configure under CMake 4.x
# (same effect as passing -DCMAKE_POLICY_VERSION_MINIMUM=3.5)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)

# ---------------------------
# Sources
# ---------------------------
file(GLOB_RECURSE RENDERER_SOURCES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(qphys_renderer ${RENDERER_SOURCES})
target_compile_features(qphys_renderer PRIVATE cxx_std_20)

# Your renderer headers (if any)
target_include_directories(qphys_renderer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link your core lib from ../core
target_link_libraries(qphys_renderer PRIVATE qphys_core)

# ---------------------------
# GLFW
# ---------------------------
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.9
)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)
target_link_libraries(qphys_renderer PRIVATE glfw)

# ---------------------------
# GLAD (use its own CMake to avoid missing-file errors)
# ---------------------------
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)
# GLAD exports target 'glad'
target_link_libraries(qphys_renderer PRIVATE glad)

# ---------------------------
# OpenGL
# ---------------------------
if(APPLE)
    target_link_libraries(qphys_renderer PRIVATE
            "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-framework CoreVideo")
elseif(WIN32)
    target_link_libraries(qphys_renderer PRIVATE opengl32)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(qphys_renderer PRIVATE OpenGL::GL)
endif()

# ---------------------------
# Dear ImGui (wrap upstream into a target)
# ---------------------------
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.0
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui PUBLIC glfw)
if(APPLE)
    target_link_libraries(imgui PUBLIC "-framework OpenGL")
elseif(WIN32)
    target_link_libraries(imgui PUBLIC opengl32)
else()
    target_link_libraries(imgui PUBLIC OpenGL::GL)
endif()

target_link_libraries(qphys_renderer PRIVATE imgui)
