#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"

#include <stdlib.h>
#include <cglm/cglm.h>

#define CHUNK_SIZE 8
#define CHUNK_HEIGHT 64

typedef struct chunk {
    block blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
    float offset[2];
    unsigned int solid_blocks_count;
    unsigned seed;
} chunk;

chunk* chunk_new(unsigned seed, int offset_x, int offset_z);

block chunk_get_block(chunk* c, int x, int y, int z);

char chunk_set_block(chunk* c, int x, int y, int z, enum block_type type);

char chunk_does_pos_intersect(chunk* c, ivec3 pos);

void chunk_destroy(chunk* c);

#define chunk_for_each_block() \
    for (int i = 0; i < CHUNK_SIZE; i++) \
        for (int j = 0; j < CHUNK_HEIGHT; j++) \
            for (int k = 0; k < CHUNK_SIZE; k++)

#endif
