#include "GLSLProgram.h"
#include "errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programID{0}, _vertex_shaderID{0}, _fragment_shaderID{0}, _num_attributes{0}
{
}
GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string &vertex_shader_filepath,
                                 const std::string &fragment_shader_filepath)
{
    // Get a program object
    _programID = glCreateProgram();

    _vertex_shaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertex_shaderID == 0)
    {
        fatalError("Vertex shader failed to be created");
    }
    _fragment_shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragment_shaderID == 0)
    {
        fatalError("Fragment shader failed to be created");
    }

    compileShader(vertex_shader_filepath, _vertex_shaderID);
    compileShader(fragment_shader_filepath, _fragment_shaderID);
}

void GLSLProgram::compileShader(const std::string &filepath, GLuint id)
{

    std::ifstream shader_file(filepath);
    if (shader_file.fail())
    {
        perror(filepath.c_str());
        fatalError("Failed to open " + filepath);
    }

    // Read the vertex shader file
    std::string file_contents{""};
    std::string line;
    while (std::getline(shader_file, line))
    {
        file_contents += line + "\n";
    }
    shader_file.close();

    // Compile the vertex shader
    const GLchar *contents_ptr{file_contents.c_str()};
    glShaderSource(id, 1, &contents_ptr, nullptr);
    glCompileShader(id);

    // Error checking for the GLSL file
    GLint is_compiled{0};
    glGetShaderiv(id, GL_COMPILE_STATUS, &is_compiled);

    if (is_compiled == GL_FALSE)
    {
        GLint max_length{0};
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> error_log(max_length);
        glGetShaderInfoLog(id, max_length, &max_length, &error_log[0]);
        glDeleteShader(id); // Don't leak the shader

        // Provide the infolog and exit with failure
        // Since error_log is a vector of characters, we can get printf to interpret
        // it as a c string by passing the address of the first element
        std::printf("%s\n", &(error_log[0]));
        fatalError("Shader " + filepath + " failed to compile");
    }
}

void GLSLProgram::linkShaders()
{

    // Attach our shaders to our program
    glAttachShader(_programID, _vertex_shaderID);
    glAttachShader(_programID, _fragment_shaderID);

    // Link our program
    glLinkProgram(_programID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint is_linked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&is_linked);
    if (is_linked == GL_FALSE)
    {
        GLint max_length = 0;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &max_length);

        // The maxLength includes the NULL character
        std::vector<GLchar> error_log(max_length);
        glGetProgramInfoLog(_programID, max_length, &max_length, &error_log[0]);

        // We don't need the program anymore.
        glDeleteProgram(_programID);
        // Don't leak shaders either.
        glDeleteShader(_vertex_shaderID);
        glDeleteShader(_fragment_shaderID);

        // Use the infoLog as you see fit.
        std::printf("%s\n", &(error_log[0]));
        fatalError("Shaders failed to link");

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(_programID, _vertex_shaderID);
    glDetachShader(_programID, _fragment_shaderID);
    // Also delete to free up resources
    glDeleteShader(_vertex_shaderID);
    glDeleteShader(_fragment_shaderID);
}

void GLSLProgram::addAttribute(const std::string &attribute_name)
{
    // For later versions use
    //      layout(location = '''Attribute number''') in vec4 a_vec;
    // in the shader file?
    glBindAttribLocation(_programID, _num_attributes++, attribute_name.c_str());
}

void GLSLProgram::use()
{
    glUseProgram(_programID);
    // Enable each vertex attribute that we have bound
    for (int j{0}; j < _num_attributes; j++)
    {
        glEnableVertexAttribArray(j);
    }
}

void GLSLProgram::unuse()
{
    glUseProgram(0);
    // Disable each vertex attribute that we have bound
    for (int j{0}; j < _num_attributes; j++)
    {
        glDisableVertexAttribArray(j);
    }
}
