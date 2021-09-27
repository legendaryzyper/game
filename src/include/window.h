#ifndef WINDOW_H
#define WINDOW_H

#include "include/gfx.h"
#include "include/util.h"

typedef void (*FWindow)();

typedef struct Button {
	bool down, last_tick, pressed_tick;
} Button;

typedef struct Mouse {
	vec2s position, delta;
	f32 sensitivity;
} Mouse;

typedef struct Keyboard {
	Button keys[GLFW_KEY_LAST];
} Keyboard;

typedef struct Window {
	GLFWwindow* handle;
	ivec2s size;
	Keyboard keyboard;
	Mouse mouse;
	FWindow init, tick, update, render, destroy;

	u64 last_second;
	u64 frames, fps, last_frame, frame_delta;
	u64 ticks, tps, tick_remainder;
	u64 tickrate;
} Window;
	
void window_create(FWindow init, FWindow tick, FWindow update, FWindow render, FWindow destroy);
void window_loop();

extern Window window;

#endif