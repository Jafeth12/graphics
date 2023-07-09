#ifndef BLOCKMESH_H
#define BLOCKMESH_H

#include <glad/glad.h>
#include <cglm/cglm.h>

#include "block.h"

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ib.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct blockmesh {
    block *block;
    vao *vao;
    vbo *vbo;
    ib *ib;
} blockmesh;

blockmesh* bmesh_new(block *b);

blockmesh* bmesh_new_block(unsigned int id, float pos[3]);

void bmesh_draw(blockmesh *bm, shader *s);

#endif
