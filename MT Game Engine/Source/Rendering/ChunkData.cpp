#include "Rendering/ChunkData.h"

namespace mtge {
	//Public
	void ChunkData::addCube(
		CubeTexture *cubeTexture,
		math::Vec<unsigned int, 3> indices,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		CubeData cubeData(cubeTexture);
		cubeData.addCubeToBuffer(
			&vertexBuffer,
			indices,
			hasTopNeighbor,
			hasBottomNeighbor,
			hasLeftNeighbor,
			hasRightNeighbor,
			hasFrontNeighbor,
			hasBackNeighbor
		);
	}
	int ChunkData::getVerticesInBuffer() {
		return vertexBuffer.size() / CubeData::ELEMENTS_PER_VERTEX;
	}
	void ChunkData::sendBuffer() {
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), vertexBuffer.data(), GL_STATIC_DRAW);
	}
}