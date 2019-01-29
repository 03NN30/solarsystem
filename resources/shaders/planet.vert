#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragPos;

out vec2 passTexCoord;

void main(void) {
	// calculate fragment's position vector for calculating light ray
	fragPos = vec3(model * vec4(aPosition, 1.0));
	
	gl_Position = projection * view * model * vec4(aPosition, 1.0);

	// calculate perpendicular vector to vertices in regard to transformations
	normal = normalize(mat3(transpose(inverse(model))) * aNormal);
	
	passTexCoord = aTexCoord;
}
