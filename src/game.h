#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <gfx/window.h>
#include <world/world.h>
#include <utils/camera.h>
#include <entity/player.h>

#include <stdio.h>
#include <stdlib.h>

#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

enum SHADER_TYPE {
    SHADER_DEFAULT = 0,
    SHADER_COUNT
    // to be continued... 
};

typedef struct game {
    window *win;
    world *world;
    player *pl;
    camera *cam;
    shader *shaders[SHADER_COUNT];
    char wireframe;
} game;

game *game_init();

void game_run(game *g);

void game_load_shaders(game *g);

void game_update_first_person_camera(game *g);

void game_world_update(game *g);

void game_loop(game *g);

void game_process_input(game *g);

void game_destroy(game *g);

#endif