#include "vao.h"

void vao_gen(GLsizei n, vao *v) {
    for (int i = 0; i < n; i++) {
        glGenVertexArrays(1, &v->handle);
    }
}

void vao_bind(vao *v) {
    glBindVertexArray(v->handle);
}

void vao_unbind() {
    glBindVertexArray(0);
}

void vao_attr(vbo *v, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
    vbo_bind(v);

    // NOTE: glVertexAttribPointer will AUTO-CONVERT integer values to floating point.
    // Integer vertex attributes must be specified with glVertexAttribIPointer.
    // THIS IS EVIL. OpenGL is bad. Who designed this to fail silently?
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void *) offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *) offset);
            break;
    }

    glEnableVertexAttribArray(index);
}

