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
    0, 0, 0,        // 0 -> North west at Y=0 (arriba izquierda)
    1, 0, 0,        // 1 -> North east at Y=0 (arriba derecha)
    1, 1, 0,        // 2 -> North east at Y=1 (arriba derecha)
    0, 1, 0,        // 3 -> North west at Y=1 (arriba izquierda)

    0, 0, 1,        // 4 -> South west at Y=0 (abajo izquierda)
    1, 0, 1,        // 5 -> South east at Y=0 (abajo derecha)
    1, 1, 1,        // 6 -> South east at Y=1 (abajo derecha)
    0, 1, 1,        // 7 -> South west at Y=1 (abajo izquierda)
};

unsigned BLOCK_INDICES[] = {
    1, 0, 3, 1, 3, 2, // north (-z)
    4, 5, 6, 4, 6, 7, // south (+z)
    5, 1, 2, 5, 2, 6, // east (+x)
    0, 4, 7, 0, 7, 3, // west (-x)
    2, 3, 7, 2, 7, 6, // top (+y)
    5, 4, 0, 5, 0, 1, // bottom (-y)
};

unsigned int RIGHT_FACE_INDICES[] = {
    5, 1, 2, 5, 2, 6
};

unsigned int LEFT_FACE_INDICES[] = {
    0, 4, 7, 0, 7, 3
};

unsigned int FRONT_FACE_INDICES[] = {
    4, 5, 6, 4, 6, 7
};

unsigned int BACK_FACE_INDICES[] = {
    1, 0, 3, 1, 3, 2
};

unsigned int TOP_FACE_INDICES[] = {
    2, 3, 7, 2, 7, 6
};

unsigned int BOTTOM_FACE_INDICES[] = {
    5, 4, 0, 5, 0, 1
};

