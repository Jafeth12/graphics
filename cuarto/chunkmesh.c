#include "chunkmesh.h"

chunkmesh* cmesh_new(chunk* chunk) {
    chunkmesh* cm = malloc(sizeof(chunkmesh));
    cm->chunk = chunk;

    cm->vao = vao_new();
    // printf("error al crear vao de cmesh: %d\n", glGetError());
    // printf("valor de vao de cmesh: %d\n", cm->vao->handle);
    // vao_bind(cm->vao);
    // printf("error al bindear vao de cmesh: %d\n", glGetError());

    // unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * chunk->solid_blocks_count;
    unsigned int total_indices_size = BLOCK_INDICES_SIZE * chunk->solid_blocks_count;

    unsigned int total_vertices_count = BLOCK_VERTICES_COUNT * chunk->solid_blocks_count;
    unsigned int total_indices_count = BLOCK_INDICES_COUNT * chunk->solid_blocks_count;

    // create vertex buffer and index buffer
    float *vertices = malloc(total_vertices_size);
    unsigned int *indices = malloc(total_indices_size);
    // float vertices[total_vertices_count];
    // unsigned int indices[total_indices_count];

    unsigned int vertex_offset, index_offset;
    vertex_offset = index_offset = 0;

    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            for (int k = 0; k < CHUNK_SIZE; k++) {
                block* b = chunk_get_block(chunk, i, j, k);
                if (b->type == AIR) continue;

                unsigned int initial_vertex_index = vertex_offset/3;
                float vert_value = 0.0f;
                unsigned int ind_value = 0;

                // create vertices
                for (unsigned ii = 0; ii < BLOCK_VERTICES_COUNT; ii += 3) {
                    vert_value = BLOCK_VERTICES[ii] + i;
                    vertices[vertex_offset++] = vert_value;

                    vert_value = BLOCK_VERTICES[ii+1] + j;
                    vertices[vertex_offset++] = vert_value;

                    vert_value = BLOCK_VERTICES[ii+2] + k;
                    vertices[vertex_offset++] = vert_value;
                }

                // create indices
                for (unsigned ii = 0; ii < BLOCK_INDICES_COUNT; ii += 3) {
                    indices[index_offset++] = BLOCK_INDICES[ii] + initial_vertex_index;
                    indices[index_offset++] = BLOCK_INDICES[ii+1] + initial_vertex_index;
                    indices[index_offset++] = BLOCK_INDICES[ii+2] + initial_vertex_index;
                }

            }
        }
    }

    vao_bind(cm->vao);
    cm->vbo = vbo_new(0, total_vertices_size, vertices);
    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0, 0); // position
    vao_add_vbo(cm->vao, cm->vbo);
    // printf("error al add vbo a cmesh: %d\n", glGetError());

    cm->ib = ib_new(0, total_indices_count, indices);
    // printf("error al crear ibo a cmesh: %d\n", glGetError());

    vao_unbind();

    free(vertices);
    free(indices);

    // printf("error en cmesh_new: %d\n", glGetError());

    return cm;
}

chunkmesh* cmesh_new_chunk(float pos[3]) {
    chunk* c = chunk_new(pos);
    return cmesh_new(c);
}

void cmesh_draw(chunkmesh* cm, shader* sh) {
    shader_bind(sh);

    mat4 mat;
    glm_translate_make(mat, cm->chunk->pos); // TODO hacer bien con offset y no posicion global literal.
    shader_set_mat4(sh, "model", mat);

    float color[3] = {1.0f, 0.0f, 0.0f};
    shader_set_vec3(sh, "color", color);

    vao_bind(cm->vao);
    // printf("error en al bindear vao de cmesh: %d\n", glGetError());
    ib_bind(cm->ib);
    // printf("error en al bindear ibo de cmesh: %d\n", glGetError());

    glDrawElements(GL_TRIANGLES, cm->ib->count, GL_UNSIGNED_INT, 0);

    // printf("error en al pintar cmesh: %d\n", glGetError());

    glBindVertexArray(0);
}
