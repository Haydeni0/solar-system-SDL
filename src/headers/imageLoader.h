#pragma once

#include "GLTexture.h"
#include <string>

// Load images as textures
class ImageLoader
{
public:
    GLTexture loadPNG(std::string filepath);
};