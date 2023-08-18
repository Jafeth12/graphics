#include "chunk.h"

chunk* chunk_new(int offset_x, int offset_z) {
    chunk *c = malloc(sizeof(chunk));
    c->offset[0] = offset_x;
    c->offset[1] = offset_z;
    c->solid_blocks_count = 0;

    chunk_for_each_block() {
        enum block_type type = AIR;
        
        if (j == 0) {
            type = BEDROCK;
            c->solid_blocks_count++;
        } else if (j >= 40) {
            type = AIR;
        } else if (j <= 10) {
            type = STONE;
            c->solid_blocks_count++;
        } else if (j <= 20) {
            type = DIRT;
            c->solid_blocks_count++;
        } else if (j <= 30) {

            type = rand() % AIR;
            c->solid_blocks_count++;
        }

        // if (offset_x == 0 && offset_z == 0) {
        //     if (i == CHUNK_SIZE/2 && j <= 10 && k == CHUNK_SIZE/2) {
        //         type = GRASS;
        //         c->solid_blocks_count++;
        //     }
        // } else {
        //     if (j <= 0) {
        //         type = GRASS;
        //         c->solid_blocks_count++;
        //     } else if (i == CHUNK_SIZE/2 && j <= 3 && k == CHUNK_SIZE/2) {
        //         type = GRASS;
        //         c->solid_blocks_count++;
        //     }
        // }

        c->blocks[i][j][k] = type;
    }

    return c;
}

enum block_type chunk_get_block(chunk* c, int x, int y, int z) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return AIR;
    }

    return c->blocks[x][y][z];
}

char chunk_set_block(chunk* c, int x, int y, int z, enum block_type type) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE) {
        return -1;
    }

    if (c->blocks[x][y][z] == AIR && type != AIR) {
        c->solid_blocks_count++;
    } else if (c->blocks[x][y][z] != AIR && type == AIR) {
        c->solid_blocks_count--;
    }

    c->blocks[x][y][z] = type;

    return 0;
}
 
void chunk_destroy(chunk* c) {
    // chunk_for_each_block() {
    //     block_destroy(c->blocks[i][j][k]);
    // }

    free(c);
}
