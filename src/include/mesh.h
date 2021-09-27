#ifndef MESH_H
#define MESH_H

#include "include/gfx.h"
#include "include/util.h"

#include "include/vbo.h"
#include "include/vao.h"
#include "include/texture.h"

typedef struct MeshBuffer {
	void* data;
	u64 count, index;
} MeshBuffer;

typedef struct Mesh {
	MeshBuffer data, indices;
	u64 vertex_count;

	VAO vao;
	VBO vbo, ebo;
} Mesh;

void mesh_init(Mesh* self);
void mesh_prepare(Mesh* self);
void mesh_emit_face(Mesh* mesh, vec3s position, Direction d);
void mesh_finalize(Mesh* self);
void mesh_render(Mesh* self);
void mesh_destroy(Mesh* self);

#endif