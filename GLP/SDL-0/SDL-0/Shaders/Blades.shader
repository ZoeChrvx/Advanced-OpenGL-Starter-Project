#version 330 core
in vec2 texCoord;

out vec2 TexCoord;

void main()
{
    vec4 offset = vec4(float(gl_InstanceID >> 10) - 512.0, 0.0f, float(gl_InstanceID & Ox3FF) - 512.0, 0.0f);
    int number1 = random(gl_InstanceID, 3);
    int number2 = random(number1, 2);
    vec2 texcoord = offset.xz / 1024.0 + vec2(0.5);
    
    float bend_factor = texture(bend_texture, texCoord).r * 2.0;            
    float bend_amount = cos(vVertex.y);     
                                   
    // Make grass angle change with texture move
    vec2 texcoord_angle = texCoord + time * 0.05;
    float angle = texture(orientation_texture, texCoord_angle).r * 2.0 * 3.141592;
    mat4 rot = construct_rotation_matrix(angle);                            
    vec4 position = (rot * (vVertex + vec4(0.0, 0.0, bend_amount * bend_factor, 0.0))) + offset;
    …

    
    offset += vec4(float(number1 & 0xFF) / 256.0, 0.0f, float(number2 & 0xFF) / 256.0, 0.0f);
    position *= vec4(1.0, texture(length_texture, texCoord).r * 0.9 + 0.3, 1.0, 1.0);
    gl_Position = mvp_matrix * position; 
    color = texture(grasspalette_texture, texture(grasscolor_texture, texCoord).r) + vec4(random_vector(gl_InstanceID).xyz * vec3(0.1, 0.5, 0.1), 1.0);  

}