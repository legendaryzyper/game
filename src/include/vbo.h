#ifndef VBO_H
#define VBO_H

#include "include/gfx.h"
#include "include/util.h"

typedef struct VBO {
	GLuint handle;
	GLint type;
} VBO;

VBO vbo_create(GLint type);
void vbo_bind(VBO* self);
void vbo_destroy(VBO* self);
void vbo_buffer(VBO* self, void* data, GLsizeiptr size);

#endif