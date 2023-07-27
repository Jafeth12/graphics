#include "block.h"

block* block_new(enum block_type type, float pos[3]) {
    block *b = malloc(sizeof(block));
    b->type = type;
    b->pos[0] = pos[0];
    b->pos[1] = pos[1];
    b->pos[2] = pos[2];

    return b;
}

//---------
 
unsigned int BLOCK_INDICES_COUNT = 36;
unsigned int BLOCK_VERTICES_COUNT = 24;

unsigned int BLOCK_VERTICES_SIZE = 24 * sizeof(float);
unsigned int BLOCK_INDICES_SIZE = 36 * sizeof(unsigned int);

float BLOCK_VERTICES[] = {
    1, 0, 0,        // 0 -> North east at Y=0 (arriba derecha)
    1, 0, 1,        // 1 -> South east at Y=0 (abajo derecha)
    0, 0, 1,        // 2 -> South west at Y=0 (abajo izquierda)
    0, 0, 0,        // 3 -> North west at Y=0 (arriba izquierda)

    // same but Y=1
    1, 1, 0,        // 4
    1, 1, 1,        // 5
    0, 1, 1,        // 6
    0, 1, 0,        // 7
};

unsigned int BLOCK_INDICES[] = {
    // Right face
    1, 0, 4,
    1, 4, 5,

    // Left face
    3, 2, 6,
    3, 6, 7,

    // Front face
    2, 1, 5,
    2, 5, 6,

    // Back face 
    0, 3, 7,
    0, 7, 4,

    // Top face
    6, 5, 4,
    6, 4, 7,

    // Bottom face
    1, 2, 3,
    1, 3, 0,
};

unsigned int RIGHT_FACE_INDICES[] = {
    0, 1, 4,
    1, 5, 4
};

unsigned int LEFT_FACE_INDICES[] = {
    3, 2, 6,
    3, 6, 7
};


unsigned int FRONT_FACE_INDICES[] = {
    2, 1, 5,
    2, 5, 6
};

unsigned int BACK_FACE_INDICES[] = {
    0, 3, 7,
    0, 7, 4
};

unsigned int TOP_FACE_INDICES[] = {
    6, 5, 4,
    6, 4, 7
};

unsigned int BOTTOM_FACE_INDICES[] = {
    1, 2, 3,
    1, 3, 0
};

