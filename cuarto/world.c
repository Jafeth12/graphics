#include "world.h"

world* world_new() {
    world *w = malloc(sizeof(world));
    w->blockmeshes = NULL;
    // w->chunkmeshes = NULL;

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            w->chunkmeshes[i][j] = NULL;
        }
    }

    return w;
}

void world_add_block(world *w, unsigned int id, float pos[3]) {
    blockmesh *bm = bmesh_new_block(id, pos);

    if (w->blockmeshes == NULL) w->blockmeshes = list_new(bm);
    else list_append(w->blockmeshes, bm);
}

void world_add_chunk(world *w, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cm = cmesh_new_chunk(offset_x, offset_z);
    w->chunkmeshes[offset_x][offset_z] = cm;
}

void world_draw(world *w, shader *sh) {
    list *element;
    list_for_each(element, w->blockmeshes) {
        blockmesh *bm = element->data;
        bmesh_draw(bm, sh);
    }

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

}

