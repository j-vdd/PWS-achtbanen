#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& shaderPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(shaderPath + ".vert");
        fShaderFile.open(shaderPath + ".frag");
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLint success;
    char infoLog[512];

    m_Program = glCreateProgram();

    //vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glAttachShader(m_Program, vertexShader);

    //fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glAttachShader(m_Program, fragmentShader);

    //link program
    glLinkProgram(m_Program);

    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //get all active uniforms
    GLint uniformCount;
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &uniformCount);

    GLint size;
    GLenum type;
    const GLsizei bufSize = 32;
    GLchar name[bufSize];
    GLsizei length;
    for (GLint i = 0; i < uniformCount; i++)
    {
        glGetActiveUniform(m_Program, i, bufSize, &length, &size, &type, name);
        GLint location = glGetUniformLocation(m_Program, name);

        m_UniformLocations[name] = location;
    }
}
Shader::~Shader()
{
    glDeleteProgram(m_Program);
}

GLint Shader::location(const std::string& name) const {
    if (m_UniformLocations.contains(name)) {
        return m_UniformLocations.at(name);
    }
    return -1;
}

void Shader::use() const
{
    glUseProgram(m_Program);
}

void Shader::setUniform(const std::string& name, float v0) const
{
    glProgramUniform1f(m_Program, location(name), v0);
}

void Shader::setUniform(const std::string& name, float v0, float v1) const
{
    glProgramUniform2f(m_Program, location(name), v0, v1);
}

void Shader::setUniform(const std::string& name, float v0, float v1, float v2) const
{
    glProgramUniform3f(m_Program, location(name), v0, v1, v2);
}

void Shader::setUniform(const std::string& name, float v0, float v1, float v2, float v3) const
{
    glProgramUniform4f(m_Program, location(name), v0, v1, v2, v3);
}

void Shader::setUniform(const std::string& name, const Vec2& value) const
{
    glProgramUniform2fv(m_Program, location(name), 1, (GLfloat*)&value);
}

void Shader::setUniform(const std::string& name, const Vec3& value) const
{
    glProgramUniform3fv(m_Program, location(name), 1, (GLfloat*)&value);
}

void Shader::setUniform(const std::string& name, const Vec4& value) const
{
    glProgramUniform4fv(m_Program, location(name), 1, (GLfloat*)&value);
}

void Shader::setUniform(const std::string& name, const Mat2& value) const
{
    glProgramUniformMatrix2fv(m_Program, location(name), 1, GL_FALSE, (GLfloat*)&value);
}

void Shader::setUniform(const std::string& name, const Mat3& value) const
{
    glProgramUniformMatrix3fv(m_Program, location(name), 1, GL_FALSE, (GLfloat*)&value);
}

void Shader::setUniform(const std::string& name, const Mat4& value) const
{
    glProgramUniformMatrix4fv(m_Program, location(name), 1, GL_FALSE, (GLfloat*)&value);
}
