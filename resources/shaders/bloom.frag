#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;
uniform sampler2D bloomBlur;
uniform float exposure;
uniform float gamma;
uniform bool blur;
uniform bool grayscale;
uniform bool verticalMirror;
uniform bool horizontalMirror;

const float offset = 1.0 / 300.0;  

void main() {             
    vec3 hdrColor = texture(scene, TexCoords).rgb;      
    vec3 bloomColor = texture(bloomBlur, TexCoords).rgb;
    
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);

    if (blur) {
        vec2 offsets[9] = vec2[](
            vec2(-offset,  offset), // top-left
            vec2( 0.0f,    offset), // top-center
            vec2( offset,  offset), // top-right
            vec2(-offset,  0.0f),   // center-left
            vec2( 0.0f,    0.0f),   // center-center
            vec2( offset,  0.0f),   // center-right
            vec2(-offset, -offset), // bottom-left
            vec2( 0.0f,   -offset), // bottom-center
            vec2( offset, -offset)  // bottom-right    
        );        

        float kernel[9] = float[](
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16  
        );

        vec3 sampleTex[9];
        for(int i = 0; i < 9; i++) {
            sampleTex[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++) {
            col += sampleTex[i] * kernel[i];
        }

        FragColor = vec4(col, 1.0);
    }

    if (verticalMirror && horizontalMirror) {
        FragColor = texture(scene, vec2(1 - TexCoords.x, 1 - TexCoords.y));
    }
    else if (horizontalMirror) {
    	FragColor = texture(scene, vec2(TexCoords.x, 1 - TexCoords.y));
    }
    else if (verticalMirror) {
        FragColor = texture(scene, vec2(1 - TexCoords.x, TexCoords.y));
    }

    if (grayscale) {
        float luminance = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
        FragColor = vec4(luminance, luminance, luminance, 1.0);
    }
}

