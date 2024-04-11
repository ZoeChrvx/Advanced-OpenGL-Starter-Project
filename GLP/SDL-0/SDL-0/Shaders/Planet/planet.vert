#version 330 core
in vec3 pos;

uniform mat4 mv_matrix;

out vec4 ourColor;
void main()
{
    float angle = radians(gl_VertexID * 5); 
    mat4 rotation = 
    mat4(cos(angle), 0.0, sin(angle), 0.0,
    0.0, 1.0, 0.0, 0.0,
    -sin(angle), 0.0, cos(angle), 0.0,
    0.0, 0.0, 0.0, 1.0);
    vec4 finalPosition = mv_matrix * rotation * vec4(position, 1.0);

    gl_Position = projection_matrix * finalPosition;
}