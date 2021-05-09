#version 460
// The fragment shader operates on each pixel in a given polygon

// Take in the colour data from the vertex shader
in vec4 fragment_colour;

// This is the 4 component float vector that gets outputted to the screen for each pixel
out vec4 colour;

void main()
{
    // Hardcode the colour to read
    colour=fragment_colour;
}