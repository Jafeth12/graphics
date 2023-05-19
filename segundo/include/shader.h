#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct shader {
    unsigned int shader_program;
} shader;

char* shader_load_file(const char *filename);

shader* shader_init( const char *vertex_shader_filename, const char *fragment_shader_filename);

// ----------------------

void shader_use(shader *s);

void shader_set_bool(shader *s, const char *name, int value);

void shader_set_int(shader *s, const char *name, int value);

void shader_set_float(shader *s, const char *name, float value);

// void shader_set_vec3(shader *s, const char *name, float x, float y, float z);

#endif // SHADERS_H

