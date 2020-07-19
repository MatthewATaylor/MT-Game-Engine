#include "Rendering/Texture/CubeTexture.h"

namespace mtge {
	//Constructor
	CubeTexture::CubeTexture(
		TextureAtlasSegment *frontTexAtlasSegment,
		TextureAtlasSegment *backTexAtlasSegment,
		TextureAtlasSegment *leftTexAtlasSegment,
		TextureAtlasSegment *rightTexAtlasSegment,
		TextureAtlasSegment *topTexAtlasSegment,
		TextureAtlasSegment *bottomTexAtlasSegment) {

		this->frontTexAtlasSegment = frontTexAtlasSegment;
		this->backTexAtlasSegment = backTexAtlasSegment;
		this->leftTexAtlasSegment = leftTexAtlasSegment;
		this->rightTexAtlasSegment = rightTexAtlasSegment;
		this->topTexAtlasSegment = topTexAtlasSegment;
		this->bottomTexAtlasSegment = bottomTexAtlasSegment;

		genFaces();
	}
	CubeTexture::CubeTexture(
		TextureAtlasSegment *sideTexAtlasSegment,
		TextureAtlasSegment *topTexAtlasSegment,
		TextureAtlasSegment *bottomTexAtlasSegment) {

		this->frontTexAtlasSegment = sideTexAtlasSegment;
		this->backTexAtlasSegment = sideTexAtlasSegment;
		this->leftTexAtlasSegment = sideTexAtlasSegment;
		this->rightTexAtlasSegment = sideTexAtlasSegment;
		this->topTexAtlasSegment = topTexAtlasSegment;
		this->bottomTexAtlasSegment = bottomTexAtlasSegment;

		genFaces();
	}
	CubeTexture::CubeTexture(
		TextureAtlasSegment *texAtlasSegment) {

		this->frontTexAtlasSegment = texAtlasSegment;
		this->backTexAtlasSegment = texAtlasSegment;
		this->leftTexAtlasSegment = texAtlasSegment;
		this->rightTexAtlasSegment = texAtlasSegment;
		this->topTexAtlasSegment = texAtlasSegment;
		this->bottomTexAtlasSegment = texAtlasSegment;

		genFaces();
	}

	//Private
	void CubeTexture::genFaces() {
		const float CUBE_SIZE = 2.0f / LENGTH_IN_CUBES;

		//Generate array of every possible vertex buffer array for each cube face
		faces = new float****[LENGTH_IN_CUBES];
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			faces[i] = new float***[LENGTH_IN_CUBES];
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				faces[i][j] = new float**[LENGTH_IN_CUBES];
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					//Array containing each face's vertex buffer array (top, bottom, front, back, left, right)
					faces[i][j][k] = new float*[6];

					for (unsigned int l = 0; l < 6; l++) {
						faces[i][j][k][l] = new float[FACE_VERTEX_BUFFER_LENGTH];
					}

					//Offsets for each cube in chunk
					float xOffset = -1.0f + CUBE_SIZE / 2 + i * CUBE_SIZE;
					float yOffset = -1.0f + CUBE_SIZE / 2 + j * CUBE_SIZE;
					float zOffset = -1.0f + CUBE_SIZE / 2 + k * CUBE_SIZE;

					float topFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->TOP_LEFT.getS(),     topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->BOTTOM_LEFT.getS(),  topTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->BOTTOM_RIGHT.getS(), topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						//Triangle 2
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->TOP_LEFT.getS(),     topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->BOTTOM_RIGHT.getS(), topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, topTexAtlasSegment->TOP_RIGHT.getS(),    topTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
					};
					std::copy(topFace, topFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][0]);

					float bottomFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  bottomTexAtlasSegment->BOTTOM_LEFT.getT(),   //Bottom Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->TOP_RIGHT.getS(),    bottomTexAtlasSegment->TOP_RIGHT.getT(),     //Top Right
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->TOP_LEFT.getS(),     bottomTexAtlasSegment->TOP_LEFT.getT(),      //Top Left
						//Triangle 2
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->BOTTOM_LEFT.getS(),  bottomTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->BOTTOM_RIGHT.getS(), bottomTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, bottomTexAtlasSegment->TOP_RIGHT.getS(),    bottomTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
					};
					std::copy(bottomFace, bottomFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][1]);

					float leftFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->TOP_LEFT.getS(),     leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->BOTTOM_LEFT.getS(),  leftTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->BOTTOM_RIGHT.getS(), leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						//Triangle 2
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->TOP_LEFT.getS(),     leftTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->BOTTOM_RIGHT.getS(), leftTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, leftTexAtlasSegment->TOP_RIGHT.getS(),    leftTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
					};
					std::copy(leftFace, leftFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][2]);

					float rightFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->TOP_LEFT.getS(),     rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->BOTTOM_LEFT.getS(),  rightTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->BOTTOM_RIGHT.getS(), rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						//Triangle 2
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->TOP_LEFT.getS(),     rightTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->BOTTOM_RIGHT.getS(), rightTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, rightTexAtlasSegment->TOP_RIGHT.getS(),    rightTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
					};
					std::copy(rightFace, rightFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][3]);

					float frontFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->TOP_LEFT.getS(),     frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->BOTTOM_LEFT.getS(),  frontTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->BOTTOM_RIGHT.getS(), frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						//Triangle 2
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->TOP_LEFT.getS(),     frontTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->BOTTOM_RIGHT.getS(), frontTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset,  1.0f / LENGTH_IN_CUBES + zOffset, frontTexAtlasSegment->TOP_RIGHT.getS(),    frontTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
					};
					std::copy(frontFace, frontFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][4]);

					float backFace[FACE_VERTEX_BUFFER_LENGTH] = {
						//Triangle 1
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->TOP_RIGHT.getS(),    backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->BOTTOM_LEFT.getS(),  backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
						-1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->BOTTOM_RIGHT.getS(), backTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
						//Triangle 2
						-1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->TOP_RIGHT.getS(),    backTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
						 1.0f / LENGTH_IN_CUBES + xOffset,  1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->TOP_LEFT.getS(),     backTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
						 1.0f / LENGTH_IN_CUBES + xOffset, -1.0f / LENGTH_IN_CUBES + yOffset, -1.0f / LENGTH_IN_CUBES + zOffset, backTexAtlasSegment->BOTTOM_LEFT.getS(),  backTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
					};
					std::copy(backFace, backFace + FACE_VERTEX_BUFFER_LENGTH, faces[i][j][k][5]);
				}
			}
		}
	}

	//Destructor
	CubeTexture::~CubeTexture() {
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					for (unsigned int l = 0; l < 6; l++) {
						delete[] faces[i][j][k][l];
					}
					delete[] faces[i][j][k];
				}
				delete[] faces[i][j];
			}
			delete[] faces[i];
		}
		delete[] faces;
	}
}