#include "player.h"

player* player_new(vec3 position) {
    player *p = malloc(sizeof(player));
    glm_vec3_copy(position, p->position);
    p->speed = 0.1f;

    return p;
}

void player_destroy(player *p) {
    free(p);
}

// ---------------

void player_move_forward(player *p) {
    glm_vec3_add(p->position, (vec3){0.0f, 0.0f, -p->speed}, p->position);
}

void player_move_backward(player *p) {
    glm_vec3_add(p->position, (vec3){0.0f, 0.0f, p->speed}, p->position);
}

void player_move_left(player *p) {
    glm_vec3_add(p->position, (vec3){-p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_right(player *p) {
    glm_vec3_add(p->position, (vec3){p->speed, 0.0f, 0.0f}, p->position);
}

void player_move_up(player *p) {
    glm_vec3_add(p->position, (vec3){0.0f, p->speed, 0.0f}, p->position);
}

void player_move_down(player *p) {
    glm_vec3_add(p->position, (vec3){0.0f, -p->speed, 0.0f}, p->position);
}

// ---------------
