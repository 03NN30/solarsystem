#version 330 core
out vec4 out_Color;

in vec2 pass_Texture_Coordinates;

uniform sampler2D texture1;
uniform bool blur;
uniform bool grayscale;
uniform bool verticalMirror;
uniform bool horizontalMirror;
uniform float exposure;
uniform float gamma;

const float offset = 1.0 / 300.0;  

void main() {

    //const float gamma = 2.2;
    vec3 hdrColor = texture(texture1, pass_Texture_Coordinates).rgb;
    // reinhard
    // vec3 result = hdrColor / (hdrColor + vec3(1.0));
    // exposure tone mapping
    vec3 result  = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma correction 
    result  = pow(result , vec3(1.0 / gamma));
  
    out_Color = vec4(result , 1.0);
    //out_Color = texture(texture1, pass_Texture_Coordinates);
    
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
            sampleTex[i] = vec3(texture(texture1, pass_Texture_Coordinates.st + offsets[i]));
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++) {
            col += sampleTex[i] * kernel[i];
        }

        out_Color = vec4(col, 1.0);
    }

    if (verticalMirror && horizontalMirror) {
        out_Color = texture(texture1, vec2(1 - pass_Texture_Coordinates.x, 1 - pass_Texture_Coordinates.y));
    }
    else if (horizontalMirror) {
    	out_Color = texture(texture1, vec2(pass_Texture_Coordinates.x, 1 - pass_Texture_Coordinates.y));
    }
    else if (verticalMirror) {
        out_Color = texture(texture1, vec2(1 - pass_Texture_Coordinates.x, pass_Texture_Coordinates.y));
    }

    if (grayscale) {
        float luminance = 0.2126 * out_Color.r + 0.7152 * out_Color.g + 0.0722 * out_Color.b;
        out_Color = vec4(luminance, luminance, luminance, 1.0);
    }

} 

