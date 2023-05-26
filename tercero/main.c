#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <world.h>
#include <triangle.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    world *world = w_create(800, 600, "Hello World", "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    if (!world) {
        printf("Error creating window\n");
        return -1;
    }

    // triangle *player = tri_new(0.0f, 1.0f, 0.0f, 0.2f);
    // triangle *apple = tri_new(1.0f, 0.0f, 0.0f, 0.2f);

    // win_add_triangle(world, player);
    // win_add_triangle(world, apple);

    w_loop(world);

    w_free(world);

    return 0;
}
