#ifndef VBO_H
#define VBO_H

#include "vbo_element.h"

#include <utils/list.h>

#include <glad/glad.h>

typedef struct vbo {
    GLuint handle;
    char dynamic;
    size_t element_count;
    list *elements;
} vbo;

#define ebo vbo

void vbo_gen(char dynamic, vbo *vb);

vbo* vbo_new(char dynamic, unsigned int size, const GLvoid *data);

void vbo_bind(vbo *vb);

void vbo_unbind();

void vbo_data(vbo *vb, unsigned int size, const GLvoid *data);

void vbo_add_element(vbo *vb, GLint size, GLenum type, char normalized, GLsizei stride);

#endif
