cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(black_navy_war LANGUAGES CXX)

# Get required packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Add include directories containing header files
include_directories(include)

add_executable(black_navy_war application.cpp 
    src/renderer.cpp 
    src/vertex_buffer.cpp 
    src/index_buffer.cpp)

target_link_libraries(black_navy_war glfw OpenGL::GL GLEW::GLEW)
