#version 330 core
in vec3 pos;
in vec3 color;
uniform float offset;
out vec4 ourColor;

void main()
{
    gl_Position = vec4(pos.x + offset, pos.y, pos.z, 1.0);
    ourColor = vec4((pos.x + offset)/2 + 0.5, pos.y/2 + 0.5, pos.z/2 + 0.5, 1.0f);
}




