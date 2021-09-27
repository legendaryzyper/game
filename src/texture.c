#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "include/texture.h"

Texture texture_create(const char* path) {
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

	Texture self;
	memset(&self, 0, sizeof(Texture));

	glGenTextures(1, &self.handle);
	glBindTexture(GL_TEXTURE_2D, self.handle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
	return self;
}

void texture_bind(Texture* self) {
	glBindTexture(GL_TEXTURE_2D, self->handle);
}

void texture_destroy(Texture* self) {
	glDeleteTextures(1, &self->handle);
}