#include "../../Include/Renderable/CubeData.h"

namespace mtge {
	//Public
	CubeData::CubeData(
		math::Vec<float, 3> offset,
		float scale,
		bool hasTopNeighbor,
		bool hasBottomNeighbor,
		bool hasLeftNeighbor,
		bool hasRightNeighbor,
		bool hasFrontNeighbor,
		bool hasBackNeighbor) {

		vertexBuffer = new float[VERTEX_BUFFER_LENGTH] {
			/*
			//Positions-----------Colors-------------
			//Triangle 1, Front
			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			-1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Bottom Right
			//Triangle 2, Front
			-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  //Top Right

			//Triangle 1, Back
			-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Right
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
			-1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Right
			//Triangle 2, Back
			-1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Top Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left

			//Triangle 1, Left
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Top Left
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Left
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Right
			//Triangle 2, Left
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  //Top Left
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Bottom Right
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  //Top Right

			//Triangle 1, Right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Top Left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Right
			//Triangle 2, Right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  //Top Left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  //Top Right

			//Triangle 1, Top
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			//Triangle 2, Top
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Top Right

			//Triangle 1, Bottom
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Top Right
			-1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f,  //Top Left
			//Triangle 2, Bottom
			-1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Left
			 1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  1.0f,  //Bottom Right
			 1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  1.0f   //Top Right
			 */

			 //Positions-----------Colors-------------
 //Triangle 1, Front
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  //Top Left
				-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  //Bottom Left
				0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  //Bottom Right
			   //Triangle 2, Front
				-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  //Top Left
				0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  //Bottom Right
				0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  //Top Right

			   //Triangle 1, Back
				-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Top Right
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Bottom Left
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Bottom Right
				//Triangle 2, Back
				-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Top Right
				0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Top Left
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  //Bottom Left

			   //Triangle 1, Left
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  //Top Left
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  //Bottom Left
				-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  //Bottom Right
				//Triangle 2, Left
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  //Top Left
				-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  //Bottom Right
				-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  //Top Right

				//Triangle 1, Right
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  //Top Left
				0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  //Bottom Left
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  //Bottom Right
			   //Triangle 2, Right
				0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,  //Top Left
				0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  //Bottom Right
				0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f,  //Top Right

			   //Triangle 1, Top
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Top Left
				-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Left
				0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Right
			   //Triangle 2, Top
				-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Top Left
				0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Right
				0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Top Right

			   //Triangle 1, Bottom
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Left
				0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  //Top Right
				-0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f,  //Top Left
				//Triangle 2, Bottom
				-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Left
				0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,  //Bottom Right
				0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f   //Top Right
		};

		for (unsigned int i = 0; i < VERTEX_BUFFER_LENGTH - 3; i += 6) {
			float &x = vertexBuffer[i];
			float &y = vertexBuffer[i + 1];
			float &z = vertexBuffer[i + 2];

			x /= scale;
			y /= scale;
			z /= scale;

			x += offset.getX();
			y += offset.getY();
			z += offset.getZ();
		}
	}
	CubeData::~CubeData() {
		delete[] vertexBuffer;
	}
}