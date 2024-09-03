#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in mat4 model;

uniform mat4 camera;
uniform vec3 light;
out float scale;

void main()
{
    float result = dot(light, aNorm);
    if (result > 0) {
        scale = 1;
    } else {
        scale = 1 + result*0.2;
    }
    gl_Position = camera*model*vec4(aPos, 1.0);
}