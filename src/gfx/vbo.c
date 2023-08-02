#include "vbo.h"

void vbo_gen(char dynamic, vbo *vb) {
    glGenBuffers(1, &vb->handle);
    vb->dynamic = dynamic;
    vb->elements = NULL;
    vb->element_count = 0;
}

vbo* vbo_new(char dynamic, unsigned int size, const GLvoid *data) {
    vbo *vb = malloc(sizeof(vbo));
    vbo_gen(dynamic, vb);
    vbo_bind(vb);
    vbo_data(vb, size, data);
    return vb;
}

void vbo_bind(vbo *vb) {
    glBindBuffer(GL_ARRAY_BUFFER, vb->handle);
}

void vbo_unbind() {
    glBindBuffer(0, 0);
}

void vbo_destroy(vbo *vb) {
    glDeleteBuffers(1, &vb->handle);

    list *e;
    list_for_each(e, vb->elements) {
        vbo_element *el = e->data;
        free(el);
    }

    free(vb);
}

void vbo_data(vbo *vb, unsigned int size, const GLvoid *data) {
    glBufferData(GL_ARRAY_BUFFER, size, data, vb->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void vbo_add_element(vbo *vb, GLint count, GLenum type, char normalized) {
    vbo_element *el = malloc(sizeof(vbo_element));
    el->count = count;
    el->type = type;
    el->normalized = normalized;

    if (vb->elements == NULL) vb->elements = list_new(el);
    else list_append(vb->elements, el);

    vb->element_count++;
}
