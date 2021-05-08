/*
File to deal with all the GLSL stuff
*/

#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();

    // Read and compile the GLSL shader files
    void compileShaders(const std::string &vertex_shader_filepath,
                        const std::string &fragment_shader_filepath);

    void linkShaders();

    void addAttribute(const std::string &attribute_name);

    void use();

    void unuse();

private:
    GLuint _programID;
    GLuint _vertex_shaderID;
    GLuint _fragment_shaderID;

    int _num_attributes;

    // Read and compile a GLSL shader file
    void compileShader(const std::string &filepath, GLuint id);
};