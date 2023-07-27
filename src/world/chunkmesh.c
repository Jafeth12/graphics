#include "chunkmesh.h"
#include "world/block.h"

chunkmesh* cmesh_new(chunk* chunk) {
    chunkmesh* cm = malloc(sizeof(chunkmesh));
    cm->chunk = chunk;

    cm->vao = vao_new();

    unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * chunk->solid_blocks_count;
    unsigned int total_indices_size = BLOCK_INDICES_SIZE * chunk->solid_blocks_count;

    unsigned int total_vertices_count = BLOCK_VERTICES_COUNT * chunk->solid_blocks_count;
    unsigned int total_indices_count = BLOCK_INDICES_COUNT * chunk->solid_blocks_count;

    float vertices[total_vertices_count];
    unsigned int indices[total_indices_count];
    // float vertices = malloc(total_vertices_size);
    // unsigned int *indices = malloc(total_indices_size);

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

    cm->ib = ib_new(0, total_indices_count, indices);

    // free(vertices);
    // free(indices);

    return cm;
}

chunkmesh* cmesh_new_chunk(unsigned offset_x, unsigned offset_z) {
    chunk* c = chunk_new(offset_x, offset_z);
    return cmesh_new(c);
}
 
void cmesh_add_face(chunkmesh *cm, enum block_face face, int x, int y, int z) {
    unsigned *FACE_INDICES = FRONT_FACE_INDICES;

    switch (face) {
        case BACK:
            FACE_INDICES = BACK_FACE_INDICES;
            break;
        case LEFT:
            FACE_INDICES = LEFT_FACE_INDICES;
            break;
        case RIGHT:
            FACE_INDICES = RIGHT_FACE_INDICES;
            break;
        case TOP:
            FACE_INDICES = TOP_FACE_INDICES;
            break;
        case BOTTOM:
            FACE_INDICES = BOTTOM_FACE_INDICES;
            break;
        default:
            break;
    }


}

void cmesh_draw(chunkmesh* cm, shader* sh) {
    shader_bind(sh);

    vec3 offset;
    glm_vec3_copy((vec3){cm->chunk->offset[0]*CHUNK_SIZE, 0.0f, cm->chunk->offset[1]*CHUNK_SIZE}, offset);

    mat4 mat;
    glm_translate_make(mat, offset);
    shader_set_mat4(sh, "model", mat);

    // float color[3] = {1.0f, 0.0f, 0.0f};
    // shader_set_vec3(sh, "color", color);

    vao_bind(cm->vao);
    ib_bind(cm->ib);

    glDrawElements(GL_TRIANGLES, cm->ib->count, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
