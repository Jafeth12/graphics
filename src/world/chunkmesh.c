#include "chunkmesh.h"
#include "world/block.h"

chunkmesh* cmesh_new(chunk* chunk) {
    chunkmesh* cm = malloc(sizeof(chunkmesh));
    cm->chunk = chunk;

    cm->vao = vao_new();
    cmesh_mesh(cm);

    return cm;
}

chunkmesh* cmesh_new_chunk(int offset_x, int offset_z) {
    chunk* c = chunk_new(offset_x, offset_z);
    return cmesh_new(c);
}

void cmesh_update(chunkmesh *cm) {
    // discard vbo and ibo
    // create new ones with new data with cmesh_mesh
    vao_delete_vbo(cm->vao, cm->vbo);
    ib_destroy(cm->ib);

    cm->vao = vao_new();
    cmesh_mesh(cm);
}

void cmesh_mesh(chunkmesh *cm) {
    chunk *chunk = cm->chunk;

    unsigned int total_vertices_size = BLOCK_VERTICES_SIZE * chunk->solid_blocks_count;
    unsigned int total_indices_size = BLOCK_INDICES_SIZE * chunk->solid_blocks_count;

    float *vertices = malloc(total_vertices_size);
    unsigned int *indices = malloc(total_indices_size);

    unsigned int vertex_offset, index_offset;
    vertex_offset = index_offset = 0;

    for_each_chunk_block() {
        block* b = chunk_get_block(chunk, i, j, k);
        if (b->type == AIR) continue;

        unsigned int initial_vertex_index = vertex_offset/3;

        // create vertices
        for (unsigned ii = 0; ii < BLOCK_VERTICES_COUNT; ii += 3) {
            vertices[vertex_offset++] = BLOCK_VERTICES[ii] + i;
            vertices[vertex_offset++] = BLOCK_VERTICES[ii+1] + j;
            vertices[vertex_offset++] = BLOCK_VERTICES[ii+2] + k;
        }

        // create indices
        // for (unsigned ii = 0; ii < BLOCK_INDICES_COUNT; ++ii) {
        //     indices[index_offset++] = BLOCK_INDICES[ii] + initial_vertex_index;
        // }

        block *test;

        test = chunk_get_block(chunk, i+1, j, k);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, RIGHT, i, j, k, indices, initial_vertex_index, &index_offset);
        }

        test = chunk_get_block(chunk, i-1, j, k);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, LEFT, i, j, k, indices, initial_vertex_index, &index_offset);
        }

        test = chunk_get_block(chunk, i, j, k-1);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, BACK, i, j, k, indices, initial_vertex_index, &index_offset);
        }

        test = chunk_get_block(chunk, i, j, k+1);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, FRONT, i, j, k, indices, initial_vertex_index, &index_offset);
        }

        test = chunk_get_block(chunk, i, j+1, k);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, TOP, i, j, k, indices, initial_vertex_index, &index_offset);
        }

        test = chunk_get_block(chunk, i, j-1, k);
        if (test == NULL || test->type == AIR) {
            cmesh_add_face(cm, BOTTOM, i, j, k, indices, initial_vertex_index, &index_offset);
        }

    }

    vao_bind(cm->vao);
    cm->vbo = vbo_new(0, total_vertices_size, vertices);
    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0, 0); // position
    vao_add_vbo(cm->vao, cm->vbo);

    cm->ib = ib_new(0, index_offset, indices);

    free(vertices);
    free(indices);
}

void cmesh_add_face(chunkmesh *cm, enum block_face face, int x, int y, int z, unsigned *indices, unsigned initial_vertex_index, unsigned *index_offset) {
    unsigned *FACE_INDICES = TOP_FACE_INDICES;

    switch (face) {
        case FRONT:
            FACE_INDICES = FRONT_FACE_INDICES;
            break;
        case BACK:
            FACE_INDICES = BACK_FACE_INDICES;
            break;
        case LEFT:
            FACE_INDICES = LEFT_FACE_INDICES;
            break;
        case RIGHT:
            FACE_INDICES = RIGHT_FACE_INDICES;
            break;
        case BOTTOM:
            FACE_INDICES = BOTTOM_FACE_INDICES;
            break;
        case TOP:
            break;
    }

    for (unsigned i = 0; i < 6; ++i) {
        indices[*index_offset] = FACE_INDICES[i] + initial_vertex_index;
        *index_offset = *index_offset + 1;
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

void cmesh_destroy(chunkmesh* cm) {
    chunk_destroy(cm->chunk);
    vao_destroy(cm->vao);
    free(cm);
}
