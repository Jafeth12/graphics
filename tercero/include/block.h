#ifndef BLOCK_H
#define BLOCK_H

// TODO add colors to the triangle

#include <glad/glad.h>
#include <cglm/cglm.h>

#include <shader.h>

#include <stdio.h>
#include <stdlib.h>

extern float CUBE_VERTICES[];
extern unsigned int CUBE_INDICES[];

typedef struct block {
    GLuint VAO, VBO, EBO;
    float scale;
    vec3 pos;
    vec3 color;
} block;

block* block_new(float red, float green, float blue, float scale);

void block_draw(block* c, shader *sh);

void block_move_up(block *bl);

void block_move_down(block *bl);

#endif // !BLOCK_H
