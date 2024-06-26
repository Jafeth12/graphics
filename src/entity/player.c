#include "player.h"
#include <cglm/vec3.h>

player* player_new(vec3 position) {
    player *p = malloc(sizeof(player));
    glm_vec3_copy(position, p->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, 1.0f}, p->direction);
    glm_vec3_copy((vec3){-1.0f, -1.0f, -1.0f}, p->last_ray_cast_hit);
    p->speed = 10.0f;
    p->y_velocity = 0.0f;

    return p;
}

void player_destroy(player *p) {
    free(p);
}

char player_is_ray_cast_hit_valid(player *p) {
    return p->last_ray_cast_hit[0] >= 0 && p->last_ray_cast_hit[1] >= 0 && p->last_ray_cast_hit[2] >= 0;
}

void player_set_ray_cast_hit(player *p, vec3 hit) {
    glm_vec3_copy(hit, p->last_ray_cast_hit);
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

void player_update_y_velocity(player *p, float delta_time) {
    p->y_velocity -= 12.f * delta_time;
}

void player_apply_gravity(player *p, float delta_time) {
    player_would_apply_gravity(p, delta_time, p->position);
}

void player_would_apply_gravity(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);
    glm_vec3_add(result, (vec3){0.0f, p->y_velocity*delta_time, 0.0f}, result);
}

void player_set_y_velocity(player *p, float velocity) {
    p->y_velocity = velocity;
}

void player_jump(player *p) {
    p->y_velocity = 5.0f;
}

// ---------------

void player_move_forward(player *p, float delta_time) {
    player_would_move_forward(p, delta_time, p->position);

    // vec3 right;
    // glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    // glm_vec3_normalize(right);
    //
    // vec3 backward;
    // glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    // glm_vec3_normalize(backward);
    //
    // glm_vec3_scale(backward, p->speed*delta_time, backward);
    // glm_vec3_add(p->position, (vec3){-backward[0], -backward[1], -backward[2]}, p->position);
    // glm_vec3_add(p->position, (vec3){0.0f, 0.0f, -p->speed}, p->position);
}

void player_move_backward(player *p, float delta_time) {
    player_would_move_backward(p, delta_time, p->position);

    // get right vector of right vector
    // vec3 right;
    // glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    // glm_vec3_normalize(right);
    //
    // vec3 backward;
    // glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    // glm_vec3_normalize(backward);
    //
    // glm_vec3_scale(backward, p->speed*delta_time, backward);
    // glm_vec3_add(p->position, backward, p->position);


    // glm_vec3_add(p->position, (vec3){0.0f, 0.0f, p->speed}, p->position);
}

void player_move_left(player *p, float delta_time) {
    player_would_move_left(p, delta_time, p->position);

    // vec3 right;
    // glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    // glm_vec3_normalize(right);
    // glm_vec3_scale(right, p->speed*delta_time, right);
    //
    // glm_vec3_add(p->position, (vec3){-right[0], -right[1], -right[2]}, p->position);

    // glm_vec3_add(p->position, (vec3){-p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_right(player *p, float delta_time) {
    player_would_move_right(p, delta_time, p->position);

    // vec3 right;
    // glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    // glm_vec3_normalize(right);
    // glm_vec3_scale(right, p->speed*delta_time, right);
    //
    // glm_vec3_add(p->position, right, p->position);

    // glm_vec3_add(p->position, (vec3){p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_up(player *p, float delta_time) {
    player_would_move_up(p, delta_time, p->position);

    // glm_vec3_add(p->position, (vec3){0.0f, p->speed*delta_time, 0.0f}, p->position);
}

void player_move_down(player *p, float delta_time) {
    player_would_move_down(p, delta_time, p->position);

    // glm_vec3_add(p->position, (vec3){0.0f, -p->speed*delta_time, 0.0f}, p->position);
}

// ---------------

void player_would_move_forward(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);

    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);

    vec3 backward;
    glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    glm_vec3_normalize(backward);

    glm_vec3_scale(backward, p->speed*delta_time, backward);
    glm_vec3_add(p->position, (vec3){-backward[0], -backward[1], -backward[2]}, result);
}

void player_would_move_backward(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);

    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);

    vec3 backward;
    glm_vec3_cross(right, (vec3){0.0f, 1.0f, 0.0f}, backward);
    glm_vec3_normalize(backward);

    glm_vec3_scale(backward, p->speed*delta_time, backward);
    glm_vec3_add(p->position, backward, result);
}

void player_would_move_left(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);

    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);
    glm_vec3_scale(right, p->speed*delta_time, right);

    glm_vec3_add(p->position, (vec3){-right[0], -right[1], -right[2]}, result);
}

void player_would_move_right(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);

    vec3 right;
    glm_vec3_cross(p->direction, (vec3){0.0f, 1.0f, 0.0f}, right);
    glm_vec3_normalize(right);
    glm_vec3_scale(right, p->speed*delta_time, right);

    glm_vec3_add(p->position, right, result);
}

void player_would_move_up(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);
    glm_vec3_add(result, (vec3){0.0f, p->speed*delta_time, 0.0f}, result);
}

void player_would_move_down(player *p, float delta_time, vec3 result) {
    glm_vec3_copy(p->position, result);
    glm_vec3_add(result, (vec3){0.0f, -p->speed*delta_time, 0.0f}, result);
}
