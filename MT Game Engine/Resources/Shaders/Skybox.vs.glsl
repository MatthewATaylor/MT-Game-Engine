#version 330 core

layout(location = 0) in vec3 vertexPositions;

out vec3 fragmentTextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec4 transformedPosition = projection * view * model * vec4(vertexPositions, 1.0f);
	gl_Position = transformedPosition.xyww;
	fragmentTextureCoord = vertexPositions;
}