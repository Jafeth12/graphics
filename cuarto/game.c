#include "game.h"

float y_block = 0.0f;

game *game_init() {
    game *g = malloc(sizeof(game));

    g->win = win_create(GAME_WIDTH, GAME_HEIGHT, "MINECRAFTXDD", (void*)game_loop, g);
    if (g->win == NULL) {
        fprintf(stderr, "Error creating window\n");
        return 0;
    }

    game_add_shader(g, "shaders/vs.glsl", "shaders/fs.glsl");

    g->cam = camera_create_perspective(70.0f, 0.1f, 100.0f, (float)GAME_WIDTH / (float)GAME_HEIGHT);
    shader_bind(g->sh);
    shader_set_mat4(g->sh, "view", g->cam->view);
    shader_set_mat4(g->sh, "projection", g->cam->projection);

    g->world = world_new();
    g->pl = player_new((vec3){0.0f, 0.0f, 0.0f});

    world_add_block(g->world, GRASS, (float[3]){0.0f, 0.0f, 0.0f});

    return g;
}

void game_run(game *g) {
    win_loop(g->win);
}

void game_add_shader(game *g, const char *vert_path, const char *frag_path) {
    g->sh = shader_init(vert_path, frag_path);
}

void game_process_input(game *g) {

    if (glfwGetKey(g->win->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(g->win->handle, 1);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_W) == GLFW_PRESS) {
        player_move_forward(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_S) == GLFW_PRESS) {
        player_move_backward(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_A) == GLFW_PRESS) {
        player_move_left(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_D) == GLFW_PRESS) {
        player_move_right(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_SPACE) == GLFW_PRESS) {
        player_move_up(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        player_move_down(g->pl);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_B) == GLFW_PRESS) {
        world_add_block(g->world, GRASS, (float[3]){g->pl->position[0], g->pl->position[1], g->pl->position[2]});
    }

}

void game_destroy(game *g) {
    world_destroy(g->world);
    win_destroy(g->win);
    player_destroy(g->pl);
    camera_destroy(g->cam);
    // shader_destroy(g->sh);
    free(g);
}

// --------------------------------------------------

void game_loop(game *g) {
    game_process_input(g);

    camera_set_position(g->cam, g->pl->position);
    camera_update(g->cam);

    // esto hay que quitarlo de aqui. lo pongo porque quiero ver lo que estoy haciendo
    shader_bind(g->sh);
    shader_set_mat4(g->sh, "view", g->cam->view);
    shader_set_mat4(g->sh, "projection", g->cam->projection);

    world_draw(g->world, g->sh);
}

// --------------------------------------------------
