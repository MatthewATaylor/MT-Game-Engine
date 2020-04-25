#include "Rendering/ChunkData.h"

namespace mtge {
	//Public
	void ChunkData::addSolidCube(
		CubeTexture *cubeTexture,
		math::Vec3 offset,
		float scale,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		CubeData cubeData(cubeTexture);
		cubeData.addCubeToBuffer(
			&vertexBuffer,
			offset,
			scale,
			hasTopNeighbor,
			hasBottomNeighbor,
			hasLeftNeighbor,
			hasRightNeighbor,
			hasFrontNeighbor,
			hasBackNeighbor
		);
	}
	void ChunkData::addWaterToQueue(
		CubeTexture *cubeTexture,
		math::Vec3 offset,
		float scale,
		bool hasTopNeighbor) {

		CubeData cubeData(cubeTexture);
		cubeData.addCubeToBuffer(
			&waterQueue,
			offset,
			scale,
			hasTopNeighbor,
			true,
			true,
			true,
			true,
			true
		);
	}
	void ChunkData::addTransparentCubesToBuffer() {
		vertexBuffer.insert(vertexBuffer.end(), waterQueue.begin(), waterQueue.end());
		waterQueue.clear();
	}
	int ChunkData::getVerticesInBuffer() {
		return vertexBuffer.size() / CubeData::ELEMENTS_PER_VERTEX;
	}
	void ChunkData::sendBuffer() {
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), vertexBuffer.data(), GL_STATIC_DRAW);
	}
}