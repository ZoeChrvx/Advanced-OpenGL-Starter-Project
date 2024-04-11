#version 450 core

layout (vertices = 4) out;
uniform float ratio01;
uniform float ratio02;

void main(void)
{
    if(gl_InvocationID == 0) {
        gl_TessLevelInner[0] = ratio02;
        gl_TessLevelInner[1] = ratio02;
        gl_TessLevelOuter[0] = ratio01;
        gl_TessLevelOuter[1] = ratio01;
        gl_TessLevelOuter[2] = ratio01;
        gl_TessLevelOuter[3] = ratio01;
    }
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
