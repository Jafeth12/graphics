#include "player.h"

player* player_new(vec3 position) {
    player *p = malloc(sizeof(player));
    glm_vec3_copy(position, p->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, 1.0f}, p->direction);
    p->speed = 8.0f;

    return p;
}

void player_destroy(player *p) {
    free(p);
}

float player_get_x(player *p) {
    return p->position[0];
}

float player_get_y(player *p) {
    return p->position[1];
}

float player_get_z(player *p) {
    return p->position[2];
}

// ---------------

void player_move_forward(player *p, float delta_time) {
    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);

    vec3 backward;
    glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    glm_vec3_normalize(backward);

    glm_vec3_scale(backward, p->speed*delta_time, backward);
    glm_vec3_add(p->position, (vec3){-backward[0], -backward[1], -backward[2]}, p->position);
    // glm_vec3_add(p->position, (vec3){0.0f, 0.0f, -p->speed}, p->position);
}

void player_move_backward(player *p, float delta_time) {
    // get right vector of right vector
    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);

    vec3 backward;
    glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    glm_vec3_normalize(backward);

    glm_vec3_scale(backward, p->speed*delta_time, backward);
    glm_vec3_add(p->position, backward, p->position);


    // glm_vec3_add(p->position, (vec3){0.0f, 0.0f, p->speed}, p->position);
}

void player_move_left(player *p, float delta_time) {
    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);
    glm_vec3_scale(right, p->speed*delta_time, right);

    glm_vec3_add(p->position, (vec3){-right[0], -right[1], -right[2]}, p->position);

    // glm_vec3_add(p->position, (vec3){-p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_right(player *p, float delta_time) {
    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);
    glm_vec3_scale(right, p->speed*delta_time, right);

    glm_vec3_add(p->position, right, p->position);

    // glm_vec3_add(p->position, (vec3){p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_up(player *p, float delta_time) {
    glm_vec3_add(p->position, (vec3){0.0f, p->speed*delta_time, 0.0f}, p->position);
}

void player_move_down(player *p, float delta_time) {
    glm_vec3_add(p->position, (vec3){0.0f, -p->speed*delta_time, 0.0f}, p->position);
}

// ---------------
