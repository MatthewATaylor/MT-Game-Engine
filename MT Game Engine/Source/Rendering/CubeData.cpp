#include "Rendering/CubeData.h"

namespace mtge {
	//Constructor
	CubeData::CubeData(CubeTexture *cubeTexture) : cubeTexture(cubeTexture) {}

	//Public
	void CubeData::addCubeToBuffer(
		std::vector<float> *vertexBuffer,
		math::Vec3 offset,
		float scale,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		if (!hasTopNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBottomNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasLeftNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasRightNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasFrontNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBackNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), cubeTexture->face, cubeTexture->face + FACE_VERTEX_BUFFER_LENGTH);
		}
	}
}