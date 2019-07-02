#version 330 core

layout(location = 0) in vec3 vertexPositions;
layout(location = 1) in vec3 vertexColors;
layout(location = 2) in vec2 vertexTextureCoord;

out vec3 fragmentColors;
out vec2 fragmentTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(vertexPositions, 1.0f);
	fragmentColors = vertexColors;
	fragmentTextureCoord = vertexTextureCoord;
}