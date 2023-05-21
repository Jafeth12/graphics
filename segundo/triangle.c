#include "shader.h"
#include <cglm/affine.h>
#include <cglm/mat4.h>
#include <cglm/vec4.h>
#include <stdio.h>
#include <triangle.h>

triangle* tri_new(float red, float green, float blue, float scale) {
    if (red > 1.0f || red < 0.0f) {
        printf("Red value must be between 0.0 and 1.0\n");
        return NULL;
    } else if (green > 1.0f || green < 0.0f) {
        printf("Green value must be between 0.0 and 1.0\n");
        return NULL;
    } else if (blue > 1.0f || blue < 0.0f) {
        printf("Blue value must be between 0.0 and 1.0\n");
        return NULL;
    } else if (scale < 0.0f) {
        printf("Scale value must be positive\n");
        return NULL;
    }

    triangle *tri = malloc(sizeof(triangle));

    tri->color[0] = red;
    tri->color[1] = green;
    tri->color[2] = blue;

    tri->pos[0] = 0.0f;
    tri->pos[1] = 0.0f;
    tri->pos[2] = 0.0f;

    tri->scale = scale;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f, 0.5f, 0.0f, // top
    };

    glGenVertexArrays(1, &tri->VAO);
    glBindVertexArray(tri->VAO);

    glGenBuffers(1, &tri->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, tri->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    return tri;
}

void tri_draw(triangle* tri, shader* sh) {
    glBindVertexArray(tri->VAO);

    shader_use(sh);

    mat4 mat;
    glm_translate_make(mat, tri->pos);
    glm_scale_uni(mat, tri->scale);

    shader_set_mat4(sh, "transform", mat);
    shader_set_vec3(sh, "color", tri->color);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int tri_collision(triangle* tri1, triangle* tri2) {
    float x1 = tri1->pos[0];
    float y1 = tri1->pos[1];
    float x2 = tri2->pos[0];
    float y2 = tri2->pos[1];

    // printf("--------------------\n");
    // printf("\nx1-x2: %f\n", x1-x2);
    // printf("y1-y2: %f\n", y1-y2);
    // printf("--------------------\n");

    float diffx = x1-x2;
    float diffy = y1-y2;

    if (fabsf(diffx) <= 0.15f && fabsf(diffy) <= 0.15f) {
        return 1;
    }

    return 0;
}

void tri_move_random(triangle* tri) {
    srand(glfwGetTime());
    // random x and y values that dont leave the screen
    float x = (float)rand() / (float)(RAND_MAX/2) - 1.0f;
    float y = (float)rand() / (float)(RAND_MAX/2) - 1.0f;
    tri->pos[0] = x;
    tri->pos[1] = y;
}

void tri_move_right(triangle* tri, float value) {
    tri->pos[0] += value;
}

void tri_move_left(triangle* tri, float value) {
    tri->pos[0] -= value;
}

void tri_move_up(triangle* tri, float value) {
    tri->pos[1] += value;
}

void tri_move_down(triangle* tri, float value) {
    tri->pos[1] -= value;
}
