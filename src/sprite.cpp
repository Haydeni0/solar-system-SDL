#include "sprite.h"
#include "vertex.h"

#include <cstddef>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
    // Clean up the buffer when destructed
    if (_vboID != 0)
        glDeleteBuffers(1, &_vboID);
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // If the vbo is uninitialised (0), make a buffer
    if (_vboID == 0)
        glGenBuffers(1, &_vboID);

    // Make data to upload
    Vertex vertex_data[6];

    // First triangle
    vertex_data[0].position.x = x + width;
    vertex_data[0].position.y = y + height;

    vertex_data[1].position.x = x;
    vertex_data[1].position.y = y + height;

    vertex_data[2].position.x = x;
    vertex_data[2].position.y = y;
    // Second Triangle
    vertex_data[3].position.x = x;
    vertex_data[3].position.y = y;

    vertex_data[4].position.x = x + width;
    vertex_data[4].position.y = y;

    vertex_data[5].position.x = x + width;
    vertex_data[5].position.y = y + height;

    // Set colours for each vertex
    for (int i{0}; i < 6; i++)
    {
        vertex_data[i].colour.r = 255;
        vertex_data[i].colour.g = 0;
        vertex_data[i].colour.b = 255;
        vertex_data[i].colour.a = 255;
    }

    vertex_data[1].colour.r = 0;
    vertex_data[1].colour.g = 0;
    vertex_data[1].colour.b = 255;
    vertex_data[1].colour.a = 255;

    vertex_data[4].colour.r = 0;
    vertex_data[4].colour.g = 255;
    vertex_data[4].colour.b = 0;
    vertex_data[4].colour.a = 255;

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    // Upload the buffer to the gpu
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    // Unbind buffer (bind to 0), for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    // Bind the buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Tell opengl that we want to use the first attribute array
    glEnableVertexAttribArray(0);

    // This is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    // This is the colour attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

    // Draw the 6 vertices on the screen
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Disable the vertex attrib array (this is not optional)
    glDisableVertexAttribArray(0);

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}