#include "Rendering/CubeData.h"

namespace mtge {
	//Constructor
	CubeData::CubeData(TextureAtlasSegment *texAtlasSegment) : texAtlasSegment(texAtlasSegment) {}

	//Private
	void CubeData::transformFace(float face[FACE_VERTEX_BUFFER_LENGTH], math::Vec3 offset, float scale) {
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

		/*if (!hasTopNeighbor) {
			transformFace(topFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), topFace, topFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, topFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}*/
		if (!hasBottomNeighbor) {
			transformFace(bottomFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), bottomFace, bottomFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, bottomFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasLeftNeighbor) {
			transformFace(leftFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), leftFace, leftFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, leftFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasRightNeighbor) {
			transformFace(rightFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), rightFace, rightFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, rightFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasFrontNeighbor) {
			transformFace(frontFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), frontFace, frontFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, frontFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
		if (!hasBackNeighbor) {
			transformFace(backFace, offset, scale);
			vertexBuffer->insert(vertexBuffer->end(), backFace, backFace + FACE_VERTEX_BUFFER_LENGTH);
			//glBufferSubData(GL_ARRAY_BUFFER, bufferOffsetSize, FACE_VERTEX_BUFFER_SIZE, backFace);
			//bufferOffsetSize += FACE_VERTEX_BUFFER_SIZE;
		}
	}
}