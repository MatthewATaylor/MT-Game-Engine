#pragma once

#include <unordered_map>

#include "Rendering/Texture/CubeTexture.h"

namespace mtge {
	class CubeCharacterizer {
	private:
		std::unordered_map<char, CubeTexture*> cubeTypeMap;

	public:
		void addCubeType(char symbol, CubeTexture *texture);
		CubeTexture *getTextureForCubeType(char symbol);
	};
}