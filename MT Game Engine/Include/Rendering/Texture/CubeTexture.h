#pragma once

#include "TextureAtlasSegment.h"

namespace mtge {
	struct CubeTexture {
		TextureAtlasSegment *frontTexAtlasSegment = nullptr;
		TextureAtlasSegment *backTexAtlasSegment = nullptr;
		TextureAtlasSegment *leftTexAtlasSegment = nullptr;
		TextureAtlasSegment *rightTexAtlasSegment = nullptr;
		TextureAtlasSegment *topTexAtlasSegment = nullptr;
		TextureAtlasSegment *bottomTexAtlasSegment = nullptr;

		CubeTexture(
			TextureAtlasSegment *frontTexAtlasSegment,
			TextureAtlasSegment *backTexAtlasSegment,
			TextureAtlasSegment *leftTexAtlasSegment,
			TextureAtlasSegment *rightTexAtlasSegment,
			TextureAtlasSegment *topTexAtlasSegment,
			TextureAtlasSegment *bottomTexAtlasSegment
		);
		CubeTexture(
			TextureAtlasSegment *sideTexAtlasSegment,
			TextureAtlasSegment *topTexAtlasSegment,
			TextureAtlasSegment *bottomTexAtlasSegment
		);
		CubeTexture(
			TextureAtlasSegment *texAtlasSegment
		);
	};
}