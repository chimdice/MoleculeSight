#version 330 core

out vec4 FragColor;
in float scale;
in vec3 color;

void main()
{
    FragColor = scale * vec4(color, 1);
} 