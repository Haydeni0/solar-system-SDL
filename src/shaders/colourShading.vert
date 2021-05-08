#version 460

// Input data from the VBO (vertex buffer object). Each vertex is 2 floats in the vec2
in vec2 vertex_position;

void main()
{   
    // Set the x,y position on the screen
     gl_Position.xy = vertex_position;
     // The z position is zero since we are in 2D
     gl_Position.z = 0.0; // No z coord
     // Don't care about w for now, set to default 1
     gl_Position.w = 1.0; 
}