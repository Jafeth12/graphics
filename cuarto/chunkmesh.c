#include "chunkmesh.h"

chunkmesh* cmesh_new(chunk* chunk) {
    chunkmesh* cm = malloc(sizeof(chunkmesh));
    cm->chunk = chunk;

    cm->vao = vao_new();
    vao_bind(cm->vao);

    unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

    // create vertex buffer and index buffer
    float vertices[BLOCK_VERTICES_COUNT * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
    unsigned int indices[BLOCK_INDICES_COUNT * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    unsigned int vertex_offset, index_offset;
    vertex_offset = index_offset = 0;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                block* b = chunk_get_block(chunk, x, y, z);
                if (b->type == AIR) continue;

                unsigned index = 0;
                float vert_value = 0.0f;
                unsigned int ind_value = 0;

                // copy vertices
                for (unsigned i = 0; i < BLOCK_VERTICES_COUNT; i += 3) {
                    vert_value = BLOCK_VERTICES[i] + x;
                    vertices[vertex_offset++] = vert_value;

                    vert_value = BLOCK_VERTICES[i+1] + y;
                    vertices[vertex_offset++] = vert_value;

                    vert_value = BLOCK_VERTICES[i+2] + z;
                    vertices[vertex_offset++] = vert_value;
                }

                // copy indices
                for (unsigned i = 0; i < BLOCK_INDICES_COUNT; i++) {
                    // index = i + (chunk_index) * BLOCK_INDICES_COUNT;
                    index = index_offset + i;
                    unsigned int vertex_index = vertex_offset + BLOCK_INDICES[i];
                    ind_value = vertex_index - vertex_offset;
                    indices[index] = ind_value;
                }

                vertex_offset += BLOCK_VERTICES_COUNT;
                index_offset += BLOCK_INDICES_COUNT;
            }
        }
    }

    cm->vbo = vbo_new(0, sizeof(vertices), vertices);
    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0, 0); // position
    vao_add_vbo(cm->vao, cm->vbo);

    cm->ib = ib_new(0, BLOCK_INDICES_COUNT*CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE, indices);

    return cm;
}

chunkmesh* cmesh_new_chunk(float pos[3]) {
    chunk* c = chunk_new(pos);
    return cmesh_new(c);
}

void cmesh_draw(chunkmesh* cm, shader* sh) {
    shader_bind(sh);

    mat4 mat;
    glm_translate_make(mat, cm->chunk->pos);
    shader_set_mat4(sh, "model", mat);

    float color[3] = {1.0f, 0.0f, 0.0f};
    shader_set_vec3(sh, "color", color);

    vao_bind(cm->vao);
    ib_bind(cm->ib);

    glDrawElements(GL_TRIANGLES, cm->ib->count, GL_UNSIGNED_INT, 0);
}
