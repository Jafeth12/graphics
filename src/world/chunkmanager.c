#include "chunkmanager.h" 
#include "utils/list.h"

chunk_manager* chunk_man_new() {
    chunk_manager *cm = malloc(sizeof(chunk_manager));

    for (int x = 0; x < MAX_CHUNKS; x++) {
        for (int z = 0; z < MAX_CHUNKS; z++) {
            cm->chunkmeshes[x][z] = NULL;
        }
    }

    cm->chunks_to_load = NULL;
    cm->chunks_to_load_count = 0;

    return cm;
}

void chunk_man_destroy(chunk_manager* cm) {
    for (int x = 0; x < MAX_CHUNKS; x++) {
        for (int z = 0; z < MAX_CHUNKS; z++) {
            if (cm->chunkmeshes[x][z] != NULL) {
                cmesh_destroy(cm->chunkmeshes[x][z]);
            }
        }
    }

    if (cm->chunks_to_load != NULL) list_destroy(cm->chunks_to_load);

    free(cm);
}


// --- Blocks ---

void chunk_man_place_block(chunk_manager *cm, enum block_type type, int x, int y, int z) {
    if (y < 0 || y >= CHUNK_HEIGHT) return;

    int offset[2];
    chunk_get_offset_from_pos(x, z, offset);

    if (offset[0] >= MAX_CHUNKS || offset[1] >= MAX_CHUNKS) return;
    if (offset[0] < 0 || offset[1] < 0) return;

    chunkmesh *cmesh = cm->chunkmeshes[offset[0]][offset[1]];
    if (cmesh == NULL) return;

    // TODO more checks for the position stuff????
    chunk_set_block(cmesh->chunk, x%CHUNK_SIZE, y+3, z%CHUNK_SIZE, type);
    cmesh_update(cmesh, MAX_CHUNKS, cm->chunkmeshes);
}

void chunk_man_remove_block(chunk_manager *cm, int x, int y, int z) {
    if (y < 0 || y >= CHUNK_HEIGHT) return;

    int offset[2];
    chunk_get_offset_from_pos(x, z, offset);

    if (offset[0] >= MAX_CHUNKS || offset[1] >= MAX_CHUNKS) return;
    if (offset[0] < 0 || offset[1] < 0) return;

    chunkmesh *cmesh = cm->chunkmeshes[offset[0]][offset[1]];
    if (cmesh == NULL) return;

    chunk_set_block(cmesh->chunk, x%CHUNK_SIZE, y, z%CHUNK_SIZE, AIR);
    cmesh_update(cmesh, MAX_CHUNKS, cm->chunkmeshes);
}

// --- Chunks ---

void chunk_man_load_chunk(chunk_manager *cm, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cmesh = cm->chunkmeshes[offset_x][offset_z];

    if (cmesh == NULL) {
        chunkmesh *cmesh = cmesh_new_chunk(offset_x, offset_z, MAX_CHUNKS, cm->chunkmeshes);
        cm->chunkmeshes[offset_x][offset_z] = cmesh;
    } else {
        cmesh_update(cmesh, MAX_CHUNKS, cm->chunkmeshes);
    }

}

void chunk_man_unload_chunk(chunk_manager *cm, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cmesh = cm->chunkmeshes[offset_x][offset_z];
    if (cmesh == NULL) return;

    if (cmesh->is_meshed) {
        cmesh_destroy_mesh(cmesh);
    }
}

// deprecated
void chunk_man_add_chunk_to_queue(chunk_manager *cm, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return;
    if (offset_x < 0 || offset_z < 0) return;

    chunkmesh *cmesh = cm->chunkmeshes[offset_x][offset_z];
    if (cmesh == NULL) {
        cmesh = cmesh_new_chunk_no_mesh(offset_x, offset_z);
        cm->chunkmeshes[offset_x][offset_z] = cmesh;
    }

    if (cm->chunks_to_load == NULL) {
        cm->chunks_to_load = list_new((void*)cmesh);
    } else {
        list_append(cm->chunks_to_load, (void*)cmesh);
    }

    cm->chunks_to_load_count += 1;
}

// deprecated
void chunk_man_load_chunk_from_queue(chunk_manager *cm) {
    list *l = cm->chunks_to_load;

    if (l == NULL || l->data == NULL) return;

    chunkmesh *cmesh = (chunkmesh*)l->data;
    if (chunk_man_is_chunk_loaded(cm, cmesh->chunk->offset[0], cmesh->chunk->offset[1])) return;

    chunk_man_load_chunk(cm, cmesh->chunk->offset[0], cmesh->chunk->offset[1]);
    list_pop_front(l);

    cm->chunks_to_load_count -= 1;
    if (cm->chunks_to_load_count == 0) {
        list_destroy(cm->chunks_to_load);
        cm->chunks_to_load = NULL;
    }
}

char chunk_man_is_chunk_loaded(chunk_manager *cm, int offset_x, int offset_z) {
    if (offset_x >= MAX_CHUNKS || offset_z >= MAX_CHUNKS) return -1;
    if (offset_x < 0 || offset_z < 0) return -1;

    chunkmesh *cmesh = cm->chunkmeshes[offset_x][offset_z];

    if (cmesh == NULL) return 0;

    return cmesh->is_meshed;
}

chunkmesh* chunk_man_get_chunk(chunk_manager *cm, int x, int z) {
    if (x >= MAX_CHUNKS || z >= MAX_CHUNKS) return NULL;
    if (x < 0 || z < 0) return NULL;

    return cm->chunkmeshes[x][z];
}

// --- Drawing ---

void chunk_man_draw(chunk_manager *cm, shader* sh) {
    for (int i = 0; i < MAX_CHUNKS; ++i) {
        for (int j = 0; j < MAX_CHUNKS; ++j) {
            chunkmesh *cmesh = cm->chunkmeshes[i][j];
            if (cmesh == NULL) continue;
            if (cmesh->is_meshed == 0) continue;

            cmesh_draw(cmesh, sh);
        }
    }
}

