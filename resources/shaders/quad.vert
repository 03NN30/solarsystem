#version 330 core
layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 pass_Texture_Coordinates;

void main()
{
    pass_Texture_Coordinates = in_TexCoord;
    gl_Position = vec4(in_Position, 0.0, 1.0); 
}  