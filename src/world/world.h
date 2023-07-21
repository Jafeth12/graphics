#ifndef WORLD_H
#define WORLD_H

#include "blockmesh.h"
#include "chunkmesh.h"

#include <utils/list.h>
#include <utils/shader.h>

#define MAX_CHUNKS 128

typedef struct world {
    size_t block_count;
    list *blockmeshes;
    // list *chunkmeshes;
    chunkmesh* chunkmeshes[MAX_CHUNKS][MAX_CHUNKS];
} world;

world* world_new();

void world_add_block(world *w, unsigned int id, float pos[3]);

void world_remove_block(world *w, float pos[3]);

void world_add_chunk(world *w, int offset_x, int offset_y);

chunkmesh* world_get_chunk(world *w, int x, int y);

void world_draw(world *w, shader *s);

void world_destroy(world *w);

#endif