#ifndef TEXTURE_H
#define TEXTURE_H

#include "include/gfx.h"
#include "include/util.h"

typedef struct Texture {
	GLuint handle;
} Texture;

Texture texture_create(const char* path);
void texture_bind(Texture* self);
void texture_destroy(Texture* self);

#endif