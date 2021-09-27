#include "include/chunk.h"

bool chunk_pos_in_bounds(ivec3s pos) {
    return pos.x >= 0 && pos.y >= 0 && pos.z >= 0 &&
	   pos.x < CHUNK_SIZE.x && pos.y < CHUNK_SIZE.y && pos.z < CHUNK_SIZE.z;
}

bool chunk_pos_on_bounds(ivec3s pos) {
    return pos.x == 0 || pos.z == 0 || pos.x == (CHUNK_SIZE.x - 1) || pos.z == (CHUNK_SIZE.z - 1);
}

void chunk_set_data(Chunk* self, ivec3s pos, u32 data) {
    assert(chunk_pos_in_bounds(pos));
    self->data[chunk_pos_to_index(pos)] = data;
	self->dirty = true;
}

u32 chunk_get_data(Chunk* self, ivec3s pos) {
    assert(chunk_pos_in_bounds(pos));
    return self->data[chunk_pos_to_index(pos)];
}

void chunk_init(Chunk* self) {
	memset(self, 0, sizeof(Chunk));
	self->data = calloc(1, CHUNK_VOLUME * sizeof(u32));
	mesh_init(&self->mesh);
}

static void mesh_process(Chunk* chunk) {
	mesh_prepare(&chunk->mesh);

	chunk_foreach(pos) {
		vec3s fpos = IVEC3S2V(pos);
		u32 data = chunk->data[chunk_pos_to_index(pos)];

		if (data != 0) {
			for (Direction d = 0; d < 6; d++) {
				ivec3s neighbor = glms_ivec3_add(pos, DIR2IVEC3S(d));

				if (!chunk_pos_in_bounds(neighbor) || chunk->data[chunk_pos_to_index(neighbor)] == 0) {
					mesh_emit_face(&chunk->mesh, fpos, d);
				}
			}
		}
	}

	mesh_finalize(&chunk->mesh);
}

void chunk_render(Chunk* self) {
	if (self->dirty) {
		mesh_process(self);
		self->dirty = false;
	}
	mesh_render(&self->mesh);
}

void chunk_destroy(Chunk* self) {
	free(self->data);
	mesh_destroy(&self->mesh);
}