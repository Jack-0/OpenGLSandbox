//
// Created by jack on 09/05/2020.
//

#ifndef OPENGLSANDBOX_SHADER_H
#define OPENGLSANDBOX_SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/matrix.hpp>


class Shader
{
public:
    // program ID
    unsigned int program_id;
    // constructor reads in shader file paths
    Shader(const char* vertexPath, const char* fragmentPath);
    // use shader
    void use();
    // utility
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, float value) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    unsigned int compileShader(unsigned int type, std::string& source);

};


#endif //OPENGLSANDBOX_SHADER_H
