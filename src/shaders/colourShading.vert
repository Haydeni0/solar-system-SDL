#version 130

in vec2 vertex_position;

void main()
{
     gl_Position.xy = vertex_position;
     gl_Position.z = 0.0; // No z coord
     gl_Position.w = 1.0; // Don't care about w for now, set to default 1
}