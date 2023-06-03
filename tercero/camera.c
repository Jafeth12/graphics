#include <camera.h>
#include <stdio.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

camera* cam_create(shader *shader) {
    camera *cam = malloc(sizeof(camera));
    cam->shader = shader;
    cam->movementSpeed = 0.1f;
    // cam->yaw = 15.0f;

    float pos[3] = {0.0f, 1.0f, 0.0f};
    float target[3] = {0.0f, 1.0f, 1.0f};
    float up[3] = {0.0f, 1.0f, 0.0f};

    float pos_front[3];

    glm_vec3_copy(pos, cam->position);
    glm_vec3_copy(up, cam->up);
    glm_vec3_copy(target, cam->target);

    glm_mat4_identity(cam->view);
    glm_mat4_identity(cam->projection);

    // view matrix
    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    // vec3 neg;
    // glm_vec3_negate_to(cam->position, neg);
    // glm_translate(cam->view, neg);
    // glm_rotate(cam->view, glm_rad(cam->yaw), cam->up);

    // projection matrix
    glm_perspective(glm_rad(70.0f), 800.0f / 600.0f, 0.1f, 100.0f, cam->projection);

    shader_set_mat4(cam->shader, "view", cam->view);
    shader_set_mat4(cam->shader, "projection", cam->projection);

    printf("cam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);

    return cam;
}

void cam_move_up(camera *cam) {
    // only add to y
    cam->position[1] += cam->movementSpeed;
    cam->target[1] += cam->movementSpeed;

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    printf("UP:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_move_down(camera *cam) {
    // only substract to y
    cam->position[1] -= cam->movementSpeed;
    cam->target[1] -= cam->movementSpeed;

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    printf("DOWN:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_move_forward(camera *cam) {
    // pos += target * speed;
    // glm_vec3_muladds(cam->target, cam->movementSpeed, cam->position);
    // glm_vec3_muladds(cam->target, cam->movementSpeed, cam->target);

    // cam->position[2] += cam->movementSpeed;
    // cam->target[2] += cam->movementSpeed;
    // Calculate the camera's forward vector

    vec3 subtracted;
    glm_vec3_sub(cam->target, cam->position, subtracted);
    glm_vec3_normalize(subtracted);

    // Move the camera forwards along the forward vector
    vec3 scaledForward;
    glm_vec3_scale(subtracted, cam->movementSpeed, scaledForward);
    glm_vec3_add(cam->position, scaledForward, cam->position);
    glm_vec3_add(cam->target, scaledForward, cam->target);

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    // vec3 neg;
    // glm_vec3_negate_to(cam->position, neg);
    // glm_translate(cam->view, neg);

    printf("FORWARD:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_move_backward(camera *cam) {
    // pos -= target * speed;
    // glm_vec3_muladds(cam->target, -cam->movementSpeed, cam->position);
    // glm_vec3_muladds(cam->target, -cam->movementSpeed, cam->target);

    // cam->position[2] -= cam->movementSpeed;
    // cam->target[2] -= cam->movementSpeed;

    vec3 subtracted;
    glm_vec3_sub(cam->target, cam->position, subtracted);
    glm_vec3_normalize(subtracted);

    // Move the camera forwards along the forward vector
    vec3 scaledForward;
    glm_vec3_scale(subtracted, -cam->movementSpeed, scaledForward);
    glm_vec3_add(cam->position, scaledForward, cam->position);
    glm_vec3_add(cam->target, scaledForward, cam->target);

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    // vec3 neg;
    // glm_vec3_negate_to(cam->position, neg);
    // glm_translate(cam->view, neg);

    printf("BACK:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_move_right(camera *cam) {
    // vec3 right;
    // glm_vec3_cross(cam->up, cam->target, right);

    // glm_vec3_norm(right);
    // glm_vec3_muladds(right, cam->movementSpeed, cam->position);
    // glm_vec3_muladds(right, cam->movementSpeed, cam->target);

    // cam->position[0] -= cam->movementSpeed;
    // cam->target[0] -= cam->movementSpeed;

    // get direction vector
    vec3 dir;
    glm_vec3_sub(cam->target, cam->position, dir);
    glm_vec3_normalize(dir);

    // get right vector
    vec3 right;
    glm_vec3_cross(dir, cam->up, right);

    vec3 scaled;
    glm_vec3_scale(right, cam->movementSpeed, scaled); // scaled = right * speed
    glm_vec3_add(cam->position, scaled, cam->position); // pos += scaled

    glm_vec3_add(cam->position, dir, cam->target); // target = pos + dir

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    // vec3 neg;
    // glm_vec3_negate_to(cam->position, neg);
    // glm_translate(cam->view, neg);

    printf("RIGHT:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_move_left(camera *cam) {
    // vec3 left;
    // glm_vec3_cross(cam->target, cam->up, left);
    //
    // glm_vec3_norm(left);
    // glm_vec3_muladds(left, cam->movementSpeed, cam->position);
    // glm_vec3_muladds(left, cam->movementSpeed, cam->target);

    // cam->position[0] += cam->movementSpeed;
    // cam->target[0] += cam->movementSpeed;

    // get direction vector
    vec3 dir;
    glm_vec3_sub(cam->target, cam->position, dir);
    glm_vec3_normalize(dir);

    // get right vector
    vec3 right;
    glm_vec3_cross(cam->up, dir, right);

    vec3 scaled;
    glm_vec3_scale(right, cam->movementSpeed, scaled); // scaled = right * speed
    glm_vec3_add(cam->position, scaled, cam->position); // pos += scaled

    glm_vec3_add(cam->position, dir, cam->target); // target = pos + dir

    glm_lookat(cam->position, cam->target, cam->up, cam->view);

    // vec3 neg;
    // glm_vec3_negate_to(cam->position, neg);
    // glm_translate(cam->view, cam->position);

    printf("LEFT:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_rotate_left(camera *cam) {
    cam->target[0] += cam->movementSpeed;
    glm_lookat(cam->position, cam->target, cam->up, cam->view);
    printf("ROT LEFT:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_rotate_right(camera *cam) {
    cam->target[0] -= cam->movementSpeed;
    glm_lookat(cam->position, cam->target, cam->up, cam->view);
    printf("ROT RIGHT:\n");
    printf("\tcam pos: %f %f %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("\ttarget: %f %f %f\n", cam->target[0], cam->target[1], cam->target[2]);
    printf("----------------\n");
}

void cam_update(camera *cam) {
    shader_set_mat4(cam->shader, "view", cam->view);
    shader_set_mat4(cam->shader, "projection", cam->projection);
}
