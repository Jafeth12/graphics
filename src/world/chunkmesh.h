#ifndef CHUNKMESH_H
#define CHUNKMESH_H

#include "chunk.h"

#include <utils/shader.h>
#include <gfx/texture.h>
#include <gfx/vao.h>
#include <gfx/vbo.h>
#include <gfx/ib.h>

#include <stdlib.h>

typedef struct chunk_buffer {
    float* vertices;
    unsigned* indices;

    int vertex_count;
    int index_count;

    unsigned vertex_offset;
    unsigned index_offset;
} chunk_buffer;

typedef struct chunkmesh {
    chunk* chunk;
    vao vao;
    vbo vbo;
    ib ib;
    char is_meshed;
} chunkmesh;

chunkmesh* cmesh_new(chunk* chunk, chunkmesh*** chunks);

chunkmesh* cmesh_new_chunk(int offset_x, int offset_y, chunkmesh*** chunks);

chunkmesh* cmesh_new_chunk_no_mesh(int offset_x, int offset_z);

void cmesh_add_face(chunkmesh *cm, enum block_face face, unsigned *indices, unsigned initial_vertex_index, unsigned *index_offset);

void cmesh_update(chunkmesh *cm, chunkmesh*** chunks);

void cmesh_mesh(chunkmesh* cm, chunkmesh*** chunks);

void cmesh_draw(chunkmesh* chunkmesh, shader* shader);

void cmesh_destroy(chunkmesh* cm);

void cmesh_destroy_mesh(chunkmesh* cm);

#endif
