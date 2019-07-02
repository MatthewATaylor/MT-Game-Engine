#version 330 core

in vec3 fragmentTextureCoord;

out vec4 finalFragmentColor;

uniform samplerCube skybox;

void main() {
	finalFragmentColor = texture(skybox, fragmentTextureCoord);
}