#include "texture.h"

texture *tex_new(GLenum target, const char *path) {
    texture *tex = malloc(sizeof(texture));

    tex->target = target;
    tex->path = path;

    stbi_set_flip_vertically_on_load(1);

    int width = 0, height = 0, bits_per_pixel = 0;
    unsigned char *data = stbi_load(path, &width, &height, &bits_per_pixel, 0);

    if (!data) {
        printf("Failed to load texture: %s\n", path);
        return NULL;
    }

    glGenTextures(1, &tex->handle);
    glBindTexture(tex->target, tex->handle);

    glTexImage2D(tex->target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameterf(tex->target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(tex->target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(tex->target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(tex->target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(data);

    return tex;
}

void tex_bind(texture *tex, GLuint unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(tex->target, tex->handle);
}
