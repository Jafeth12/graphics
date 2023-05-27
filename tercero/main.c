#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <world.h>
#include <triangle.h>

#include <stdio.h>
#include <stdlib.h>

int main() {
    world *world = w_create("Hello World", "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    if (!world) {
        printf("Error creating window\n");
        return -1;
    }

    w_loop(world);
    w_free(world);

    return 0;
}
