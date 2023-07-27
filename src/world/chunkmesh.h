#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "chunk.h"

#include <utils/shader.h>
#include <gfx/vao.h>
#include <gfx/vbo.h>
#include <gfx/ib.h>

#include <stdlib.h>

typedef struct chunkmesh {
    chunk* chunk;
    vao* vao;
    vbo* vbo;
    ib* ib;
} chunkmesh;

chunkmesh* cmesh_new(chunk* chunk);

chunkmesh* cmesh_new_chunk(unsigned offset_x, unsigned offset_y);

void cmesh_add_face(chunkmesh *cm, enum block_face face, int x, int y, int z);

void cmesh_draw(chunkmesh* chunkmesh, shader* shader);

#endif
