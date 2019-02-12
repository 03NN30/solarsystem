#version 330 core
uniform vec3 viewPos;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform float LightConstant;
uniform float LightLinear;
uniform float LightQuadratic;
uniform float Shininess;
uniform float Reflectivity;
uniform float AmbientVal;
uniform bool outline;
uniform bool planetBloom;
uniform sampler2D texture1;

in vec3 fragPos;
in vec3 normal;
in vec2 passTexCoord;

out vec4 out_Color;

void main() {
    vec3 viewDir = normalize(viewPos - fragPos);
    float angle = degrees(acos(dot(normal, viewDir) / (length(normal) * length(viewDir))));
    
    if (angle > 80.0 && angle < 100.0 && outline) {
        out_Color = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        // ambient
        vec3 ambient = AmbientVal * vec3(texture(texture1, passTexCoord)).xyz;

        // diffuse
        vec3 lightDirection = normalize(LightPosition - fragPos);
        float diff = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = diff * vec3(texture(texture1, passTexCoord)).xyz;

        // specular
        vec3 centreDirection = normalize(lightDirection + viewDir);  
        float spec = pow(max(dot(normal, centreDirection), 0.0), Shininess);
        vec3 specular = vec3(Reflectivity) * spec;

        // attenuation
        float distance = length(LightPosition - fragPos);
        float attenuation = LightIntensity / (LightConstant + LightLinear * distance + LightQuadratic * (distance * distance));  
    
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;
        vec3 result = ambient + diffuse + specular;
        
        if (planetBloom) {
            out_Color = vec4(result, 1.0);
        } else {
            vec3 normResult = normalize(result);
            out_Color = vec4(normResult, 1.0);
        }
    }
}
