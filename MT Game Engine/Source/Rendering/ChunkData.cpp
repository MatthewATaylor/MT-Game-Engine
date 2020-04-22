#include "Rendering/ChunkData.h"

namespace mtge {
	//Constructor
	ChunkData::ChunkData(TextureAtlasSegment *texAtlasSegment) {
		this->texAtlasSegment = texAtlasSegment;
	}

	//Public
	void ChunkData::addCube(
		math::Vec3 offset,
		float scale,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		CubeData cubeData(texAtlasSegment);
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
	int ChunkData::getVerticesInBuffer() {
		return vertexBuffer.size() / CubeData::ELEMENTS_PER_VERTEX;
	}
	void ChunkData::sendBuffer() {
		glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), vertexBuffer.data(), GL_STATIC_DRAW);
	}
}