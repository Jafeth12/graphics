#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window.h>
#include <triangle.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    if (win_init_glfw() != 0) {
        printf("Error initializing GLFW\n");
        return -1;
    }

    window *win = win_create(800, 600, "Hello World", "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    if (!win) {
        printf("Error creating window\n");
        return -1;
    }

    triangle *player = tri_new(0.0f, 1.0f, 0.0f, 0.2f);
    triangle *apple = tri_new(1.0f, 0.0f, 0.0f, 0.2f);

    win_add_triangle(win, player);
    win_add_triangle(win, apple);

    win_loop(win);

    return 0;
}
