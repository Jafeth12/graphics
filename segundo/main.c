#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    if (win_init_glfw() != 0) {
        printf("Error initializing GLFW\n");
        return -1;
    }

    window *win = win_create(640, 480, "Hello World", "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    if (!win) {
        printf("Error creating window\n");
        return -1;
    }

    win_add_triangle(win, 1.0f, 1.0f, 0.0f, 0.5f);
    // win_add_triangle(win, 0.0f, 0.0f, 1.0f, 0.2f);

    win_loop(win);

    return 0;
}
