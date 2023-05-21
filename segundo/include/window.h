#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include <shader.h>
#include <triangle.h>

#include <stdlib.h>

#define MAX_TRIANGLES 10

#define TRI_PLAYER 0
#define TRI_APPLE 1

typedef struct window {
    GLFWwindow* window;
    shader *shader;
    triangle *triangles[MAX_TRIANGLES];
} window;

extern int points;

int win_init_glfw();

window* win_create(int width, int height, char *title, char *vs_filename, char *fs_filename);

int win_add_triangle(window *win, triangle *tri);

void win_loop(window *win);

#endif // !WINDOW_H
