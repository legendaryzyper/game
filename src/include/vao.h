#ifndef VAO_H
#define VAO_H

#include "include/gfx.h"
#include "include/util.h"

#include "include/vbo.h"

typedef struct VAO {
	GLuint handle;
} VAO;

VAO vao_create();
void vao_bind(VAO* self);
void vao_destroy(VAO* self);
void vao_attrib(VAO* self, VBO* vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif