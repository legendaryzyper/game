#include "include/mesh.h"
#include "include/state.h"

const u32 FACE_INDICES[] = { 1, 0, 3, 1, 3, 2 };
const u32 UNIQUE_INDICES[] = { 1, 0, 5, 2 };
const u32 CUBE_INDICES[] = {
	1, 0, 3, 1, 3, 2,
	4, 5, 6, 4, 6, 7, 
	5, 1, 2, 5, 2, 6, 
	0, 4, 7, 0, 7, 3,
	2, 3, 7, 2, 7, 6, 
	5, 4, 0, 5, 0, 1  
};

const f32 CUBE_VERTICES[] = {
	0, 0, 0,
	1, 0, 0,
	1, 1, 0,
	0, 1, 0,

	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1
};

const f32 CUBE_UVS[] = {
	1, 0,
	0, 0,
	0, 1,
	1, 1
};

#define DATA_BUFFER_SIZE (16 * 256 * 16) * 40
#define INDICES_BUFFER_SIZE (16 * 256 * 16) * 36

struct {
	f32 data[DATA_BUFFER_SIZE];
	u32 indices[INDICES_BUFFER_SIZE];
} global_buffer;

void mesh_init(Mesh* self) {
	memset(self, 0, sizeof(Mesh));

	self->vao = vao_create();
	self->vbo = vbo_create(GL_ARRAY_BUFFER);
	self->ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER);
}

void mesh_prepare(Mesh* self) {
	self->vertex_count = 0;
	MeshBuffer* buffers[2] = {
		&self->data, &self->indices
	};

	for (u32 i = 0; i < 2; i++) {
		MeshBuffer* buffer = buffers[i];
		buffer->count = 0;
		buffer->data = ((void* [2]) {
			global_buffer.data,
			global_buffer.indices
		})[i];
	}
}

void mesh_emit_face(Mesh* mesh, vec3s position, Direction d) {
	for (u32 i = 0; i < 4; i++) {
		const f32 *vertex = &CUBE_VERTICES[CUBE_INDICES[(d * 6) + UNIQUE_INDICES[i]] * 3];
		((f32*)mesh->data.data)[mesh->data.index++] = position.x + vertex[0];
		((f32*)mesh->data.data)[mesh->data.index++] = position.y + vertex[1];
		((f32*)mesh->data.data)[mesh->data.index++] = position.z + vertex[2];
		((f32*)mesh->data.data)[mesh->data.index++] = CUBE_UVS[(i * 2) + 0];
		((f32*)mesh->data.data)[mesh->data.index++] = CUBE_UVS[(i * 2) + 1];
	}

	for (u32 i = 0; i < 6; i++) {
		((u32*)mesh->indices.data)[mesh->indices.index++] = mesh->vertex_count + FACE_INDICES[i];
	}

	mesh->vertex_count += 4;
}

void mesh_finalize(Mesh* self) {
	MeshBuffer* buffers[2] = {
			&self->data, &self->indices
	};

	for (u32 i = 0; i < 2; i++) {
		MeshBuffer* buffer = buffers[i];
		buffer->count = buffer->index;
		buffer->index = 0;
	}

	vbo_buffer(&self->vbo, self->data.data, self->data.count * sizeof(f32));
	vbo_buffer(&self->ebo, self->indices.data, self->indices.count * sizeof(u32));	
}

void mesh_render(Mesh* self) {
	shader_bind(&state.shader);
	shader_uniform_camera(&state.shader, &state.world.player.camera);
	shader_uniform_mat4(&state.shader, "m", glms_translate(glms_mat4_identity(), (vec3s) {{ 0.0f, 0.0f, 0.0f }}));
	shader_uniform_texture2D(&state.shader, "tex", &state.texture, 0);	

	const size_t vertex_size = 5 * sizeof(f32);
	vao_attrib(&self->vao, &self->vbo, 0, 3, GL_FLOAT, vertex_size, 0 * sizeof(f32));
	vao_attrib(&self->vao, &self->vbo, 1, 2, GL_FLOAT, vertex_size, 3 * sizeof(f32));

	vao_bind(&self->vao);
	vbo_bind(&self->ebo);
	glDrawElements(GL_TRIANGLES, self->indices.count, GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh* self) {
	vao_destroy(&self->vao);
	vbo_destroy(&self->vbo);
	vbo_destroy(&self->ebo);
}