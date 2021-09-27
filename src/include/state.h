#ifndef STATE_H
#define STATE_H

#include "include/gfx.h"
#include "include/util.h"

#include "include/window.h"
#include "include/shader.h"
#include "include/world.h"
#include "include/texture.h"

typedef struct State {
	Window* window;
	Shader shader;
	Texture texture;
	World world;
} State;

extern State state;

#endif