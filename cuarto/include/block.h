#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>

extern float BLOCK_VERTICES[];
extern unsigned int BLOCK_INDICES[];

extern unsigned int BLOCK_VERTICES_SIZE;
extern unsigned int BLOCK_INDICES_SIZE;

extern unsigned int BLOCK_INDICES_COUNT;
extern unsigned int BLOCK_VERTICES_COUNT;

enum block_type {
    GRASS = 0,
    DIRT,
    STONE
};

typedef struct block {
    enum block_type type;
    float pos[3];
} block;

block* block_new(enum block_type type, float pos[3]);

#endif
