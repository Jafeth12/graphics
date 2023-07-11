#ifndef PLAYER_H
#define PLAYER_H

#include <cglm/cglm.h>

typedef struct player {
    vec3 position;
    float speed;
} player;

player* player_new(vec3 position);

void player_destroy(player *p);

// ---------------

void player_move_forward(player *p);

void player_move_backward(player *p);

void player_move_left(player *p);

void player_move_right(player *p);

void player_move_up(player *p);

void player_move_down(player *p);

// ---------------

#endif
