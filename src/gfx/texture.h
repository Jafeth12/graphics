#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <utils/stb_image.h>

#include <stdlib.h>

typedef struct texture {
    GLuint handle;
    GLenum target;
    const char *path;
} texture;

texture *tex_new(GLenum target, const char *path);

void tex_bind(texture *tex, GLuint unit); 

#endif
