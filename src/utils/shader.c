#include "shader.h"

char *shader_load_file(const char *filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("Failed to open file %s\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';

    int x = 0;

    fclose(fp);

    return buffer;
}

shader* shader_init(
    const char *vs_filename,
    const char *fs_filename)
{
    shader *sh = malloc(sizeof(shader));

    const char* vs_source = shader_load_file(vs_filename);
    const char* fs_source = shader_load_file(fs_filename);

    if (vs_source == NULL || fs_source == NULL) {
        return NULL;
    }

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vs_source, NULL);
    glCompileShader(vertex_shader);

    GLint success;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("Failed to compile vertex shader: %s\n", info_log);
        return NULL;
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("Failed to compile fragment shader: %s\n", info_log);
        return NULL;
    }

    sh->shader_program = glCreateProgram();

    glAttachShader(sh->shader_program, vertex_shader);
    glAttachShader(sh->shader_program, fragment_shader);
    glLinkProgram(sh->shader_program);

    glGetProgramiv(sh->shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(sh->shader_program, 512, NULL, info_log);
        printf("Failed to link shader program: %s\n", info_log);
        return NULL;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return sh;
}

void shader_bind(shader *sh) {
    glUseProgram(sh->shader_program);
}

void shader_set_int(shader *sh, const char *name, int value) {
    int location = glGetUniformLocation(sh->shader_program, name);
    glUniform1i(location, value);
}

void shader_set_float(shader *sh, const char *name, float value) {
    int location = glGetUniformLocation(sh->shader_program, name);
    glUniform1f(location, value);
}

void shader_set_vec3(shader *sh, const char *name, vec3 value) {
    glUniform3fv(glGetUniformLocation(sh->shader_program, name), 1, value);
}

void shader_set_mat4(shader *sh, const char *name, mat4 value) {
    int location = glGetUniformLocation(sh->shader_program, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, (float*)value);
}
