#include "include/direction.h"
#include <string.h>

const ivec3s DIRECTION_IVEC[6] = {
    {{  0,  0, -1 }},
    {{  0,  0,  1 }},
    {{  1,  0,  0 }},
    {{ -1,  0,  0 }},
    {{  0,  1,  0 }},
    {{  0, -1,  0 }},
};

const vec3s DIRECTION_VEC[6] = {
    {{  0.0f,  0.0f, -1.0f }},
    {{  0.0f,  0.0f,  1.0f }},
    {{  1.0f,  0.0f,  0.0f }},
    {{ -1.0f,  0.0f,  0.0f }},
    {{  0.0f,  1.0f,  0.0f }},
    {{  0.0f, -1.0f,  0.0f }},
};

Direction _ivec3s2dir(ivec3s v) {
    for (s32 i = 0; i < 6; i++) {
        if (!memcmp(&DIR2IVEC3S(i), &v, sizeof(ivec3s))) {
            return i;
        }
    }

    return -1;
}