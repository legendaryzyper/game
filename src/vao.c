#include "include/vao.h"

VAO vao_create(void) {
	VAO self;
	memset(&self, 0, sizeof(VAO));
	glGenVertexArrays(1, &self.handle);
	return self;
}

void vao_bind(VAO* self) {
	glBindVertexArray(self->handle);
}

void vao_destroy(VAO* self) {
	glDeleteVertexArrays(1, &self->handle);
}

void vao_attrib(VAO* self, VBO* vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
	vao_bind(self);
	vbo_bind(vbo);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}