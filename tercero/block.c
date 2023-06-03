#include <block.h>

float CUBE_VERTICES[] = {
    1, 0, 1,        // 0 -> North east at Y=0 (arriba derecha)
    1, 0, -1,       // 1 -> South east at Y=0 (abajo derecha)
    -1, 0, -1,      // 2 -> South west at Y=0 (abajo izquierda)
    -1, 0, 1,       // 3 -> North west at Y=0 (arriba izquierda)

    // same but Y=1
    1, 1, 1,        // 4
    1, 1, -1,       // 5
    -1, 1, -1,      // 6
    -1, 1, 1,       // 7
};

unsigned int CUBE_INDICES[] = {
    // Face looking east
    0, 1, 4,
    1, 5, 4,

    // Face looking south
    2, 1, 5,
    2, 5, 6,

    // Face looking west
    3, 2, 6,
    3, 6, 7,

    // Face looking north
    3, 0, 4,
    3, 4, 7,

    // Face looking down
    3, 0, 1,
    3, 1, 2,

    // Face looking up
    7, 4, 5,
    7, 5, 6
};

block* block_new(float red, float green, float blue, float scale) {
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

    block *bl = malloc(sizeof(block));

    bl->color[0] = red;
    bl->color[1] = green;
    bl->color[2] = blue;

    bl->pos[0] = 0.0f;
    bl->pos[1] = 0.0f;
    bl->pos[2] = 0.0f;

    bl->scale = scale;

    glGenVertexArrays(1, &bl->VAO);
    glBindVertexArray(bl->VAO);

    glGenBuffers(1, &bl->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, bl->VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    glGenBuffers(1, &bl->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bl->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);

    return bl;
}

void block_draw(block* bl, shader *sh) {
    shader_use(sh);

    mat4 mat;
    glm_translate_make(mat, bl->pos);
    shader_set_mat4(sh, "model", mat);
    shader_set_vec3(sh, "color", bl->color);

    glBindVertexArray(bl->VAO);
    glDrawElements(GL_TRIANGLES, sizeof(CUBE_INDICES)/sizeof(unsigned), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void block_move_up(block *bl) {
    vec3 movement = {0.0f, 0.05f, 0.0f};
    glm_vec3_add(bl->pos, movement, bl->pos);
}

void block_move_down(block *bl) {
    vec3 movement = {0.0f, -0.05f, 0.0f};
    glm_vec3_add(bl->pos, movement, bl->pos);
}
