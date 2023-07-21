#include "camera.h"

camera* camera_create(enum CAMERA_TYPE type) {
    camera *cam = malloc(sizeof(camera));

    cam->type = type;

    glm_vec3_copy((vec3){0.0f, 0.0f, 0.0f}, cam->position);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, cam->up);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, cam->direction);
    glm_vec3_cross(cam->direction, cam->up, cam->right);

    cam->speed = 1.0f;
    cam->sensitivity = 0.1f;

    glm_mat4_identity(cam->view);
    glm_mat4_identity(cam->projection);

    return cam;
}

camera* camera_create_perspective(float fov, float near, float far, float aspect_ratio, vec3 direction) {
    camera *cam = camera_create(PERSPECTIVE);
    glm_vec3_copy(direction, cam->direction);

    cam->perspective.fov = fov;
    cam->perspective.near = near;
    cam->perspective.far = far;
    cam->perspective.aspect_ratio = aspect_ratio;

    cam->perspective.yaw = 90.0f;
    cam->perspective.pitch = 0.0f;

    glm_perspective(fov, aspect_ratio, near, far, cam->projection);

    return cam;
}

camera* camera_create_orthogongal(float left, float right, float bottom, float top, float near, float far) {
    camera *cam = camera_create(ORTHOGONGAL);

    cam->orthogongal.left = left;
    cam->orthogongal.right = right;
    cam->orthogongal.bottom = bottom;
    cam->orthogongal.top = top;
    cam->orthogongal.near = near;
    cam->orthogongal.far = far;

    glm_ortho(left, right, bottom, top, near, far, cam->projection);

    return cam;
}

void camera_destroy(camera *cam) {
    free(cam);
}

void camera_set_position(camera* cam, vec3 position) {
    glm_vec3_copy(position, cam->position);
}

void camera_update(camera* cam) {
    if (cam->type == PERSPECTIVE) camera_perspective_update(cam);
    else if (cam->type == ORTHOGONGAL) camera_orthogongal_update(cam);
}

void camera_perspective_update(camera *cam) {
    if (cam->type != PERSPECTIVE) return;

    cam->direction[0] = cos(glm_rad(cam->perspective.yaw)) * cos(glm_rad(cam->perspective.pitch));
    cam->direction[1] = sin(glm_rad(cam->perspective.pitch));
    cam->direction[2] = sin(glm_rad(cam->perspective.yaw)) * cos(glm_rad(cam->perspective.pitch));
    glm_vec3_normalize(cam->direction);

    glm_vec3_cross(cam->direction, cam->up, cam->right);
    glm_vec3_cross(cam->right, cam->direction, cam->up);

    vec3 center;
    glm_vec3_add(cam->position, cam->direction, center);

    glm_look(cam->position, cam->direction, cam->up, cam->view);


    // glm_lookat(cam->position, center, cam->up, cam->view);
}

void camera_orthogongal_update(camera *cam) {
    if (cam->type != ORTHOGONGAL) return;

    // M_PI_2 <- existe

    // glm_mat4_identity(cam->view);
    glm_translate_make(cam->view, (vec3){-cam->position[0], -cam->position[1], -cam->position[2]});

    // TODO lo demas xdxd
}
