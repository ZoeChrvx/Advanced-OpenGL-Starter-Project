#version 330 core
in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 projection;

out vec3 FragPos;  
out float DistanceCenter;  


void main()
{
    vec3 displacedPos = pos + normalize(pos);  

    gl_Position = projection * mv_matrix * vec4(displacedPos, 1.0);
    FragPos = displacedPos;  
    DistanceCenter = length(displacedPos);  
}