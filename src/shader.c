#include "include/shader.h"

static GLuint compile(const char* path, GLenum type) {
    FILE* f;
    char* text;
    long len;

    f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = calloc(1, len + 1);
    text[len] = '\0';
    fread(text, 1, len, f);
    fclose(f);

    GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, (const GLchar* const*)&text, (const GLint*)&len);
    glCompileShader(handle);

    free(text);
    return handle;
}

Shader shader_create(const char* vs_path, const char* fs_path) {
	Shader self;
    memset(&self, 0, sizeof(Shader));
	self.vs_handle = compile(vs_path, GL_VERTEX_SHADER);
	self.fs_handle = compile(fs_path, GL_FRAGMENT_SHADER);
	self.handle = glCreateProgram();

	glAttachShader(self.handle, self.vs_handle);
	glAttachShader(self.handle, self.fs_handle);

	glLinkProgram(self.handle);
	return self;
}

void shader_destroy(Shader* self) {
	glDeleteProgram(self->handle);
}

void shader_bind(Shader* self) {
	glUseProgram(self->handle);
}

void shader_uniform_mat4(Shader* self, const char* name, mat4s m) {
    glUniformMatrix4fv(glGetUniformLocation(self->handle, name), 1, GL_FALSE, (const GLfloat*)&m.raw);
}

void shader_uniform_camera(Shader* self, Camera* camera) {
    shader_uniform_mat4(self, "v", camera->view);
    shader_uniform_mat4(self, "p", camera->proj);
}

void shader_uniform_texture2D(Shader* self, const char* name, Texture* texture, GLuint n) {
    glActiveTexture(GL_TEXTURE0 + n);
    texture_bind(texture);
    glUniform1i(glGetUniformLocation(self->handle, (const GLchar*)name), n);
}