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