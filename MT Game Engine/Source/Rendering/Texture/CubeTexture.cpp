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

		float faceTemplate[] = {
			//Triangle 1
			-1.0f,  1.0f, -1.0f, topTexAtlasSegment->TOP_LEFT.getS(),     topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			-1.0f,  1.0f,  1.0f, topTexAtlasSegment->BOTTOM_LEFT.getS(),  topTexAtlasSegment->BOTTOM_LEFT.getT(),  //Bottom Left
			 1.0f,  1.0f,  1.0f, topTexAtlasSegment->BOTTOM_RIGHT.getS(), topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			//Triangle 2
			-1.0f,  1.0f, -1.0f, topTexAtlasSegment->TOP_LEFT.getS(),     topTexAtlasSegment->TOP_LEFT.getT(),     //Top Left
			 1.0f,  1.0f,  1.0f, topTexAtlasSegment->BOTTOM_RIGHT.getS(), topTexAtlasSegment->BOTTOM_RIGHT.getT(), //Bottom Right
			 1.0f,  1.0f, -1.0f, topTexAtlasSegment->TOP_RIGHT.getS(),    topTexAtlasSegment->TOP_RIGHT.getT(),    //Top Right
		};

		for (unsigned int i = 0; i < 30; i++) {
			face[i] = faceTemplate[i];
		}
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
	}
	CubeTexture::CubeTexture(
		TextureAtlasSegment *texAtlasSegment) {

		this->frontTexAtlasSegment = texAtlasSegment;
		this->backTexAtlasSegment = texAtlasSegment;
		this->leftTexAtlasSegment = texAtlasSegment;
		this->rightTexAtlasSegment = texAtlasSegment;
		this->topTexAtlasSegment = texAtlasSegment;
		this->bottomTexAtlasSegment = texAtlasSegment;
	}
}