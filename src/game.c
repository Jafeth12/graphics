#include "game.h"

game *game_init() {
    game *g = malloc(sizeof(game));

    g->win = win_create(GAME_WIDTH, GAME_HEIGHT, "MINECRAFTXDD", (void*)game_loop, g);
    if (g->win == NULL) {
        fprintf(stderr, "Error creating window\n");
        return 0;
    }
    win_mouse_set_grabbed(g->win, 1);

    g->wireframe = 0;

    game_load_shaders(g);

    g->pl = player_new((vec3){0.0f, 2.0f, 0.0f});
    g->cam = camera_create_perspective(70.0f, 0.1f, 100.0f, (float)GAME_WIDTH / (float)GAME_HEIGHT, g->pl->direction);

    g->world = world_new();

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            world_add_chunk(g->world, i, j);
        }
    }

    return g;
}

void game_run(game *g) {
    win_loop(g->win);
}

void game_load_shaders(game *g) {
    g->shaders[SHADER_DEFAULT] = shader_init("shaders/vs.glsl", "shaders/fs.glsl");

    // more to be added if needed
}

void game_update_first_person_camera(game *g) {
    camera_set_position(g->cam, g->pl->position);
    camera_update(g->cam);

    glm_vec3_copy(g->cam->direction, g->pl->direction);

    shader_bind(g->shaders[SHADER_DEFAULT]);
    shader_set_mat4(g->shaders[SHADER_DEFAULT], "view", g->cam->view);
    shader_set_mat4(g->shaders[SHADER_DEFAULT], "projection", g->cam->projection);
}

void game_process_input(game *g) {

    if (glfwGetKey(g->win->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(g->win->handle, 1);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_T) == GLFW_PRESS) {
        g->wireframe = !g->wireframe;

        if (g->wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_P) == GLFW_PRESS) {
        printf("------------------------\n");
        // world position
        printf("x: %f, y: %f, z: %f\n", g->pl->position[0], g->pl->position[1], g->pl->position[2]);

        player *p = g->pl;
        unsigned player_world_pos[3];
        player_world_pos[0] = floor(player_get_x(p));
        player_world_pos[1] = floor(player_get_y(p));
        player_world_pos[2] = floor(player_get_z(p));

        // block position
        printf("x: %d, y: %d, z: %d\n", player_world_pos[0], player_world_pos[1], player_world_pos[2]);


        unsigned offset_x, offset_z;
        offset_x = player_world_pos[0]/CHUNK_SIZE;
        offset_z = player_world_pos[2]/CHUNK_SIZE;

        // chunk position
        printf("x: %d, z: %d\n", offset_x, offset_z);
        printf("------------------------\n");
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_M) == GLFW_PRESS) {
        win_mouse_set_grabbed(g->win, !g->win->mouse_grabbed);
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

    if (glfwGetKey(g->win->handle, GLFW_KEY_LEFT) == GLFW_PRESS) {
        g->cam->perspective.yaw -= 1.2f;
        printf("yaw: %f\n", g->cam->perspective.yaw);
    }

    if (glfwGetKey(g->win->handle, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        g->cam->perspective.yaw += 1.2f;
        printf("yaw: %f\n", g->cam->perspective.yaw);
    }
    //
    // if (glfwGetKey(g->win->handle, GLFW_KEY_UP) == GLFW_PRESS) {
    //     g->cam->perspective.pitch += 0.5f;
    // }
    //
    // if (glfwGetKey(g->win->handle, GLFW_KEY_DOWN) == GLFW_PRESS) {
    //     g->cam->perspective.pitch -= 0.5f;
    // }

    if (glfwGetKey(g->win->handle, GLFW_KEY_B) == GLFW_PRESS) {
        world_add_block(g->world, GRASS, (float[3]){ceil(g->pl->position[0]), ceil(g->pl->position[1])-1, ceil(g->pl->position[2])});
    }

}

void game_destroy(game *g) {
    world_destroy(g->world);
    win_destroy(g->win);
    player_destroy(g->pl);
    camera_destroy(g->cam);
    // shader_destroy(g->shaders[SHADER_DEFAULT]);
    free(g);
}

void game_world_update(game *g) {
    world *w = g->world;
    player *p = g->pl;

    unsigned player_world_pos[3];
    player_world_pos[0] = floor(player_get_x(p));
    player_world_pos[1] = floor(player_get_y(p));
    player_world_pos[2] = floor(player_get_z(p));

    unsigned offset_x, offset_z;
    offset_x = player_world_pos[0]/CHUNK_SIZE;
    offset_z = player_world_pos[2]/CHUNK_SIZE;

    if (world_get_chunk(w, offset_x, offset_z) == NULL) world_add_chunk(w, offset_x, offset_z);
}

// --------------------------------------------------

void game_loop(game *g) {
    game_process_input(g);
    game_update_first_person_camera(g);
    game_world_update(g);
    world_draw(g->world, g->shaders[SHADER_DEFAULT]);

        printf("------------------------\n");
        // world position
        printf("x: %f, y: %f, z: %f\n", g->pl->position[0], g->pl->position[1], g->pl->position[2]);

        player *p = g->pl;
        unsigned player_world_pos[3];
        player_world_pos[0] = floor(player_get_x(p));
        player_world_pos[1] = floor(player_get_y(p));
        player_world_pos[2] = floor(player_get_z(p));

        // block position
        printf("x: %d, y: %d, z: %d\n", player_world_pos[0], player_world_pos[1], player_world_pos[2]);


        unsigned offset_x, offset_z;
        offset_x = player_world_pos[0]/CHUNK_SIZE;
        offset_z = player_world_pos[2]/CHUNK_SIZE;

        // chunk position
        printf("x: %d, z: %d\n", offset_x, offset_z);
        printf("------------------------\n");

}

// --------------------------------------------------