#version 460
// The fragment shader operates on each pixel in a given polygon

// This is the 3 component float vector that gets outputted to the screen for each pixel
out vec3 colour;

void main()
{
    // Hardcode the colour to read
    colour=vec3(1.,0.,0.);
}