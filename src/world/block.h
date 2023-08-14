#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>

extern float BLOCK_VERTICES_POS[];
extern float BLOCK_VERTICES_NORMALS[];
extern float BLOCK_VERTICES_UV[];

extern unsigned int BLOCK_INDICES[];

extern unsigned int BLOCK_VERTICES_SIZE;
extern unsigned int BLOCK_INDICES_SIZE;

extern unsigned int BLOCK_INDICES_COUNT;
extern unsigned int BLOCK_VERTICES_COUNT;

extern unsigned int RIGHT_FACE_INDICES[];
extern unsigned int LEFT_FACE_INDICES[];
extern unsigned int FRONT_FACE_INDICES[];
extern unsigned int BACK_FACE_INDICES[];
extern unsigned int TOP_FACE_INDICES[];
extern unsigned int BOTTOM_FACE_INDICES[];

enum block_type {
    GRASS = 0,
    DIRT,
    STONE,
    AIR
};

enum block_face {
    TOP = 0,
    BOTTOM,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

typedef struct block {
    enum block_type type;
} block;

block* block_new(enum block_type type);

void block_destroy(block* b);

#endif
