#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture/Texture.h"
#include "Math/Vec.h"
#include "Math/Mat.h"

namespace mtge {
	class Skybox {
	private:
		static const unsigned int VERTEX_BUFFER_LENGTH = 108;
		static const unsigned int VERTEX_BUFFER_SIZE = sizeof(float) * VERTEX_BUFFER_LENGTH;
		static const float VERTEX_BUFFER[VERTEX_BUFFER_LENGTH];

		static unsigned int vertexArrayID;
		static unsigned int vertexBufferID;

	public:
		static void init();
		static void render(glm::mat4 projectionMatrix, math::Mat<float, 4, 4> viewMatrix);
		static void freeResources();
	};
}