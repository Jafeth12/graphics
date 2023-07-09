#include "game.h"

game *game_init() {
    game *g = malloc(sizeof(game));

    g->win = win_create(800, 600, "MINECRAFTXDD", (void*)game_loop, g);
    if (g->win == NULL) {
        fprintf(stderr, "Error creating window\n");
        return 0;
    }

    g->world = world_new();

    // world_add_block(g->world, GRASS, (float[3]){0.0f, 0.0f, 0.0f});

    g->sh = NULL;

    return g;
}

void game_run(game *g) {
    win_loop(g->win);
}

void game_add_shader(game *g, const char *vert_path, const char *frag_path) {
    g->sh = shader_init(vert_path, frag_path);
}

void game_loop(game *g) {
    game_process_input(g);
    world_draw(g->world, g->sh);
}

void game_process_input(game *g) {

    if (glfwGetKey(g->win->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(g->win->handle, 1);
    } 

}

void game_destroy(game *g) {
    world_destroy(g->world);
    win_destroy(g->win);
    // shader_destroy(g->sh);
    free(g);
}
