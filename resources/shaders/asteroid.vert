#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 pass_normal;
out vec2 pass_texCoord;
out vec3 pass_fragPos;

void main() {
    pass_fragPos = vec3(model * vec4(aPos, 1.0));
    pass_texCoord = aTexCoord;
    pass_normal = normalize(aNormal);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}