#ifndef WORLD_H
#define WORLD_H

#include "blockmesh.h"
#include "chunkmesh.h"
#include "list.h"
#include "shader.h"

typedef struct world {
    size_t block_count;
    list *blockmeshes;
    list *chunkmeshes;
} world;

world* world_new();

void world_add_block(world *w, unsigned int id, float pos[3]);

void world_remove_block(world *w, float pos[3]);

void world_add_chunk(world *w, float pos[3]);

void world_draw(world *w, shader *s);

void world_destroy(world *w);

#endif
