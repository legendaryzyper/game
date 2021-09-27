#ifndef CAMERA_H
#define CAMERA_H

#include "include/gfx.h"
#include "include/util.h"

typedef struct Camera {
	mat4s view, proj;
	vec3s position, direction, right, up;
	f32 pitch, yaw, fov, aspect, znear, zfar;
} Camera;

Camera camera_create(f32 fov);
void camera_update(Camera* self);

#endif