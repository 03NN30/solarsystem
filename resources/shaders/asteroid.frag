#version 330 core

out vec4 out_Color;

in vec2 pass_texCoord;
in vec3 pass_normal;
in vec3 pass_fragPos;

uniform sampler2D texture1;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main() {
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 lightDirection = normalize(lightPosition - pass_fragPos);
    float diff = max(dot(lightDirection, pass_normal), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - pass_fragPos);
    vec3 reflectDir = reflect(-lightDirection, pass_normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * texture(texture1, pass_texCoord).xyz;
    out_Color = vec4(result, 1.0);
}