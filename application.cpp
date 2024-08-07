#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "graphics/renderer.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/index_buffer.hpp"


static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result != GL_TRUE) { // Doing some error handling
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type==GL_VERTEX_SHADER ? "Vertex Shader " : "Fragment Shader ") << message << '\n'; 
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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
    GLFWwindow* window = glfwCreateWindow(800, 800, "cpp Black Navy War", NULL, NULL);;

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    IndexBuffer ib(indices, 6);

    // Set up arrays and buffers for background
    unsigned int background_vao;
    glGenVertexArrays(1, &background_vao);
    glBindVertexArray(background_vao);

    VertexBuffer background_color_vb(background_color, sizeof(background_color));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    IndexBuffer background_color_ib(background_indices, 6);

    // Set up arrays and buffers for line
    unsigned int sea_line_vao;
    glGenVertexArrays(1, &sea_line_vao);
    glBindVertexArray(sea_line_vao);

    VertexBuffer sea_line_vb(sea_line, sizeof(sea_line));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    IndexBuffer sea_line_ib(sea_line_indices, 4);


    const std::string vertexShader =
        R"(#version 330 core
        layout(location = 0) in vec4 position;
        void main()
        {
           gl_Position = position;
        })";

    const std::string fragmentShader =
        R"(#version 330 core
        layout(location = 0) out vec4 color;

        uniform vec4 u_Color;

        void main()
        {
           color = u_Color;
        })";


    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 0.5f, 0.5f, 0.5f, 1.0f);

    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glUniform4f(location, 0.5f, 0.5f, 0.55f, 1.0f); // Draw background
        background_color_ib.Bind();
        glBindVertexArray(background_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glUniform4f(location, 0.1f, 0.1f, 0.1f, 1.0f); // Draw bases
        glBindVertexArray(vao);
        ib.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glUniform4f(location, 0.1f, 0.1f, 0.1f, 1.0f); // Draw bases
        glBindVertexArray(sea_line_vao);
        sea_line_ib.Bind();
        glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, nullptr);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
