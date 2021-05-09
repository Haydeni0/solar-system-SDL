/*
A header file to contain the definition of a vertex struct
that contains position (in 2D) and colour
*/

#pragma once
#include <GL/glew.h>

struct Vertex
{
    // Structs inside of a struct
    struct Position
    {
        float x;
        float y;
    } position;
    // Use just one byte to store each colour (0-255)
    // Red, Green, Blue and alpha
    struct Colour
    {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } colour;
    // The Vertex struct needs to have a multiple of 4 bytes for alignment
};
