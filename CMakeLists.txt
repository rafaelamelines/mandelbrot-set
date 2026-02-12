cmake_minimum_required(VERSION 3.10)
project(mandelbrot VERSION 0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

include_directories(${CMAKE_SOURCE_DIR}/vendor/glfw/include)

set(SDL_STATIC ON)
set(SDL_SHARED OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glad)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glfw)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glad
    glfw
)