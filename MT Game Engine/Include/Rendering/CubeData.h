#pragma once

#include <vector>

#include <GL/glew.h>

#include "Math/Vec.h"
#include "Rendering/Texture/CubeTexture.h"

namespace mtge {
	class CubeData {
	private:
		CubeTexture *cubeTexture = nullptr;

	public:
		static const unsigned int ELEMENTS_PER_VERTEX = 5;
		static const unsigned int FACE_VERTEX_BUFFER_LENGTH = 30;
		static const unsigned int FACE_VERTEX_BUFFER_SIZE = FACE_VERTEX_BUFFER_LENGTH * sizeof(float);
		static const unsigned int VERTEX_BUFFER_LENGTH = FACE_VERTEX_BUFFER_LENGTH * 6;
		static const unsigned int VERTEX_BUFFER_SIZE = VERTEX_BUFFER_LENGTH * sizeof(float);

		CubeData(CubeTexture *cubeTexture);
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
			-1.0f,  1.0f, -1.0f, cubeTexture->topTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			-1.0f,  1.0f,  1.0f, cubeTexture->topTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->topTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			 1.0f,  1.0f,  1.0f, cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, cubeTexture->topTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f,  1.0f,  1.0f, cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			 1.0f,  1.0f, -1.0f, cubeTexture->topTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->topTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};
		float bottomFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f, -1.0f, -1.0f, cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getT(),   //Bottom Left
			 1.0f, -1.0f,  1.0f, cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getT(),     //Top Right
			-1.0f, -1.0f,  1.0f, cubeTexture->bottomTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->bottomTexAtlasSegment->TOP_LEFT.getT(),      //Top Left
			//Triangle 2
			-1.0f, -1.0f, -1.0f, cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			 1.0f, -1.0f, -1.0f, cubeTexture->bottomTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->bottomTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			 1.0f, -1.0f,  1.0f, cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};
		float leftFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, cubeTexture->leftTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			-1.0f, -1.0f, -1.0f, cubeTexture->leftTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->leftTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			-1.0f, -1.0f,  1.0f, cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, cubeTexture->leftTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			-1.0f, -1.0f,  1.0f, cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			-1.0f,  1.0f,  1.0f, cubeTexture->leftTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->leftTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};
		float rightFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			 1.0f,  1.0f,  1.0f, cubeTexture->rightTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f, -1.0f,  1.0f, cubeTexture->rightTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->rightTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			 1.0f, -1.0f, -1.0f, cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			 1.0f,  1.0f,  1.0f, cubeTexture->rightTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f, -1.0f, -1.0f, cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			 1.0f,  1.0f, -1.0f, cubeTexture->rightTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->rightTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};
		float frontFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			-1.0f, -1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->frontTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			 1.0f, -1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f, -1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			 1.0f,  1.0f,  1.0f, cubeTexture->frontTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->frontTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};
		float backFace[FACE_VERTEX_BUFFER_LENGTH] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, cubeTexture->backTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			 1.0f, -1.0f, -1.0f, cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			-1.0f, -1.0f, -1.0f, cubeTexture->backTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->backTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, cubeTexture->backTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			 1.0f,  1.0f, -1.0f, cubeTexture->backTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->backTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f, -1.0f, -1.0f, cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
		};

		void transformFace(float face[FACE_VERTEX_BUFFER_LENGTH], math::Vec3 offset, float);
	};
}