#pragma once

#include "../Math/Vec.h"

namespace mtge {
	class CubeData {
	public:
		static const unsigned int VERTEX_BUFFER_LENGTH = 216;
		static const unsigned int VERTEX_BUFFER_SIZE = VERTEX_BUFFER_LENGTH * sizeof(float);
		float* vertexBuffer = nullptr;

		CubeData(
			math::Vec<float, 3> offset, 
			float scale, 
			bool hasTopNeighbor, 
			bool hasBottomNeighbor, 
			bool hasLeftNeighbor, 
			bool hasRightNeighbor, 
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);
		~CubeData();
	};
}