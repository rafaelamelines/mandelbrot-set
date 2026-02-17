cmake_minimum_required(VERSION 3.10)
project(mandelbrot)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(${CMAKE_SOURCE_DIR}/vendor/stb)
include_directories(${CMAKE_SOURCE_DIR}/vendor/glfw/include)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glfw)

add_library(imgui)

target_include_directories(imgui PUBLIC ${CMAKE_SOURCE_DIR}/vendor/imgui)
target_sources(imgui PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    glfw
    imgui
)