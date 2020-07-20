#include "Rendering/CubeData.h"

namespace mtge {
	//Constructor
	CubeData::CubeData(CubeTexture *cubeTexture) : cubeTexture(cubeTexture) {}

	//Public
	void CubeData::addCubeToBuffer(
		float *vertexBuffer,
		unsigned int &vertexBufferLength,
		math::Vec<unsigned int, 3> indices,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		float **facesForIndices = cubeTexture->faces[indices.getX()][indices.getY()][indices.getZ()];

		if (!hasTopNeighbor) {
			std::copy(facesForIndices[0], facesForIndices[0] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
		if (!hasBottomNeighbor) {
			std::copy(facesForIndices[1], facesForIndices[1] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
		if (!hasLeftNeighbor) {
			std::copy(facesForIndices[2], facesForIndices[2] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
		if (!hasRightNeighbor) {
			std::copy(facesForIndices[3], facesForIndices[3] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
		if (!hasFrontNeighbor) {
			std::copy(facesForIndices[4], facesForIndices[4] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
		if (!hasBackNeighbor) {
			std::copy(facesForIndices[5], facesForIndices[5] + FACE_VERTEX_BUFFER_LENGTH, vertexBuffer + vertexBufferLength);
			vertexBufferLength += FACE_VERTEX_BUFFER_LENGTH;
		}
	}
}