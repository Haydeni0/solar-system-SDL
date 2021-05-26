#include "imageLoader.h"
#include "GLTexture.h"
#include "picopng.h"
#include "IOManager.h"
#include "errors.h"

GLTexture ImageLoader::loadPNG(std::string filepath)
{
    GLTexture texture{};

    std::vector<unsigned char> out;
    std::vector<unsigned char> in;
    unsigned long width, height;

    // Read theh png file to buffer
    if (IOManager::readFileToBuffer(filepath, in) == false)
    {
        fatalError("Failed to load PNG file to buffer");
    }

    int error_code = decodePNG(out, width, height, &(in[0]), in.size());

    // If this fails, return an error and look up code on lodepng
    if (error_code != 0)
    {
        fatalError("decodePNG failed with error: " + std::to_string(error_code));
    }

    // Generate a texture id
    glGenTextures(1, &texture.id);
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture.id);
    // Upload
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0])); // GL_UNSIGNED_BYTE is the same as a char
    // Parameters for the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter for mipmapping, use linear interp
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // Generate mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}