#include "sprite.h"

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
    float vertex_data[12];

    // First triangle
    vertex_data[0] = x + width;
    vertex_data[1] = y + height;
    vertex_data[2] = x;
    vertex_data[3] = y + height;
    vertex_data[4] = x;
    vertex_data[5] = y;
    // Second Triangle
    vertex_data[6] = x;
    vertex_data[7] = y;
    vertex_data[8] = x + width;
    vertex_data[9] = y;
    vertex_data[10] = x + width;
    vertex_data[11] = y + height;

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    // Upload the buffer to the gpu
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
    // Unbind buffer (bind to 0), for safety
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}