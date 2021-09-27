#ifndef DIRECTION_H
#define DIRECTION_H

#include "include/util.h"

typedef enum Direction {
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN
} Direction;

extern const ivec3s DIRECTION_IVEC[6];
extern const vec3s DIRECTION_VEC[6];

Direction _ivec3s2dir(ivec3s v);

#define DIR2IVEC3S(d) (DIRECTION_IVEC[d])
#define DIR2VEC3S(d) (DIRECTION_VEC[d])
#define IVEC3S2DIR(v) (_ivec3s2dir(v))

#endif