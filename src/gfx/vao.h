#ifndef VAO_H
#define VAO_H

#include <glad.h>

#include "vbo.h"
#include "ib.h"
#include <utils/list.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct vao {
    GLuint handle; 

    size_t vb_count;
    list *vbos;

    size_t ib_count;
    list *ibs;
} vao;

void vao_gen(vao *v);

vao vao_new();

void vao_bind(vao *v);

void vao_unbind();

void vao_add_vbo(vao *va, vbo *vb, GLsizei stride);

void vao_delete_vbo(vao *va, vbo *vb);

void vao_attr(GLuint index, GLint size, GLenum type, char normalized, GLsizei stride, const void *offset);

void vao_destroy(vao *va);

#endif
