#version 330 core

in vec3 fragmentColors;
in vec2 fragmentTextureCoord;

out vec4 finalFragmentColor;

uniform sampler2D texture1;

void main() {
	finalFragmentColor = texture(texture1, fragmentTextureCoord);
}