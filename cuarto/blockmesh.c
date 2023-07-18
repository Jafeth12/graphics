#include "blockmesh.h"
#include "shader.h"

blockmesh* bmesh_new(block *b) {
    blockmesh *bm = malloc(sizeof(blockmesh));
    bm->block = b;

    bm->vao = vao_new();
    // printf("error al crear vao de bmesh: %d\n", glGetError());
    vao_bind(bm->vao);
    // printf("error al bindear vao de bmesh: %d\n", glGetError());

    if (b->type == AIR) {
        bm->vbo = vbo_new(0, 0, NULL);
        bm->ib = ib_new(0, 0, NULL);
        vao_add_vbo(bm->vao, bm->vbo);
        return bm;
    }

    bm->vbo = vbo_new(0, BLOCK_VERTICES_SIZE, BLOCK_VERTICES);
    // printf("error al crear vbo de bmesh: %d\n", glGetError());

    // 0 EN STRIDE (ultimo parametro) PORQUE ESTAN TIGHTLY PACKED
    // SI SE AÑADE ALGO RARO EN MEDIO QUE HACE QUE HAYA PADDING
    // SE TIENE QUE AÑADIR STRIDE!!!!!!!!!!1
    // DE MOMENTO SE QUEDA ASI
    vbo_add_element(bm->vbo, 3, GL_FLOAT, 0, 0);

    bm->ib = ib_new(0, BLOCK_INDICES_COUNT, BLOCK_INDICES);
    vao_add_vbo(bm->vao, bm->vbo);
    // vao_add_ib(bm->vao, bm->ib); // borra esta mierda, se tiene que hacer el bind igualmente al hacer draw. esto es inutil

    return bm;
}

blockmesh* bmesh_new_block(enum block_type type, float pos[3]) {
    block *b = block_new(type, pos);
    return bmesh_new(b);
}

void bmesh_draw(blockmesh *bm, shader *sh) {
    // TODO poner todo esto en el renderer para hacer renderer_draw(vao, ib, shader)
    shader_bind(sh);

    mat4 mat;
    glm_translate_make(mat, bm->block->pos);
    shader_set_mat4(sh, "model", mat);

    float color[3] = {0.0f, 0.7f, 0.0f};
    shader_set_vec3(sh, "color", color);

    vao_bind(bm->vao);
    // printf("error al bindear vao de bmesh: %d\n", glGetError());
    ib_bind(bm->ib);
    // printf("error al bindear ibo de bmesh: %d\n", glGetError());
    glDrawElements(GL_TRIANGLES, BLOCK_INDICES_COUNT, GL_UNSIGNED_INT, 0);
    // printf("error despues de pintar bmesh: %d\n", glGetError());
    glBindVertexArray(0);
}
