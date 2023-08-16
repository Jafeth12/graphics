#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "chunkmesh.h"
#include <utils/list.h>

#define MAX_CHUNKS 64


typedef struct chunk_manager {
    chunkmesh* chunkmeshes[MAX_CHUNKS][MAX_CHUNKS];

    list* chunks_to_load;

} chunk_manager;

// ---

chunk_manager* chunk_man_new();

void chunk_man_destroy(chunk_manager* cm);


// --- Blocks ---

void chunk_man_place_block(chunk_manager *cm, enum block_type type, int x, int y, int z);

// void chunk_man_remove_block(chunk_manager *cm, int x, int y, int z);

// --- Chunks ---

void chunk_man_load_chunk(chunk_manager *cm, int offset_x, int offset_y);

void chunk_man_unload_chunk(chunk_manager *cm, int offset_x, int offset_y);

char chunk_man_is_chunk_loaded(chunk_manager *cm, int offset_x, int offset_y);

chunkmesh* chunk_man_get_chunk(chunk_manager *cm, int x, int y);

void chunk_man_update_chunks(chunk_manager *cm);

#define chunk_man_get_offset_from_pos(_x, _z, _offset) \
    (_offset)[0] = (_x)/CHUNK_SIZE; \
    (_offset)[1] = (_z)/CHUNK_SIZE; \

#define chunk_for_each(_w) \
    for (int _x = 0; _x < MAX_CHUNKS; _x++) \
        for (int _z = 0; _z < MAX_CHUNKS; _z++) \

// --- Drawing ---

void chunk_man_draw(chunk_manager *cm, shader* sh);

// ----------------------

#define chunk_get_offset_from_pos(_x, _z, _offset) \
    (_offset)[0] = (_x)/CHUNK_SIZE; \
    (_offset)[1] = (_z)/CHUNK_SIZE; \

#define chunk_for_each(_w) \
    for (int _x = 0; _x < MAX_CHUNKS; _x++) \
        for (int _z = 0; _z < MAX_CHUNKS; _z++) \

#endif
