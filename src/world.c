#include "include/world.h"

void world_init(World* self) {
	memset(self, 0, sizeof(World));
	player_init(&self->player);
	chunk_init(&self->chunk);
	for (s32 x = 0; x < 16; x++) {
		for (s32 z = 0; z < 16; z++) {
			for (s32 y = 0; y < 2; y++) {
				chunk_set_data(&self->chunk, (ivec3s) {{ x, y, z }}, 1);
			}
		}
	}
}

void world_tick(World* self) {
	player_tick(&self->player);
}

void world_update(World* self) {
	player_update(&self->player);
}

void world_render(World* self) {
	chunk_render(&self->chunk);
}

void world_destroy(World* self) {
	chunk_destroy(&self->chunk);
}