#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct window {
    GLFWwindow *handle;
    GLuint width;
    GLuint height;
    float delta_time;
    const char *title;
    char mouse_grabbed;

    // custom loop that runs inside the window loop
    void (*custom_loop)(void*arg);
    void *custom_args;
} window;

window *win_create(GLuint width, GLuint height, const char *title, void (*custom_loop)(void*arg), void* args);

int win_init_glfw(void);

void win_mouse_set_grabbed(window *win, char grabbed);

void win_loop(window *win);

void win_destroy(window *win);

#endif
