#ifndef IB_H
#define IB_H

#include <utils/list.h>

#include <glad.h>

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

void ib_destroy(ib *i_b);

#endif
