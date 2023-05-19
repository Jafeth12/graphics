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

    shader_set_float(sh, "scale", tri->scale);
    shader_set_float(sh, "red", tri->color[0]);
    shader_set_float(sh, "green", tri->color[1]);
    shader_set_float(sh, "blue", tri->color[2]);

    // shader_set_vec3(sh, "color", tri->color);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
