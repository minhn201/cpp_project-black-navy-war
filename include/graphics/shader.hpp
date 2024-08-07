#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <GL/glew.h>

class Shader {
    private:
        unsigned int shader_id_;
        std::string vertex_shader_;
        std::string fragment_shader_;

    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);
        ~Shader();

        void Bind() const;
        void UnBind() const;
        
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    
    private:
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        int GetUniformLocation(const std::string& name);
};

#endif