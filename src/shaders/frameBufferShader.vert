#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTextCord;

out vec2 TextCord;

void main()
{
    TextCord = aTextCord;
    gl_Position = vec4(aPos, 0.0, 1.0);
}