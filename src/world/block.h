#ifndef BLOCK_H
#define BLOCK_H

#include <stdlib.h>

extern float BLOCK_VERTICES_POS[];
extern float BLOCK_VERTICES_NORMALS[];
extern float BLOCK_VERTICES_UV[];
extern float BLOCK_VERTICES_BRIGHTNESS[];

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

struct uv {
    char u;
    char v;
};

extern struct uv BLOCK_UVS[];

enum block_type {
    GRASS = 0,
    DIRT,
    STONE,
    SAND,
    GRAVEL,
    BEDROCK,
    WOOD,
    BRICK,
    COBBLESTONE,
    AIR,
    OUT_OF_BOUNDS
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

void blocks_init();

void block_destroy(block* b);

#endif
