#version 460
// The fragment shader operates on each pixel in a given polygon

// Take in the colour data from the vertex shader
in vec2 fragment_position;
in vec4 fragment_colour;

// This is the 4 component float vector that gets outputted to the screen for each pixel
out vec4 colour;

uniform float time;

void main()
{
    // Hardcode the colour to read
    colour=vec4(
        fragment_colour.r*(cos(fragment_position.x*4+time)+1)*.5,
        fragment_colour.g*(cos(fragment_position.y*8+time)+1)*.5,
        fragment_colour.b*(cos(fragment_position.x*2+time)+1)*.5,
        fragment_colour.a
    );
}