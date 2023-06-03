#ifndef WORLD_H
#define WORLD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

// #include <triangle.h>
#include <block.h>
#include <camera.h>

#include <stdlib.h>

#define MAX_TRIANGLES 10

#define TRI_PLAYER 0
#define TRI_APPLE 1

#define WIDTH 1920
#define HEIGHT 1080

typedef struct world {
    GLFWwindow* window;
    camera *camera;
    shader *shader;
    GLuint floor_VBO;
    GLuint floor_VAO;
    block *blocks[MAX_TRIANGLES];
    // triangle *triangles[MAX_TRIANGLES];
} world;

int w_init_glfw();

world* w_create(char *title, char *vs_filename, char *fs_filename);

void w_loop(world *world);

void w_render(world *world);

void w_free(world *world);

#endif // !WORLD_H
