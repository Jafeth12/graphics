#include <camera.h>
#include <cglm/affine.h>
#include <cglm/vec3.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

camera* cam_create(shader *shader) {
    camera *cam = malloc(sizeof(camera));
    cam->shader = shader;

    float pos[3] = {0.0f, 1.0f, -10.0f};
    float front[3] = {0.0f, 2.0f, -1.0f};
    float up[3] = {0.0f, 1.0f, 0.0f};

    float pos_front[3];

    glm_vec3_copy(pos, cam->position);
    glm_vec3_copy(up, cam->up);

    glm_mat4_identity(cam->view);
    glm_mat4_identity(cam->projection);

    // view matrix
    glm_lookat(cam->position, cam->front, cam->up, cam->view);

    // projection matrix
    glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, cam->projection);

    shader_set_mat4(cam->shader, "view", cam->view);
    shader_set_mat4(cam->shader, "projection", cam->projection);

    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);

    return cam;
}

void cam_move_forward(camera *cam) {
    vec3 movement = {0.0f, 0.0f, 0.1f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    // print cam pos
    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    // glm_translate(cam->view, cam->position);
    // shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_backward(camera *cam) {
    vec3 movement = {0.0f, 0.0f, -0.1f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    // glm_lookat(cam->position, cam->front, cam->up, cam->view);
    // glm_translate(cam->view, cam->position);
    // shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_right(camera *cam) {
    vec3 movement = {0.1f, 0.0f, 0.0f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    // glm_translate(cam->view, cam->position);
    // shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_left(camera *cam) {
    vec3 movement = {-0.1f, 0.0f, 0.0f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    // glm_translate(cam->view, cam->position);
    // shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_update(camera *cam) {
    shader_set_mat4(cam->shader, "view", cam->view);
    shader_set_mat4(cam->shader, "projection", cam->projection);
}
