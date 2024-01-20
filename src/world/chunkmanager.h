#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "chunkmesh.h"
#include <utils/list.h>

#define MAX_CHUNKS 256


typedef struct chunk_manager {
    chunkmesh* chunkmeshes[MAX_CHUNKS][MAX_CHUNKS];
    list* chunks_to_load;
    size_t chunks_to_load_count;
} chunk_manager;

// ---

chunk_manager* chunk_man_new();

void chunk_man_destroy(chunk_manager* cm);


// --- Blocks ---

void chunk_man_place_block(chunk_manager *cm, enum block_type type, int x, int y, int z);

void chunk_man_remove_block(chunk_manager *cm, int x, int y, int z);

// --- Chunks ---

void chunk_man_load_chunk(chunk_manager *cm, int offset_x, int offset_y);

void chunk_man_unload_chunk(chunk_manager *cm, int offset_x, int offset_y);

char chunk_man_is_chunk_loaded(chunk_manager *cm, int offset_x, int offset_y);

chunkmesh* chunk_man_get_chunk(chunk_manager *cm, int x, int y);

void chunk_man_update_chunks(chunk_manager *cm);

void chunk_man_add_chunk_to_queue(chunk_manager *cm, int offset_x, int offset_z);

void chunk_man_load_chunk_from_queue(chunk_manager *cm);

// --- Drawing ---

void chunk_man_draw(chunk_manager *cm, shader* sh);

// ----------------------

#define chunk_get_offset_from_pos(_x, _z, _offset) \
    (_offset)[0] = (_x)/CHUNK_SIZE; \
    (_offset)[1] = (_z)/CHUNK_SIZE; \

#define chunk_for_each() \
    for (int x = 0; x < MAX_CHUNKS; x++) \
        for (int z = 0; z < MAX_CHUNKS; z++) \

#endif
