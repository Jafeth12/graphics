#include "chunk.h"

chunk* chunk_new(float pos[3]) {
    chunk *c = malloc(sizeof(chunk));
    glm_vec3_copy(pos, c->pos);

    c->blocks = malloc(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * sizeof(block*));
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                c->blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE] = block_new(GRASS, (vec3){x, y, z});
            }
        }
    }

    return c;
}

block* chunk_get_block(chunk* c, int x, int y, int z) {
    return c->blocks[x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE];
}
