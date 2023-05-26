#ifndef WORLD_H
#define WORLD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <triangle.h>
#include <camera.h>

#include <stdlib.h>

#define MAX_TRIANGLES 10

#define TRI_PLAYER 0
#define TRI_APPLE 1

typedef struct world {
    GLFWwindow* window;
    camera *camera;
    shader *shader;
    triangle *triangles[MAX_TRIANGLES];
} world;

extern int points;

int w_init_glfw();

world* w_create(int width, int height, char *title, char *vs_filename, char *fs_filename);

// int win_add_triangle(world *win, triangle *tri);

void w_loop(world *world);

void w_free(world *world);

#endif // !WORLD_H
