#include "include/player.h"
#include "include/state.h"

void player_init(Player* self) {
	memset(self, 0, sizeof(Player));
	self->camera = camera_create(radians(45));
}

void player_tick(Player* self) {
	vec3s movement, forward, right;
	movement = GLMS_VEC3_ZERO;
	forward = (vec3s) {{ cosf(self->camera.yaw), 0.0f, sinf(self->camera.yaw) }};
	right = glms_vec3_cross(forward, (vec3s) {{ 0.0f, 1.0f, 0.0f }});

	if (state.window->keyboard.keys[GLFW_KEY_W].down) {
		movement = glms_vec3_add(movement, forward);
	}

	if (state.window->keyboard.keys[GLFW_KEY_S].down) {
		movement = glms_vec3_sub(movement, forward);
	}

	if (state.window->keyboard.keys[GLFW_KEY_D].down) {
		movement = glms_vec3_add(movement, right);
	}

	if (state.window->keyboard.keys[GLFW_KEY_A].down) {
		movement = glms_vec3_sub(movement, right);
	}

	if (state.window->keyboard.keys[GLFW_KEY_SPACE].down) {
		movement = glms_vec3_add(movement, (vec3s) {{ 0.0f, 1.0f, 0.0f }});
	}

	if (state.window->keyboard.keys[GLFW_KEY_LEFT_SHIFT].down) {
		movement = glms_vec3_sub(movement, (vec3s) {{ 0.0f, 1.0f, 0.0f }});
	}

	if (state.window->keyboard.keys[GLFW_KEY_Q].down) {
		glfwSetWindowShouldClose(state.window->handle, true);
	}

	movement = glms_vec3_normalize(movement);
	movement = glms_vec3_scale(movement, self->speed / state.window->tickrate);

	self->camera.position = glms_vec3_add(self->camera.position, movement);
}

void player_update(Player* self) {
	camera_update(&self->camera);
	self->camera.pitch -= state.window->mouse.delta.y / (((f32)state.window->frame_delta) / (state.window->mouse.sensitivity * 1000.0f));
	self->camera.yaw += state.window->mouse.delta.x / (((f32)state.window->frame_delta) / (state.window->mouse.sensitivity * 1000.0f));
}