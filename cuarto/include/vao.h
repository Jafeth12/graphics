#ifndef VAO_H
#define VAO_H

#include <GL/glew.h>

#include "vbo.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct vao {
    GLuint handle; 
} vao;

void vao_gen(GLsizei n, vao *v);

void vao_bind(vao *v);

void vao_unbind();

void vao_attr(vbo *v, GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);

#endif
