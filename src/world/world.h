#ifndef WORLD_H
#define WORLD_H

#include "blockmesh.h"
#include "chunkmesh.h"

#include <utils/list.h>
#include <utils/shader.h>

#define MAX_CHUNKS 128

typedef struct world {
    size_t block_count;
    chunkmesh* chunkmeshes[MAX_CHUNKS][MAX_CHUNKS];
    texture* terrain_texture;
} world;

world* world_new();

void world_place_block(world *w, enum block_type type, int x, int y, int z);

void world_remove_block(world *w, int x, int y, int z);

void world_add_chunk(world *w, int offset_x, int offset_y);

void world_remove_chunk(world *w, int offset_x, int offset_y);

char world_is_chunk_loaded(world *w, int offset_x, int offset_y);

chunkmesh* world_get_chunk(world *w, int x, int y);

void world_draw(world *w, shader *s);

void world_destroy(world *w);

#define world_get_offset_from_pos(_x, _z, _offset) \
    (_offset)[0] = (_x)/CHUNK_SIZE; \
    (_offset)[1] = (_z)/CHUNK_SIZE;

#define world_for_each_chunk(_w) \
    for (int _x = 0; _x < MAX_CHUNKS; _x++) \
        for (int _z = 0; _z < MAX_CHUNKS; _z++) \

#endif
