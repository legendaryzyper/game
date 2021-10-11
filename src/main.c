#include "include/state.h"

State state;

void init(void) {
	state.window = &window;
	state.shader = shader_create("res/shaders/shader.vert", "res/shaders/shader.frag");
	state.texture = texture_create("res/textures/grass.jpg");
	world_init(&state.world);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	state.world.player.camera.position = (vec3s) {{ 0.0f, 0.0f, 0.0f }};
	state.world.player.speed = 6.0f;
}

void tick(void) {
	world_tick(&state.world);
}

void update(void) {
	world_update(&state.world);
}

void render(void) {
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	world_render(&state.world);
}

void destroy(void) {
	shader_destroy(&state.shader);
	world_destroy(&state.world);
}

int main(int argc, char** argv) {
	window_create(init, tick, update, render, destroy);
	window_loop();
}