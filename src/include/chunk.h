#ifndef CHUNK_H
#define CHUNK_H

#include "include/gfx.h"
#include "include/util.h"

#include "include/mesh.h"

#define CHUNK_SIZE ((ivec3s) {{ 16, 256, 16 }})
#define CHUNK_SIZE_F ((vec3s) {{ 16.0f, 256.0f, 16.0f }})
#define CHUNK_VOLUME (CHUNK_SIZE.x * CHUNK_SIZE.y * CHUNK_SIZE.z)

#define chunk_foreach(_pname)\
    ivec3s _pname = GLMS_IVEC3_ZERO_INIT;\
    for (s32 x = 0; x < CHUNK_SIZE.x; x++)\
        for (s32 y = 0; y < CHUNK_SIZE.y; y++)\
            for (s32 z = 0;\
                z < CHUNK_SIZE.z &&\
                ((_pname.x = x) != INT32_MAX) &&\
                ((_pname.y = y) != INT32_MAX) &&\
                ((_pname.z = z) != INT32_MAX);\
                z++)

#define chunk_pos_to_index(_p) ((_p).x * CHUNK_SIZE.y * CHUNK_SIZE.z + (_p).y * CHUNK_SIZE.z + (_p).z)

typedef struct Chunk {
    u32* data;
    bool dirty;
    Mesh mesh;
} Chunk;

bool chunk_pos_in_bounds(ivec3s pos);
bool chunk_pos_on_bounds(ivec3s pos);
void chunk_set_data(Chunk* self, ivec3s pos, u32 data);
u32 chunk_get_data(Chunk* self, ivec3s pos);
void chunk_init(Chunk* self);
void chunk_render(Chunk* self);
void chunk_destroy(Chunk* self);

#endif