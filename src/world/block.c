#include "block.h"

block* block_new(enum block_type type, float pos[3]) {
    block *b = malloc(sizeof(block));
    b->type = type;
    b->pos[0] = pos[0];
    b->pos[1] = pos[1];
    b->pos[2] = pos[2];

    return b;
}

void block_destroy(block* b) {
    free(b);
}

//---------
 
unsigned int BLOCK_INDICES_COUNT = 36;
unsigned int BLOCK_VERTICES_COUNT = 24;

unsigned int BLOCK_VERTICES_SIZE = 3 * 24 * sizeof(float);
unsigned int BLOCK_INDICES_SIZE = 36 * sizeof(unsigned int);

float BLOCK_VERTICES_NORMALS[] = {
    // Right face
    1, 0, 0,

    // Left face
    -1, 0, 0,

    // Front face
    0, 0, 1,

    // Back face
    0, 0, -1,

    // Top face
    0, 1, 0,

    // Bottom face
    0, -1, 0
};

float BLOCK_VERTICES_POS[] = {
    // Right face
    1, 0, 1,    // 0
    1, 0, 0,    // 1
    1, 1, 0,    // 2
    1, 1, 1,    // 3

    // Left face
    0, 0, 0,    // 4
    0, 0, 1,    // 5
    0, 1, 1,    // 6
    0, 1, 0,    // 7

    // Front face
    0, 0, 1,    // 8
    1, 0, 1,    // 9
    1, 1, 1,    // 10
    0, 1, 1,    // 11

    // Back face
    1, 0, 0,    // 12
    0, 0, 0,    // 13
    0, 1, 0,    // 14
    1, 1, 0,    // 15

    // Top face
    0, 1, 1,    // 16
    1, 1, 1,    // 17
    1, 1, 0,    // 18
    0, 1, 0,    // 19

    // Bottom face
    1, 0, 1,    // 20
    0, 0, 1,    // 21
    0, 0, 0,    // 22
    1, 0, 0,    // 23
};

unsigned int BLOCK_INDICES[] = {
    // Right face
    0, 1, 2,
    0, 2, 3,

    // Left face
    4, 5, 6,
    4, 6, 7,

    // Front face
    8, 9, 10,
    8, 10, 11,

    // Back face 
    12, 13, 14,
    12, 14, 15,

    // Top face
    16, 17, 18,
    16, 18, 19,

    // Bottom face
    20, 21, 22,
    20, 22, 23
};

unsigned int RIGHT_FACE_INDICES[] = {
    0, 1, 2,
    0, 2, 3,
};

unsigned int LEFT_FACE_INDICES[] = {
    4, 5, 6,
    4, 6, 7,
};

unsigned int FRONT_FACE_INDICES[] = {
    8, 9, 10,
    8, 10, 11,
};

unsigned int BACK_FACE_INDICES[] = {
    12, 13, 14,
    12, 14, 15,
};

unsigned int TOP_FACE_INDICES[] = {
    16, 17, 18,
    16, 18, 19,
};

unsigned int BOTTOM_FACE_INDICES[] = {
    20, 21, 22,
    20, 22, 23
};
