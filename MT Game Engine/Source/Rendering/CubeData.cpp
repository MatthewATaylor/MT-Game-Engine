#include "Rendering/CubeData.h"

namespace mtge {
	//Constructor
	CubeData::CubeData(CubeTexture *cubeTexture) : cubeTexture(cubeTexture) {}

	//Public
	void CubeData::addCubeToBuffer(
		std::vector<float> *vertexBuffer,
		math::Vec<unsigned int, 3> indices,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		float **facesForIndices = cubeTexture->faces[indices.getX()][indices.getY()][indices.getZ()];

		if (!hasTopNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[0], facesForIndices[0] + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBottomNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[1], facesForIndices[1] + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasLeftNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[2], facesForIndices[2] + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasRightNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[3], facesForIndices[3] + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasFrontNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[4], facesForIndices[4] + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBackNeighbor) {
			vertexBuffer->insert(vertexBuffer->end(), facesForIndices[5], facesForIndices[5] + FACE_VERTEX_BUFFER_LENGTH);
		}
	}
}