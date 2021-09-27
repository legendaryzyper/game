#include "include/vbo.h"

VBO vbo_create(GLint type) {
	VBO self;
	memset(&self, 0, sizeof(VBO));
	self.type = type;

	glGenBuffers(1, &self.handle);
	return self;
}

void vbo_bind(VBO* self) {
	glBindBuffer(self->type, self->handle);
}

void vbo_destroy(VBO* self) {
	glDeleteBuffers(1, &self->handle);
}

void vbo_buffer(VBO* self, void* data, GLsizeiptr size) {
	vbo_bind(self);
	glBufferData(self->type, size, data, GL_STATIC_DRAW);
}