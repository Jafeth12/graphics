#ifndef PLAYER_H
#define PLAYER_H

#include <cglm/cglm.h>

#define player_floor(position) \
    {floor(position[0]), floor(position[1]), floor(position[2])}

typedef struct player {
    vec3 position;
    vec3 direction;
    float y_velocity;
    float speed;
} player;

player* player_new(vec3 position);

void player_destroy(player *p);

float player_get_x(player *p);

float player_get_y(player *p);

float player_get_z(player *p);

void player_update_y_velocity(player *p, float delta_time);

void player_set_y_velocity(player *p, float velocity);

void player_apply_gravity(player *p, float delta_time);

void player_would_apply_gravity(player *p, float delta_time, vec3 result);

void player_jump(player *p);

// ---------------

void player_move_forward(player *p, float delta_time);

void player_move_backward(player *p, float delta_time);

void player_move_left(player *p, float delta_time);

void player_move_right(player *p, float delta_time);

void player_move_up(player *p, float delta_time);

void player_move_down(player *p, float delta_time);

// ---------------

void player_would_move_forward(player *p, float delta_time, vec3 result);

void player_would_move_backward(player *p, float delta_time, vec3 result);

void player_would_move_left(player *p, float delta_time, vec3 result);

void player_would_move_right(player *p, float delta_time, vec3 result);

void player_would_move_up(player *p, float delta_time, vec3 result);

void player_would_move_down(player *p, float delta_time, vec3 result);

#endif
