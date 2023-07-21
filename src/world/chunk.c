#include "chunk.h"

chunk* chunk_new(unsigned offset_x, unsigned offset_z) {
    chunk *c = malloc(sizeof(chunk));
    c->offset[0] = offset_x;
    c->offset[1] = offset_z;
    c->solid_blocks_count = 0;

    // c->blocks = malloc(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(block*));

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                enum block_type type = AIR;
                if (y <= 0) {
                    type = GRASS;
                    c->solid_blocks_count++;
                }

                c->blocks[x][y][z] = block_new(type, (vec3){x, y, z});
            }
        }
    }

    return c;
}

block* chunk_get_block(chunk* c, int x, int y, int z) {
    return c->blocks[x][y][z];
}
