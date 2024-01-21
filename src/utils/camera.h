#ifndef CAMERA_H
#define CAMERA_H

#include <glad.h>
#include <cglm/cglm.h>

#include <stdlib.h>
#include <math.h>

enum CAMERA_TYPE {
    PERSPECTIVE,
    ORTHOGONGAL
};

typedef struct perspective_cam {
    float yaw;
    float pitch;
    float fov;
    float near;
    float far;
    float aspect_ratio;
} perspective_cam; 

typedef struct orthogongal_cam {
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
} orthogongal_cam;

typedef struct camera {
    enum CAMERA_TYPE type;

    vec3 position;
    vec3 direction;
    vec3 up;
    vec3 right;

    float speed;
    float sensitivity;

    mat4 view;
    mat4 projection;

    union {
        perspective_cam perspective;
        orthogongal_cam orthogongal;
    };

} camera;

camera* camera_create(enum CAMERA_TYPE type);

camera* camera_create_perspective(float fov, float near, float far, float aspect_ratio, vec3 direction);

camera* camera_create_orthogongal(float left, float right, float bottom, float top, float near, float far);

void camera_destroy(camera* camera);

void camera_set_position(camera* camera, vec3 position);

void camera_perspective_update(camera* camera);

void camera_orthogongal_update(camera* camera);

void camera_update(camera* camera);


#endif
