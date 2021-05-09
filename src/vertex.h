/*
A header file to contain the definition of a vertex struct
that contains position (in 2D) and colour
*/

#pragma once
#include <GL/glew.h>

struct Position
{
    float x;
    float y;
};

struct Colour
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct Vertex
{
    // Structs inside of a struct (composition)
    // Position of the vertex
    Position position;
    // Use just one byte to store each colour (0-255)
    // Red, Green, Blue and alpha
    Colour colour;
    // The Vertex struct needs to have a multiple of 4 bytes for alignment
};
