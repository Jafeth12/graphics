#include "blockmesh.h"

blockmesh* bmesh_new(block *b) {
    blockmesh *bm = malloc(sizeof(blockmesh));
    bm->block = b;

    bm->vao = vao_new();

    bm->vbo = vbo_new(0, BLOCK_INDICES_SIZE, BLOCK_VERTICES);

    // 0 EN STRIDE (ultimo parametro) PORQUE ESTAN TIGHTLY PACKED
    // SI SE AÑADE ALGO RARO EN MEDIO QUE HACE QUE HAYA PADDING
    // SE TIENE QUE AÑADIR STRIDE!!!!!!!!!!1
    // DE MOMENTO SE QUEDA ASI
    vbo_add_element(bm->vbo, 3, GL_FLOAT, 0, 0);

    bm->ib = ib_new(0, BLOCK_INDICES_SIZE, BLOCK_INDICES);
    vao_bind(bm->vao);
    vao_add_vbo(bm->vao, bm->vbo);
    vao_add_ib(bm->vao, bm->ib);

    return bm;
}

blockmesh* bmesh_new_block(unsigned int id, float pos[3]) {
    block *b = block_new(id, pos);
    return bmesh_new(b);
}

void bmesh_draw(blockmesh *bm, shader *s) {
    vao_bind(bm->vao);
    shader_bind(s);
    glDrawElements(GL_TRIANGLES, BLOCK_INDICES_COUNT, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
