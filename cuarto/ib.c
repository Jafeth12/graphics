#include "ib.h"

void ib_gen(char dynamic, ib *i_b) {
    glGenBuffers(1, &i_b->handle);
    i_b->dynamic = dynamic;
}

ib* ib_new(char dynamic, unsigned int count, const GLuint *data) {
    ib *i_b = malloc(sizeof(ib));
    ib_gen(dynamic, i_b);
    ib_data(i_b, count * sizeof(GLuint), data);

    return i_b;
}

void ib_bind(ib *i_b) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_b->handle);
}

void ib_unbind() {
    glBindBuffer(0, 0);
}

void ib_data(ib *i_b, unsigned int count, const GLuint *data) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, i_b->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
