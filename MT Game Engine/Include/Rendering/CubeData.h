#pragma once

#include <vector>

#include <GL/glew.h>

#include "Math/Vec.h"
#include "Rendering/Texture/CubeTexture.h"

namespace mtge {
	class CubeData {
	private:
		CubeTexture *cubeTexture = nullptr;

	public:
		static const unsigned int ELEMENTS_PER_VERTEX = 5;
		static const unsigned int FACE_VERTEX_BUFFER_LENGTH = 30;
		static const unsigned int FACE_VERTEX_BUFFER_SIZE = FACE_VERTEX_BUFFER_LENGTH * sizeof(float);
		static const unsigned int VERTEX_BUFFER_LENGTH = FACE_VERTEX_BUFFER_LENGTH * 6;
		static const unsigned int VERTEX_BUFFER_SIZE = VERTEX_BUFFER_LENGTH * sizeof(float);

		CubeData(CubeTexture *cubeTexture);
		void addCubeToBuffer(
			std::vector<float> *vertexBuffer,
			math::Vec3 offset,
			float scale,
			bool hasTopNeighbor,
			bool hasBottomNeighbor,
			bool hasLeftNeighbor,
			bool hasRightNeighbor,
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);
	};
}