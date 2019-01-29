#version 150
out vec4 out_Color;

in vec2 outTexCoord;

uniform sampler2D ColorTex;

void main() {

    out_Color = texture(ColorTex, outTexCoord);
}
