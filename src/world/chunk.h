#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#include <stdlib.h>
#include <cglm/cglm.h>

#define CHUNK_SIZE 16

typedef struct chunk {
    block* blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    float offset[2];
    unsigned int solid_blocks_count;
} chunk;

chunk* chunk_new(int offset_x, int offset_z);

block* chunk_get_block(chunk* c, int x, int y, int z);

char chunk_set_block(chunk* c, int x, int y, int z, enum block_type type);

void chunk_destroy(chunk* c);

#endif
