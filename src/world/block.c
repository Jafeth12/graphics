#include "block.h"

block* block_new(enum block_type type) {
    block *b = malloc(sizeof(block));
    b->type = type;

    return b;
}

void block_destroy(block* b) {
    free(b);
}

// AIR is the last block type, so it's the size of the array
// plus the uvs of an AIR block are non existent so its two birds in one stone even though its kinda ugly
struct uv BLOCK_UVS[AIR]; 

void blocks_init() {
    // GRASS = 0,
    // DIRT,
    // STONE,
    // SAND,
    // GRAVEL,
    // BEDROCK,
    // WOOD,
    // BRICK,
    // COBBLESTONE,
    // AIR

    // GRASS
    BLOCK_UVS[GRASS].u = 3; // original is 3
    BLOCK_UVS[GRASS].v = 15;

    // DIRT
    BLOCK_UVS[DIRT].u = 2;
    BLOCK_UVS[DIRT].v = 15;

    // STONE
    BLOCK_UVS[STONE].u = 1;
    BLOCK_UVS[STONE].v = 15;

    // SAND
    BLOCK_UVS[SAND].u = 2;
    BLOCK_UVS[SAND].v = 14;

    // GRAVEL
    BLOCK_UVS[GRAVEL].u = 3;
    BLOCK_UVS[GRAVEL].v = 14;

    // BEDROCK
    BLOCK_UVS[BEDROCK].u = 1;
    BLOCK_UVS[BEDROCK].v = 14;

    // WOOD
    BLOCK_UVS[WOOD].u = 4;
    BLOCK_UVS[WOOD].v = 15;

    // BRICK
    BLOCK_UVS[BRICK].u = 7;
    BLOCK_UVS[BRICK].v = 15;

    // COBBLESTONE
    BLOCK_UVS[COBBLESTONE].u = 0;
    BLOCK_UVS[COBBLESTONE].v = 14;
}


//---------
 
unsigned int BLOCK_INDICES_COUNT = 36;
unsigned int BLOCK_VERTICES_COUNT = 24;

unsigned int BLOCK_VERTICES_SIZE = 3 * 24 * sizeof(float);
unsigned int BLOCK_INDICES_SIZE = 36 * sizeof(unsigned int);

float BLOCK_VERTICES_UV[] = {
    // Right face
    0, 0,
    1, 0,
    1, 1,
    0, 1,
};

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

float BLOCK_VERTICES_BRIGHTNESS[] = {
    // Left face
    0.8,

    // Right face
    0.9,

    // Back face
    0.8,

    // Front face
    0.7,

    // Top face
    1.0,

    // Bottom face
    0.5,

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
