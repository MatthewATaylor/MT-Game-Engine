#include "Rendering/ChunkData.h"

namespace mtge {
	//Constructor
	ChunkData::ChunkData() {
		vertexBuffer = new float[MAX_VERTEX_BUFFER_SIZE];
	}

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
			vertexBuffer,
			vertexBufferLength,
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
		return vertexBufferLength / CubeData::ELEMENTS_PER_VERTEX;
	}
	void ChunkData::sendBuffer() {
		glBufferData(GL_ARRAY_BUFFER, vertexBufferLength * sizeof(float), vertexBuffer, GL_STATIC_DRAW);
	}

	//Destructor
	ChunkData::~ChunkData() {
		delete[] vertexBuffer;
	}
}