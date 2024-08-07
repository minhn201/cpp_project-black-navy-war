#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "graphics/renderer.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/index_buffer.hpp"
#include "graphics/shader.hpp"


int main() {

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 800, "cpp Black Navy War", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    float positions[] = {
        -1.0f, -0.5f,
        -0.7f, -0.5f,
        -1.0f, 0.5f,

        0.7f, -0.5f,
        1.0f, -0.5f,
        1.0f, 0.5f,
    };

    float background_color[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, 1.0f
    };

    float sea_line[] = {
        -1.0f, 0.0f,
        1.0f, 0.0f
    };


    unsigned int indices[] = {0, 1, 2, 3, 4, 5};

    unsigned int background_indices[] = {0, 1, 2, 2, 3, 0};

    unsigned int sea_line_indices[] = {0, 1};

    // Set up arrays and buffers for bases
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    VertexBuffer vb(positions, sizeof(positions));

    glEnableVertexAttribArray(0);

    IndexBuffer ib(indices, 6);

    VertexBuffer background_color_vb(background_color, sizeof(background_color));

    IndexBuffer background_color_ib(background_indices, 6);

    VertexBuffer sea_line_vb(sea_line, sizeof(sea_line));

    IndexBuffer sea_line_ib(sea_line_indices, 4);


    const std::string vertexShader = // Initialize Vertex Shaders
        R"(#version 330 core
        layout(location = 0) in vec4 position;
        void main()
        {
           gl_Position = position;
        })";

    const std::string fragmentShader = // Initialize Fragment Shaders
        R"(#version 330 core
        layout(location = 0) out vec4 color;

        uniform vec4 u_Color;

        void main()
        {
           color = u_Color;
        })";

    // Create and compile shaders
    Shader shader(vertexShader, fragmentShader);
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vao);

        shader.SetUniform4f("u_Color", 0.5f, 0.5f, 0.55f, 1.0f); // Draw background
        background_color_ib.Bind();
        background_color_vb.Bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        shader.SetUniform4f("u_Color", 0.1f, 0.1f, 0.1f, 1.0f); // Draw bases
        vb.Bind();
        ib.Bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        shader.SetUniform4f("u_Color", 0.1f, 0.1f, 0.1f, 1.0f); // Draw bases
        sea_line_ib.Bind();
        sea_line_vb.Bind();
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, nullptr);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
