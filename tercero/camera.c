#include <camera.h>
#include <cglm/vec3.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

camera* camera_create(shader *shader) {
    camera *cam = malloc(sizeof(camera));
    cam->shader = shader;

    float pos[3] = {0.0f, 0.0f, -3.0f};
    float front[3] = {0.0f, 0.0f, -1.0f};
    float up[3] = {0.0f, 1.0f, 0.0f};

    float pos_front[3];

    glm_vec3_copy(pos, cam->position);
    glm_vec3_copy(front, cam->front);
    glm_vec3_copy(up, cam->up);

    glm_vec3_add(pos, front, pos_front);

    // view matrix
    glm_lookat(pos, pos_front, up, cam->view);

    // projection matrix
    glm_perspective(glm_rad(90.0f), 800.0f / 600.0f, 0.1f, 100.0f, cam->projection);

    glm_translate_make(cam->view, (vec3){0.0f, 0.0f, -3.0f});

    shader_set_mat4(shader, "view", cam->view);
    shader_set_mat4(shader, "projection", cam->projection);

    return cam;
}

void cam_move_forward(camera *cam) {
    vec3 movement = {0.0f, 0.0f, 0.1f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_backward(camera *cam) {
    vec3 movement = {0.0f, 0.0f, -0.1f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_right(camera *cam) {
    vec3 movement = {0.1f, 0.0f, 0.0f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    shader_set_mat4(cam->shader, "view", cam->view);
}

void cam_move_left(camera *cam) {
    vec3 movement = {-0.1f, 0.0f, 0.0f};
    glm_vec3_add(cam->position, movement, cam->position);
    glm_lookat(cam->position, cam->front, cam->up, cam->view);
    shader_set_mat4(cam->shader, "view", cam->view);
}
