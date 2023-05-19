#ifndef TRIANGLE_H
#define TRIANGLE_H

// TODO add colors to the triangle

#include <glad/glad.h>

#include <shader.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct triangle {
    unsigned int VBO;
    unsigned int VAO;
    float scale;
    float color[3];
} triangle;

triangle* tri_new(float red, float green, float blue, float scale);

void tri_draw(triangle* tri, shader* sh);

#endif // !TRIANGLE_H
