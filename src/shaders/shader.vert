#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

uniform mat4 camera;
uniform mat4 model;
uniform vec3 light;
out float scale;

void main()
{
    float result = dot(light, aNorm);
    if (result > 0) {
        scale = result;
    } else {
        scale = 0;
    }
    gl_Position = camera*model*vec4(aPos, 1.0);
}