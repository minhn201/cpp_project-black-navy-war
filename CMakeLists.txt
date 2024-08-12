cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(cpp_black_navy_war LANGUAGES CXX)

# Get required packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Add include directories containing header files
include_directories(include)

set(IMGUI_DIR "external/imgui")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)


add_executable(black_navy_war 
    app/application.cpp 
    src/graphics/renderer.cpp 
    src/graphics/vertex_buffer.cpp 
    src/graphics/index_buffer.cpp
    src/graphics/shader.cpp
    src/logics/Unit.cpp
    src/logics/naval_base.cpp
    src/logics/resources.cpp
    src/logics/game.cpp
    ${IMGUI_SOURCES})

target_include_directories(black_navy_war PRIVATE 
                            ${IMGUI_DIR}
                            include)

target_link_libraries(black_navy_war 
    glfw 
    OpenGL::GL 
    GLEW::GLEW 
    dl  
)

# Install the black_navy_war program.
install(TARGETS black_navy_war DESTINATION bin)

# Install the demo script.
install(PROGRAMS demo DESTINATION bin)