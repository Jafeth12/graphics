#include "vbo.h"

void vbo_gen(GLsizei n, GLenum type, GLboolean dynamic, vbo *v) {
    for (int i = 0; i < n; i++) {
        glGenBuffers(1, &v->handle);
        v->type = type;
        v->dynamic = dynamic;
    }
}

void vbo_bind(vbo *v) {
    glBindBuffer(v->type, v->handle);
}

void vbo_unbind() {
    glBindBuffer(0, 0);
}

void vbo_data(vbo *v, GLsizeiptr size, const GLvoid *data, GLenum usage) {
    glBufferData(v->type, size, data, usage);
}
