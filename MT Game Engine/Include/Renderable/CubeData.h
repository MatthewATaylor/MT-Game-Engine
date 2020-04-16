#pragma once

#include <GL/glew.h>

#include "../Math/Vec.h"

namespace mtge {
	class CubeData {
	public:
		static const unsigned int FACE_VERTEX_BUFFER_LENGTH = 36;
		static const unsigned int FACE_VERTEX_BUFFER_SIZE = FACE_VERTEX_BUFFER_LENGTH * sizeof(float);
		static const unsigned int VERTEX_BUFFER_LENGTH = 216;
		static const unsigned int VERTEX_BUFFER_SIZE = VERTEX_BUFFER_LENGTH * sizeof(float);
		float topFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Right
		};
		float bottomFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Top Right
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			//Triangle 2
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			 1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f   //Top Right
		};
		float leftFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Top Left
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Left
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Top Left
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Right
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Top Right
		};
		float rightFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Top Left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Right
			//Triangle 2
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Top Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Top Right
		};
		float frontFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Bottom Right
			//Triangle 2
			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Top Right
		};
		float backFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Right
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
			-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		};

		static void resetBufferOffsetCounter();
		static unsigned int getBufferOffsetCounter();
		void addBufferSubData(
			math::Vec<float, 3> offset,
			float scale,
			bool hasTopNeighbor,
			bool hasBottomNeighbor,
			bool hasLeftNeighbor,
			bool hasRightNeighbor,
			bool hasFrontNeighbor,
			bool hasBackNeighbor
		);

	private:
		static unsigned int bufferOffsetSize;

		void transformFace(float face[FACE_VERTEX_BUFFER_LENGTH], math::Vec<float, 3> offset, float);
	};
}