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
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

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
        float surface, clouds, lights; 

        surface = 0.5; clouds = 1.0 - surface;
        vec3 tex12 = vec3(texture2D(texture1, passTexCoord) * surface + 
                          texture2D(texture2, passTexCoord) * clouds).xyz;
        
        clouds = 0.5; lights = 1.0 - clouds;
        vec3 tex23 = vec3(texture2D(texture2, passTexCoord) * clouds +
                          texture2D(texture3, passTexCoord) * lights).xyz;
       
        surface = 0.5; clouds = 0.5; lights = 1.0 - surface - clouds;
        vec3 tex123 = vec3(texture2D(texture1, passTexCoord) * surface + 
                           texture2D(texture2, passTexCoord) * clouds +
                           texture2D(texture3, passTexCoord) * lights).xyz;
        // ambient
        vec3 ambient = AmbientVal * tex12;

        // diffuse
        vec3 lightDirection = normalize(LightPosition - fragPos);
        float diff = max(dot(lightDirection, normal), 0.0);
        vec3 diffuse = diff * tex12;

        // specular
        vec3 reflectDir = reflect(-lightDirection, normal);
        vec3 centreDirection = normalize(lightDirection + viewDir);  
        float spec = pow(max(dot(normal, centreDirection), 0.0), Shininess);
        vec3 specular = vec3(Reflectivity) * spec;

        // attenuation
        float distance = length(LightPosition - fragPos);
        float attenuation = LightIntensity / (LightConstant + LightLinear * distance + LightQuadratic * (distance * distance));  
    
        ambient  *= attenuation;
        diffuse  *= attenuation;
        specular *= attenuation;

        out_Color = vec4(ambient + diffuse + specular, 1.0);
    }
}
