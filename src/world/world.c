#include "world.h"

world* world_new() {
    world *w = malloc(sizeof(world));

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            w->chunkmeshes[i][j] = NULL;
        }
    }

    return w;
}

void world_add_block(world *w, enum block_type type, int x, int y, int z) {
    int offset[2];
    world_get_offset_from_pos(x, z, offset);

    if (offset[0] < 0 || offset[1] < 0) return;

    chunkmesh *cm = w->chunkmeshes[offset[0]][offset[1]];

    // TODO more checks for the position stuff????
    chunk_set_block(cm->chunk, x%CHUNK_SIZE, y, z%CHUNK_SIZE, type);
    cmesh_update(cm);
}

void world_add_chunk(world *w, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cm = cmesh_new_chunk(offset_x, offset_z);
    w->chunkmeshes[offset_x][offset_z] = cm;
}

void world_draw(world *w, shader *sh) {
    float r, g, b;
    r = g = b = 0;

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            chunkmesh *cm = w->chunkmeshes[i][j];

            if (cm == NULL) continue;

            r += i*0.001;
            g += j*0.002;
            b += j*0.0015;

            shader_bind(sh);
            shader_set_vec3(sh, "color", (vec3){r, g, b});

            cmesh_draw(cm, sh);
        }
    }

}

chunkmesh* world_get_chunk(world *w, int x, int y) {
    return w->chunkmeshes[x][y];
}

// TODO XDD
void world_destroy(world *w) {

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            chunkmesh *cm = w->chunkmeshes[i][j];
            if (cm == NULL) continue;

            cmesh_destroy(cm);
        }
    }

    free(w);
}

