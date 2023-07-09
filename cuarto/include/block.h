#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>

extern float BLOCK_VERTICES[];
extern unsigned int BLOCK_INDICES[];

extern unsigned int BLOCK_VERTICES_SIZE;
extern unsigned int BLOCK_INDICES_SIZE;

extern unsigned int BLOCK_INDICES_COUNT;

#define GRASS 0
#define DIRT 1
#define STONE 2

typedef struct block {
    unsigned int id;
    float pos[3];
} block;

block* block_new(unsigned int id, float pos[3]);

#endif
