#include "vao.h"
#include "gfx/vbo.h"

void vao_gen(vao *va) {
    glGenVertexArrays(1, &va->handle);
    va->vbos = NULL;
    va->vb_count = 0;
}

vao* vao_new() {
    vao *va = malloc(sizeof(vao));
    vao_gen(va);
    return va;
}

void vao_bind(vao *va) {
    glBindVertexArray(va->handle);
}

void vao_unbind() {
    glBindVertexArray(0);
}

void vao_add_vbo(vao *va, vbo *vb) {
    vao_bind(va);
    vbo_bind(vb);

    if (va->vb_count == 0) va->vbos = list_new(vb);
    else list_append(va->vbos, vb);

    va->vb_count++;

    list *e;
    int i = 0;
    void* offset = 0;
    list_for_each(e, vb->elements) {
        vbo_element *el = e->data;

        vao_attr(i, el->count, el->type, el->normalized, el->stride, (void*)offset);

        int sizeof_type = vbo_el_sizeof(el->type);
        if (sizeof_type == 0) {
            printf("ERROR: Unknown type %d\n", el->type);
            exit(-1);
        }

        offset += el->count * sizeof_type;

        // glEnableVertexAttribArray(i);
        ++i;
    }
}

void vao_delete_vbo(vao *va, vbo *vb) {
    vao_bind(va);

    list *e;
    int i = 0;
    void* offset = 0;
    list_for_each(e, vb->elements) {
        vbo_element *el = e->data;

        glDisableVertexAttribArray(i);

        ++i;
    }

    vbo_destroy(vb);
}

void vao_add_ib(vao *va, ib *i_b) {
    vao_bind(va);
    ib_bind(i_b);
}

void vao_attr(GLuint index, GLint size, GLenum type, char normalized, GLsizei stride, const void *offset) {

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
            glVertexAttribPointer(index, size, type, normalized ? GL_TRUE : GL_FALSE, stride, (void *) offset);
            break;
    }

    glEnableVertexAttribArray(index);
}


void vao_destroy(vao *va) {
    vao_bind(va);

    list *e;
    list_for_each(e, va->vbos) {
        vbo *vb = e->data;
        vao_delete_vbo(va, vb);
    }

    glDeleteVertexArrays(1, &va->handle);
    free(va);
}
