#version 330 core
in vec3 pos;
in vec3 color;
uniform float offset;
out vec4 ourColor;

void main()
{
    gl_Position = vec4(offset * pos.x, offset * pos.y , pos.z , 1.0);
    ourColor = vec4(offset * pos.x +0.5f, offset * pos.y +0.5f , offset * pos.z + 0.5f, 1.0f);
}




