#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

typedef struct vbo {
    GLuint handle;
    GLenum type;
    GLboolean dynamic;
} vbo;

#define ebo vbo

void vbo_gen(GLsizei n, GLenum type, GLboolean dynamic, vbo *v);

void vbo_bind(vbo *v);

void vbo_unbind();

void vbo_data(vbo *v, GLsizeiptr size, const GLvoid *data, GLenum usage);

#endif
