#include "chunk.h"

enum block_type gen_block_type(chunk* c, int x, int y, int z) {
    if (y == 0) {
        c->solid_blocks_count++;
        return BEDROCK;
    }

    float frequency = 0.1f;
    float amplitude = 2.0f;

    float xOffset = sin(x * frequency) * amplitude;
    float zOffset = sin(z * frequency) * amplitude;

    // float surfaceY = 30 + xOffset + zOffset;
    float surfaceY = 3 + xOffset + zOffset;
    if ((float)y < surfaceY) {
        c->solid_blocks_count++;

        if (y >= (surfaceY - 2)) {
            return GRASS;
        }

        return STONE;
    }

    return AIR;
}

chunk* chunk_new(int offset_x, int offset_z) {
    chunk *c = malloc(sizeof(chunk));
    c->offset[0] = offset_x;
    c->offset[1] = offset_z;
    c->solid_blocks_count = 0;

    chunk_for_each_block() {
        c->blocks[i][j][k] = (block) {
            .type = gen_block_type(c, i+(offset_x*CHUNK_SIZE), j, k+(offset_z*CHUNK_SIZE))
        };
    }

    return c;
}

block chunk_get_block(chunk* c, int x, int y, int z) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return (block) { 
            // .type = OUT_OF_BOUNDS
            .type = AIR
        };
    }

    return c->blocks[x][y][z];
}

char chunk_set_block(chunk* c, int x, int y, int z, enum block_type type) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return -1;
    }

    if (c->blocks[x][y][z].type == AIR && type != AIR) {
        c->solid_blocks_count++;
    } else if (c->blocks[x][y][z].type != AIR && type == AIR) {
        c->solid_blocks_count--;
    }

    c->blocks[x][y][z].type = type;

    return 0;
}
 
void chunk_destroy(chunk* c) {
    // chunk_for_each_block() {
    //     block_destroy(c->blocks[i][j][k]);
    // }

    free(c);
}
