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
			float topFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->topTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				//Triangle 2
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->topTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->topTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			};
			vertexBuffer->insert(vertexBuffer->end(), topFace, topFace + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBottomNeighbor) {
			float bottomFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getT(),   //Bottom Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getT(),     //Top Right
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->bottomTexAtlasSegment->TOP_LEFT.getT(),      //Top Left
				//Triangle 2
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->bottomTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->bottomTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->bottomTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			};
			vertexBuffer->insert(vertexBuffer->end(), bottomFace, bottomFace + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasLeftNeighbor) {
			float leftFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->leftTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				//Triangle 2
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->leftTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->leftTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			};
			vertexBuffer->insert(vertexBuffer->end(), leftFace, leftFace + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasRightNeighbor) {
			float rightFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->rightTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				//Triangle 2
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->rightTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->rightTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			};
			vertexBuffer->insert(vertexBuffer->end(), rightFace, rightFace + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasFrontNeighbor) {
			float frontFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->frontTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				//Triangle 2
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(),  1.0f / scale + offset.getZ(), cubeTexture->frontTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->frontTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
			};
			vertexBuffer->insert(vertexBuffer->end(), frontFace, frontFace + FACE_VERTEX_BUFFER_LENGTH);
		}
		if (!hasBackNeighbor) {
			float backFace[FACE_VERTEX_BUFFER_LENGTH] = {
				//Triangle 1
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
				-1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->BOTTOM_RIGHT.getS(), cubeTexture->backTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
				//Triangle 2
				-1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->TOP_RIGHT.getS(),    cubeTexture->backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
				 1.0f / scale + offset.getX(),  1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->TOP_LEFT.getS(),     cubeTexture->backTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
				 1.0f / scale + offset.getX(), -1.0f / scale + offset.getY(), -1.0f / scale + offset.getZ(), cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getS(),  cubeTexture->backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			};
			vertexBuffer->insert(vertexBuffer->end(), backFace, backFace + FACE_VERTEX_BUFFER_LENGTH);
		}
	}
}