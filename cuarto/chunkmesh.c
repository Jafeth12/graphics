#include "chunkmesh.h"

chunkmesh* cmesh_new(chunk* chunk) {
    chunkmesh* cm = malloc(sizeof(chunkmesh));
    cm->chunk = chunk;

    cm->vao = vao_new();
    vao_bind(cm->vao);

    unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    unsigned int total_indices_size = BLOCK_INDICES_SIZE * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

    // create vertex buffer and index buffer
    float *vertices = malloc(total_vertices_size);
    unsigned int *indices = malloc(total_indices_size);

    unsigned int vertex_offet, index_offset;
    vertex_offet = index_offset = 0;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                block* b = chunk_get_block(chunk, x, y, z);
                unsigned chunk_index = x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
                unsigned index = 0;
                float vert_value = 0.0f;
                unsigned int ind_value = 0;

                // copy vertices
                for (unsigned i = 0; i < BLOCK_VERTICES_COUNT; i++) {
                    // index = i + (chunk_index) * BLOCK_VERTICES_COUNT;
                    index = vertex_offet + i;
                    vert_value = BLOCK_VERTICES[i] + b->pos[i % 3];
                    vertices[index] = vert_value;
                }

                // copy indices
                for (unsigned i = 0; i < BLOCK_INDICES_COUNT; i++) {
                    // index = i + (chunk_index) * BLOCK_INDICES_COUNT;
                    index = index_offset + i;
                    ind_value = BLOCK_INDICES[i] + (chunk_index) * BLOCK_VERTICES_COUNT;
                    indices[index] = ind_value;
                }

                vertex_offet += BLOCK_VERTICES_COUNT;
                index_offset += BLOCK_INDICES_COUNT;
            }
        }
    }

    cm->vbo = vbo_new(0, total_vertices_size, vertices);
    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0, 0); // position
    vao_add_vbo(cm->vao, cm->vbo);

    cm->ib = ib_new(0, BLOCK_INDICES_COUNT*CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE, indices);

    return cm;
}

chunkmesh* cmesh_new_chunk(float pos[3]) {
    chunk* c = chunk_new((vec3){0, 0, 0});
    return cmesh_new(c);
}

void cmesh_draw(chunkmesh* cm, shader* sh) {
    shader_bind(sh);

    mat4 mat;
    glm_translate_make(mat, cm->chunk->pos);
    shader_set_mat4(sh, "model", mat);

    float color[3] = {0.0f, 0.7f, 0.0f};
    shader_set_vec3(sh, "color", color);

    vao_bind(cm->vao);
    ib_bind(cm->ib);

    glDrawElements(GL_TRIANGLES, cm->ib->count, GL_UNSIGNED_INT, 0);
}
