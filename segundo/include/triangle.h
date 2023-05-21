#ifndef TRIANGLE_H
#define TRIANGLE_H

// TODO add colors to the triangle

#include <glad/glad.h>
#include <cglm/cglm.h>

#include <shader.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct triangle {
    unsigned int VBO;
    unsigned int VAO;
    float scale;
    vec3 color;
    vec3 pos;
} triangle;

triangle* tri_new(float red, float green, float blue, float scale);

void tri_draw(triangle* tri, shader* sh);

int tri_collision(triangle* tri1, triangle* tri2);

void tri_move_random(triangle* tri);

void tri_move_right(triangle* tri, float value);

void tri_move_left(triangle* tri, float value);

void tri_move_up(triangle* tri, float value);

void tri_move_down(triangle* tri, float value);

#endif // !TRIANGLE_H
