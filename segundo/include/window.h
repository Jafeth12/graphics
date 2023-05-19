#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader.h>
#include <triangle.h>

#include <stdlib.h>

#define MAX_TRIANGLES 10

typedef struct window {
    GLFWwindow* window;
    shader *shader;
    triangle *triangles[MAX_TRIANGLES];
} window;

int win_init_glfw();

window* win_create(int width, int height, char *title, char *vs_filename, char *fs_filename);

void win_add_triangle(window *win, float red, float green, float blue, float scale);

void win_loop(window *win);

#endif // !WINDOW_H
