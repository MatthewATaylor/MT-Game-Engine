#include "Rendering/CubeData.h"

namespace mtge {
	//Constructor
	CubeData::CubeData(TextureAtlasSegment *texAtlasSegment) : texAtlasSegment(texAtlasSegment) {}

	//Private
	unsigned int CubeData::bufferOffsetSize = 0;

	void CubeData::transformFace(float face[FACE_VERTEX_BUFFER_LENGTH], math::Vec<float, 3> offset, float scale) {
		for (unsigned int i = 0; i < FACE_VERTEX_BUFFER_LENGTH - 2; i += 5) {
			float &x = face[i];
			float &y = face[i + 1];
			float &z = face[i + 2];

			x /= scale;
			y /= scale;
			z /= scale;

			x += offset.getX();
			y += offset.getY();
			z += offset.getZ();
		}
	}

	//Public
	void CubeData::resetBufferOffsetCounter() {
		bufferOffsetSize = 0;
	}
	unsigned int CubeData::getVerticesAdded() {
		return bufferOffsetSize / ELEMENTS_PER_VERTEX / sizeof(float);
	}
	void CubeData::addBufferSubData(
		math::Vec<float, 3> offset,
		float scale,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		if (!hasTopNeighbor) {
			transformFace(topFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, topFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasBottomNeighbor) {
			transformFace(bottomFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, bottomFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasLeftNeighbor) {
			transformFace(leftFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, leftFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasRightNeighbor) {
			transformFace(rightFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, rightFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasFrontNeighbor) {
			transformFace(frontFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, frontFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasBackNeighbor) {
			transformFace(backFace, offset, scale);
			glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, backFace);
			bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
	}
}