#include "chunk.h"

#include "noise1234.h"

// f32 octave_compute(struct Octave *p, f32 seed, f32 x, f32 z) {
//     f32 u = 1.0f, v = 0.0f;
//     for (int i = 0; i < p->n; i++) {
//         v += (1.0f / u) * noise3((x / 1.01f) * u, (z / 1.01f) * u, seed + (p->o * 32));
//         u *= 2.0f;
//     }
//     return v;
// }

enum block_type gen_block_type(chunk* c, int x, int y, int z) {
    if (y == 0) {
        c->solid_blocks_count++;
        return BEDROCK;
    }

    float height = 0.0f;
    float offset = c->seed % 100;
    for (int i = 0; i < 5; i++) {
        height += noise3((x*0.03) + offset, z*0.03 + offset, c->seed + 10 * 64) * 2.05 + 3;
    }

    float surfaceY = height;

    if (y < height) {
        c->solid_blocks_count++;

        if (y >= (surfaceY - 2)) {
            return GRASS;
        }

        return STONE;
    }

    return AIR;

    // float frequency = 0.1f;
    // float amplitude = 2.0f;
    //
    // float xOffset = sin(x * frequency) * amplitude;
    // float zOffset = sin(z * frequency) * amplitude;
    //
    // // float surfaceY = 30 + xOffset + zOffset;
    // float surfaceY = 3 + xOffset + zOffset;
    // if ((float)y < surfaceY) {
    //     c->solid_blocks_count++;
    //
    //     if (y >= (surfaceY - 2)) {
    //         return GRASS;
    //     }
    //
    //     return STONE;
    // }
    //
    // return AIR;
}

chunk* chunk_new(unsigned seed, int offset_x, int offset_z) {
    chunk *c = malloc(sizeof(chunk));
    c->offset[0] = offset_x;
    c->offset[1] = offset_z;
    c->solid_blocks_count = 0;
    c->seed = seed;

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
            .type = OUT_OF_BOUNDS
            // .type = AIR
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

char chunk_does_pos_intersect(chunk* c, ivec3 pos) {
    int x = pos[0];
    int y = pos[1];
    int z = pos[2];

    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return 0;
    }

    enum block_type type = chunk_get_block(c, x, y, z).type;

    return type != AIR && type != OUT_OF_BOUNDS;
}
 
void chunk_destroy(chunk* c) {
    // chunk_for_each_block() {
    //     block_destroy(c->blocks[i][j][k]);
    // }

    free(c);
}
