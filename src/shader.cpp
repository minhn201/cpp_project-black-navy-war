#include "graphics/shader.hpp"


Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) : shader_id_(0), vertex_shader_(vertexShader), fragment_shader_(fragmentShader) {
    shader_id_ = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(shader_id_);
}

void Shader::Bind() const {
    glUseProgram(shader_id_);
}

void Shader::UnBind() const {
    glUseProgram(0);
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name) {
    int location = glGetUniformLocation(shader_id_, name.c_str());
    if (location == -1) {
        std::cout << "Warning uniform name does not exist in shader\n";
    }
    return location;
}