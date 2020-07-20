#pragma once

#include <algorithm>

#include "Rendering/Texture/CubeTexture.h"

namespace mtge {
	class CubeCharacterizer {
	private:
		unsigned char cubeTypesLength = 0;
		CubeTexture **cubeTypes = nullptr;

	public:
		void addCubeType(unsigned char id, CubeTexture *texture);
		CubeTexture *getTextureForID(unsigned char id);
	};
}