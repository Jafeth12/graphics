#ifndef WORLD_H
#define WORLD_H

#include "blockmesh.h"
#include "chunkmanager.h"

#include <utils/list.h>
#include <utils/shader.h>

typedef struct world {
    chunk_manager* chunk_manager;
    texture* terrain_texture;
} world;

world* world_new();

// --- Chunk management ---
void world_add_chunk(world *w, int offset_x, int offset_y);

void world_remove_chunk(world *w, int offset_x, int offset_y);

char world_is_chunk_loaded(world *w, int offset_x, int offset_y);

chunkmesh* world_get_chunk(world *w, int x, int y);

// --- Block management ---
void world_place_block(world *w, enum block_type type, int x, int y, int z);

void world_remove_block(world *w, int x, int y, int z);

// --- World management ---

void world_update(world *w, vec3 pos);

void world_draw(world *w, shader *s);

void world_destroy(world *w);

#endif
