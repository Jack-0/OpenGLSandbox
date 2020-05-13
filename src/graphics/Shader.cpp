//
// Created by jack on 09/05/2020.
//

#include "Shader.h"

Shader::Shader(const char *vertexPath, const char* fragmentPath)
{
    // get shader source code
    // retrieve the vertex and fragment file paths
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertFile;
    std::ifstream fragFile;
    // ensure std::ifstream objects can throw exceptions
    vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vertFile.open(vertexPath);
        fragFile.open(fragmentPath);
        // read file buffer into strings
        std::stringstream vertStream, fragStream;
        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();
        // close files
        vertFile.close();
        fragFile.close();
        // convert streams into strings
        vertCode = vertStream.str();
        fragCode = fragStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_READ_ERROR" << std::endl;
    }

    // compile shaders source code
    unsigned int vert_id = compileShader(GL_VERTEX_SHADER, vertCode);
    unsigned int frag_id = compileShader(GL_FRAGMENT_SHADER, fragCode);

    // attach shaders to program
    program_id = glCreateProgram();
    glAttachShader(program_id, vert_id);
    glAttachShader(program_id, frag_id);
    glLinkProgram(program_id);
    glValidateProgram(program_id);

    // clean up
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
}

unsigned int Shader::compileShader(unsigned int type, std::string &source)
{
    // shader id
    unsigned int shader_id = glCreateShader(type);
    // convert string to c string
    const char* src = source.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);

    // error handling
    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); // allocate on stack dynamically
        glGetShaderInfoLog(shader_id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n" << message << std::endl;
        glDeleteShader(shader_id);
        return 0;
    }
    return shader_id;
}

void Shader::use()
{
    glUseProgram(program_id);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program_id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

