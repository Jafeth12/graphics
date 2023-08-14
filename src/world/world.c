#include "world.h"

world* world_new() {
    world *w = malloc(sizeof(world));

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            w->chunkmeshes[i][j] = NULL;
        }
    }

    w->terrain_texture = tex_new(GL_TEXTURE_2D, "res/images/terrain.png");

    return w;
}

void world_place_block(world *w, enum block_type type, int x, int y, int z) {
    if (y < 0 || y >= CHUNK_HEIGHT) return;

    int offset[2];
    world_get_offset_from_pos(x, z, offset);

    if (offset[0] < 0 || offset[1] < 0) return;

    chunkmesh *cm = w->chunkmeshes[offset[0]][offset[1]];
    if (cm == NULL) return;

    // TODO more checks for the position stuff????
    chunk_set_block(cm->chunk, x%CHUNK_SIZE, y, z%CHUNK_SIZE, type);
    cmesh_update(cm);
}

void world_add_chunk(world *w, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cm = w->chunkmeshes[offset_x][offset_z];

    if (cm == NULL) {
        chunkmesh *cm = cmesh_new_chunk(offset_x, offset_z);
        w->chunkmeshes[offset_x][offset_z] = cm;
    } else {
        cmesh_update(cm);
    }
}

void world_remove_chunk(world *w, int offset_x, int offset_y) {
    if (offset_x >= MAX_CHUNKS || offset_y >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_y < 0) return;

    chunkmesh *cm = w->chunkmeshes[offset_x][offset_y];
    if (cm == NULL) return;

    if (cm->is_meshed) {
        cmesh_destroy_mesh(cm);
    }

    // w->chunkmeshes[offset_x][offset_y] = NULL;
}

char world_is_chunk_loaded(world *w, int offset_x, int offset_y) {
    if (offset_x >= MAX_CHUNKS || offset_y >= MAX_CHUNKS) return -1;
    if (offset_x < 0 || offset_y < 0) return -1;

    chunkmesh *cm = w->chunkmeshes[offset_x][offset_y];

    if (cm == NULL) return 0;

    return cm->is_meshed;
}

void world_draw(world *w, shader *sh) {
    tex_bind(w->terrain_texture, 0);
    shader_set_int(sh, "tex", 0);

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            chunkmesh *cm = w->chunkmeshes[i][j];
            if (cm == NULL) continue;

            cmesh_draw(cm, sh);
        }
    }

}

chunkmesh* world_get_chunk(world *w, int x, int y) {
    return w->chunkmeshes[x][y];
}

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

