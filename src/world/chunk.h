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

chunk* chunk_new(unsigned offset_x, unsigned offset_z);

block* chunk_get_block(chunk* c, int x, int y, int z);

//void chunk_set_block(chunk* c, int x, int y, int z, block* b);

void chunk_destroy(chunk* c);

#endif