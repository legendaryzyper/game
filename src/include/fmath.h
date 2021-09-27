#ifndef FMATH_H
#define FMATH_H

#define IVEC2S2V(_v) ((vec2s) {{ _v.x, _v.y }})
#define VEC2S2I(_v) ((ivec2s) {{ _v.x, _v.y }})
#define IVEC3S2V(_v) ((vec3s) {{ _v.x, _v.y, _v.z }})
#define VEC3S2I(_v) ((ivec3s) {{ _v.x, _v.y, _v.z }})

#define IVEC2S23(_v) ((ivec3s) {{ _v.x, _v.y, 0 }})

#define PI_2 GLM_PI_2
#define PI GLM_PI
#define TAU (2 * PI)
#define F32_EPSILON FLT_EPSILON
#define F64_EPSILON DBL_EPSILON

#define cosf(_x) ((f32)cos(_x))
#define sinf(_x) ((f32)sin(_x))
#define radians(_x) ((_x) * (PI / 180.0f))
#define degrees(_x) ((_x) * (180.0f / PI))
#define floori(_x) ((s32)(floor((f64)(_x))))

#define sign(_x) (\
    (0 < _x) - (_x < 0))

#define max(_a, _b) (\
    (_a) > (_b) ? (_a) : (_b))

#define min(_a, _b) (\
    (_a) < (_b) ? (_a) : (_b))

#define clamp(_x, _mn, _mx) (\
    max((_mn), min((_mx), (_x))))

#endif