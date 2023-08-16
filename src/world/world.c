#include "world.h"

world* world_new() {
    world *w = malloc(sizeof(world));

    w->terrain_texture = tex_new(GL_TEXTURE_2D, "res/images/terrain.png");
    w->chunk_manager = chunk_man_new();

    return w;
}

// --- Chunk management ---

void world_add_chunk(world *w, int offset_x, int offset_z) {
    chunk_man_load_chunk(w->chunk_manager, offset_x, offset_z);
}

void world_remove_chunk(world *w, int offset_x, int offset_y) {
    chunk_man_unload_chunk(w->chunk_manager, offset_x, offset_y);
}

char world_is_chunk_loaded(world *w, int offset_x, int offset_y) {
    return chunk_man_is_chunk_loaded(w->chunk_manager, offset_x, offset_y);
}

chunkmesh* world_get_chunk(world *w, int x, int y) {
    return chunk_man_get_chunk(w->chunk_manager, x, y);
}

// --- Block management ---

void world_place_block(world *w, enum block_type type, int x, int y, int z) {
    chunk_man_place_block(w->chunk_manager, type, x, y, z);
}

// ------------------------

void world_draw(world *w, shader *sh) {
    tex_bind(w->terrain_texture, 0);
    shader_set_int(sh, "tex", 0);

    chunk_man_draw(w->chunk_manager, sh);
}


void world_update(world *w, vec3 pos) {

}

void world_destroy(world *w) {

    chunk_man_destroy(w->chunk_manager);
    // TODO destroy texture

    free(w);
}

