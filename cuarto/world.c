#include "world.h"

world* world_new() {
    world *w = malloc(sizeof(world));
    w->blockmeshes = NULL;

    return w;
}

void world_add_block(world *w, unsigned int id, float pos[3]) {
    blockmesh *bm = bmesh_new_block(id, pos);

    if (w->blockmeshes == NULL) w->blockmeshes = list_new(bm);
    else list_append(w->blockmeshes, bm);
}

void world_draw(world *w, shader *s) {
    list *element;
    list_for_each(element, w->blockmeshes) {
        blockmesh *bm = element->data;
        bmesh_draw(bm, s);
    }
}

// TODO XDD
void world_destroy(world *w) {

}

