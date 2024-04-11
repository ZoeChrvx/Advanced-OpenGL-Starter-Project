#version 450 core

out vec4 color;
uniform float ratio01;
uniform float ratio02;

void main()
{
    color = vec4(ratio01, ratio02, ratio02, 1.0f);
} 