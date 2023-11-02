#version 330 core
in vec3 pos;
in vec3 offset;
in vec3 color;

out vec4 ourColor;

void main()
{
    pos = pos + vec3(0, 0.3f, 0);
    gl_Position = vec4(-pos, 1.0);
    ourColor = vec4(color, 1.0f);
}




