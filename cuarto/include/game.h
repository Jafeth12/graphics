#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "world.h"
#include "camera.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

typedef struct game {
    window *win;
    world *world;
    shader *sh;
    player *pl;
    camera *cam;
} game;

game *game_init();

void game_run(game *g);

void game_add_shader(game *g, const char *vert_path, const char *frag_path);

void game_loop(game *g);

void game_process_input(game *g);

void game_destroy(game *g);

#endif
