#include <shader.h>

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

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fs_source, NULL);
    glCompileShader(fragment_shader);

    sh->shader_program = glCreateProgram();

    glAttachShader(sh->shader_program, vertex_shader);
    glAttachShader(sh->shader_program, fragment_shader);
    glLinkProgram(sh->shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return sh;
}

void shader_use(shader *sh) {
    glUseProgram(sh->shader_program);
}

void shader_set_int(shader *sh, const char *name, int value) {
    glUniform1i(glGetUniformLocation(sh->shader_program, name), value);
}

void shader_set_float(shader *sh, const char *name, float value) {
    glUniform1f(glGetUniformLocation(sh->shader_program, name), value);
}

// void shader_set_vec3(shader *sh, const char *name, vec3 value) {
//     glUniform3fv(glGetUniformLocation(sh->shader_program, name), 1, value);
// }
