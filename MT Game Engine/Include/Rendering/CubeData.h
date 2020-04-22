#pragma once

#include <vector>

#include <GL/glew.h>

#include "Math/Vec.h"
#include "Rendering/Texture/TextureAtlasSegment.h"

namespace mtge {
	class CubeData {
	private:
		TextureAtlasSegment *texAtlasSegment = nullptr;

	public:
		static const unsigned int ELEMENTS_PER_VERTEX = 5;
		static const unsigned int FACE_VERTEX_BUFFER_LENGTH = 30;
		static const unsigned int FACE_VERTEX_BUFFER_SIZE = FACE_VERTEX_BUFFER_LENGTH * sizeof(float);
		static const unsigned int VERTEX_BUFFER_LENGTH = FACE_VERTEX_BUFFER_LENGTH * 6;
		static const unsigned int VERTEX_BUFFER_SIZE = VERTEX_BUFFER_LENGTH * sizeof(float);

		CubeData(TextureAtlasSegment *texAtlasSegment);
		void addCubeToBuffer(
			std::vector<float> *vertexBuffer,
			math::Vec3 offset,
			float scale,
			bool hasTopNeighbor,
			bool hasBottomNeighbor,
			bool hasLeftNeighbor,
			bool hasRightNeighbor,
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);

	private:
		float topFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::TOP), //Top Left
			-1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(0, CoordBuffer_T::BOTTOM), //Bottom Left
			 1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(0, CoordBuffer_T::BOTTOM), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::TOP), //Top Left
			 1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(0, CoordBuffer_T::BOTTOM), //Bottom Right
			 1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::TOP), //Top Right
		};
		float bottomFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Left
			 1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Right
			-1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Left
			//Triangle 2
			-1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Left
			 1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Right
			 1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Right
		};
		float leftFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(0, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Left
			-1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(0, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Left
			-1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(0, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Left
			-1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Right
			-1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Right
		};
		float rightFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			 1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Left
			 1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Left
			 1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(3, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Right
			//Triangle 2
			 1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Left
			 1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(3, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::BOTTOM), //Bottom Right
			 1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(3, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::TOP), //Top Right
		};
		float frontFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::TOP), //Top Left
			-1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::BOTTOM), //Bottom Left
			 1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::BOTTOM), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::TOP), //Top Left
			 1.0f, -1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(1, CoordBuffer_T::BOTTOM), //Bottom Right
			 1.0f,  1.0f,  1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(2, CoordBuffer_T::TOP), //Top Right
		};
		float backFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(4, CoordBuffer_T::TOP), //Top Right
			 1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::BOTTOM), //Bottom Left
			-1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::BOTTOM), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(2, CoordBuffer_S::RIGHT), texAtlasSegment->getTexCoord_T(4, CoordBuffer_T::TOP), //Top Right
			 1.0f,  1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(4, CoordBuffer_T::TOP), //Top Left
			 1.0f, -1.0f, -1.0f, texAtlasSegment->getTexCoord_S(1, CoordBuffer_S::LEFT), texAtlasSegment->getTexCoord_T(3, CoordBuffer_T::BOTTOM), //Bottom Left
		};

		void transformFace(float face[FACE_VERTEX_BUFFER_LENGTH], math::Vec3 offset, float);
	};
}