#version 330 core

out vec4 FragColor;
in float scale;

void main()
{
    FragColor = scale * vec4(0.9, 0.5, 0.2, 1);
} 