#version 460

// Input data from the VBO (vertex buffer object). Each vertex is 2 floats in the vec2
in vec2 vertex_position;
in vec4 vertex_colour;

// Pass to the fragment shader
out vec2 fragment_position;
out vec4 fragment_colour;

void main()
{
    // Set the x,y position on the screen
    gl_Position.xy=vertex_position;
    // The z position is zero since we are in 2D
    gl_Position.z=0.;// No z coord
    // Indicate that the coordinates are normalised
    gl_Position.w=1.;
    
    fragment_position=vertex_position;
    
    // Set the fragment colour
    fragment_colour=vertex_colour;
}