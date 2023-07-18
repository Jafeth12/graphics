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

void world_add_chunk(world *w, float pos[3]) {
    chunkmesh *cm = cmesh_new_chunk(pos);

    w->chunkmeshes[(int)ceil(pos[0])][(int)ceil(pos[1])] = cm;

    // if (w->chunkmeshes == NULL) w->chunkmeshes = list_new(cm);
    // else list_append(w->chunkmeshes, cm);
}

void world_draw(world *w, shader *sh) {
    list *element;
    list_for_each(element, w->blockmeshes) {
        blockmesh *bm = element->data;
        bmesh_draw(bm, sh);
    }

    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            chunkmesh *cm = w->chunkmeshes[i][j];
            if (cm != NULL) cmesh_draw(cm, sh);

        }
    }

    // list_for_each(element, w->chunkmeshes) {
    //     chunkmesh *cm = element->data;
    //     cmesh_draw(cm, sh);
    // }
}

// TODO XDD
void world_destroy(world *w) {

}

