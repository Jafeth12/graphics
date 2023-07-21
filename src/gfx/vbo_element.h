#ifndef VBO_ELEMENT_H
#define VBO_ELEMENT_H

#include <glad/glad.h>

#include <stdlib.h>

typedef struct vbo_element {
    // GLuint index;
    GLint count;
    GLenum type;
    char normalized;
    GLsizei stride;
    // const GLvoid *offset;
} vbo_element;

vbo_element* vbo_el_new(GLint count, GLenum type, char normalized, GLsizei stride);

void vbo_element_free(vbo_element *e);

// ------------

int vbo_el_sizeof(GLenum type);

#endif

