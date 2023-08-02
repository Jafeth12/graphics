#include "vbo_element.h"

vbo_element* vbo_el_new(GLint count, GLenum type, char normalized) {
    vbo_element *e = malloc(sizeof(vbo_element));
    e->count = count;
    e->type = type;
    e->normalized = normalized;

    return e;
}

void vbo_element_free(vbo_element *e) {
    free(e);
}

// ------------

int vbo_el_sizeof(GLenum type) {
    switch (type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
            return sizeof(GLbyte);
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
            return sizeof(GLshort);
        case GL_INT:
        case GL_UNSIGNED_INT:
            return sizeof(GLint);
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_DOUBLE:
            return sizeof(GLdouble);
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            return sizeof(GLint);
        default:
            return 0;
    }
}
