#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "world.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct game {
    window *win;
    world *world;
    shader *sh;
} game;

game *game_init();

void game_run(game *g);

void game_add_shader(game *g, const char *vert_path, const char *frag_path);

void game_loop(game *g);

void game_process_input(game *g);

void game_destroy(game *g);

#endif
