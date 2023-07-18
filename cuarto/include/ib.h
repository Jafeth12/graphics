#ifndef IB_H
#define IB_H

#include "list.h"

#include <glad/glad.h>

typedef struct ib {
    GLuint handle;
    char dynamic;
    unsigned int count; // index count
} ib;

void ib_gen(char dynamic, ib *i_b);

ib* ib_new(char dynamic, unsigned int count, const GLuint *data);

void ib_bind(ib *i_b);

void ib_unbind();

void ib_data(ib *i_b, unsigned int count, const GLuint *data);

#endif