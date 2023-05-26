#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <glad/glad.h>

#include <shader.h>

typedef struct camera {
    vec3 position;
    vec3 front;
    vec3 up;

    mat4 view;
    mat4 projection;

    shader *shader;

    // float yaw;
    // float pitch;
    //
    // float movementSpeed;
    // float mouseSensitivity;
    // float zoom;
    // float fov;
} camera;

camera* cam_create(shader *shader);

void cam_move_forward(camera *cam);

void cam_move_backward(camera *cam);

void cam_move_right(camera *cam);

void cam_move_left(camera *cam);

void cam_update(camera *cam);

#endif // !CAMERA_H
