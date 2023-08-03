#include "chunkmesh.h"
#include <stdio.h>

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

    // 3 floats for position, 3 floats for normal, 2 floats for uv
    unsigned int total_vertices_size = ((3+3+2)*sizeof(float) * BLOCK_VERTICES_COUNT) * chunk->solid_blocks_count;
    unsigned int total_indices_size = BLOCK_INDICES_SIZE * chunk->solid_blocks_count;

    float *vertices = malloc(total_vertices_size);
    unsigned int *indices = malloc(total_indices_size);

    unsigned int vertex_offset, index_offset;
    vertex_offset = index_offset = 0;

    for_each_chunk_block() {
        block* b = chunk_get_block(chunk, i, j, k);
        if (b->type == AIR) continue;

        unsigned int initial_vertex_index = vertex_offset/(3+3+2);

        unsigned ii_uvs = 0;
        unsigned grass_uvs_index = 0;

        // create vertices
        for (unsigned ii = 0; ii < BLOCK_VERTICES_COUNT; ii++) {
            unsigned ii_pos = ii*3;
            unsigned ii_normal = ii/4;

            // positions
            vertices[vertex_offset++] = BLOCK_VERTICES_POS[ii_pos] + i;
            vertices[vertex_offset++] = BLOCK_VERTICES_POS[ii_pos+1] + j;
            vertices[vertex_offset++] = BLOCK_VERTICES_POS[ii_pos+2] + k;
            
            // normals
            vertices[vertex_offset++] = BLOCK_VERTICES_NORMALS[ii_normal];
            vertices[vertex_offset++] = BLOCK_VERTICES_NORMALS[ii_normal+1];
            vertices[vertex_offset++] = BLOCK_VERTICES_NORMALS[ii_normal+2];

            // uvs
            vertices[vertex_offset++] = (BLOCK_VERTICES_UV[ii_uvs]+1)/16;
            vertices[vertex_offset++] = (BLOCK_VERTICES_UV[ii_uvs+1]+15)/16;

            ii_uvs += 2;
            if (ii_uvs >= 8) ii_uvs = 0;
        }

        // // create indices
        // for (unsigned ii = 0; ii < BLOCK_INDICES_COUNT; ++ii) {
        //     // indices[index_offset++] = BLOCK_INDICES[ii] + initial_vertex_index;
        //     indices[index_offset++] = BLOCK_INDICES[ii] + initial_vertex_index;
        // }

        block *neighbor;

        neighbor = chunk_get_block(chunk, i+1, j, k);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, RIGHT, indices, initial_vertex_index, &index_offset);
        }

        neighbor = chunk_get_block(chunk, i-1, j, k);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, LEFT, indices, initial_vertex_index, &index_offset);
        }

        neighbor = chunk_get_block(chunk, i, j, k-1);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, BACK, indices, initial_vertex_index, &index_offset);
        }

        neighbor = chunk_get_block(chunk, i, j, k+1);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, FRONT, indices, initial_vertex_index, &index_offset);
        }

        neighbor = chunk_get_block(chunk, i, j+1, k);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, TOP, indices, initial_vertex_index, &index_offset);
        }

        neighbor = chunk_get_block(chunk, i, j-1, k);
        if (neighbor == NULL || neighbor->type == AIR) {
            cmesh_add_face(cm, BOTTOM, indices, initial_vertex_index, &index_offset);
        }

    }

    vao_bind(cm->vao);
    cm->vbo = vbo_new(0, total_vertices_size, vertices);

    float stride = 8*sizeof(GLfloat);

    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0); // position
    vbo_add_element(cm->vbo, 3, GL_FLOAT, 0); // normal
    vbo_add_element(cm->vbo, 2, GL_FLOAT, 0); // uvs

    vao_add_vbo(cm->vao, cm->vbo, stride);

    cm->ib = ib_new(0, index_offset, indices);

    free(vertices);
    free(indices);
}

void cmesh_add_face(chunkmesh *cm, enum block_face face, unsigned *indices, unsigned initial_vertex_index, unsigned *index_offset) {
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
