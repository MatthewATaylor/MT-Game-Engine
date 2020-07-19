#pragma once

#include <vector>
#include <algorithm>

#include "TextureAtlasSegment.h"

namespace mtge {
	class CubeTexture {
	private:
		static const unsigned int LENGTH_IN_CUBES = 16;
		static const unsigned int FACE_VERTEX_BUFFER_LENGTH = 30;

		void genFaces();

	public:
		float *****faces = nullptr;

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

		~CubeTexture();
	};
}