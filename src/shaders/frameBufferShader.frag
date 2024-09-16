#version 330 core

out vec4 FragColor;
in vec2 TextCord;
uniform sampler2D screenText;

void main()
{
    FragColor = texture(screenText, TextCord);
}