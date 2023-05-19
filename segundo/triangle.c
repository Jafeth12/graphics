#include "shader.h"
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

    tri->pos[0] = 1.0f;
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
    glm_mat4_scale_p(mat, tri->scale);

    shader_set_vec3(sh, "color", tri->color);
    shader_set_mat4(sh, "transform", mat);

    glDrawArrays(GL_TRIANGLES, 0, 3);
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
