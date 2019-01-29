#version 330 core
layout (location = 0) in float aPos1;
layout (location = 1) in float aPos2;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(void) {
	gl_Position = projection * view * model * vec4(aPos2, 0.0, aPos1, 1.0);
}