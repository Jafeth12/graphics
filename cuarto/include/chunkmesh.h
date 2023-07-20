#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "chunk.h"

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "ib.h"

#include <stdlib.h>

typedef struct chunkmesh {
    chunk* chunk;
    vao* vao;
    vbo* vbo;
    ib* ib;
} chunkmesh;

chunkmesh* cmesh_new(chunk* chunk);

chunkmesh* cmesh_new_chunk(unsigned offset_x, unsigned offset_y);

void cmesh_draw(chunkmesh* chunkmesh, shader* shader);

#endif
