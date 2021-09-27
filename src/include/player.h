#ifndef PLAYER_H
#define PLAYER_H

#include "include/gfx.h"
#include "include/util.h"

#include "include/camera.h"

typedef struct Player {
	Camera camera;
	f32 speed;
} Player;

void player_init(Player* self);
void player_tick(Player* self);
void player_update(Player* self);

#endif