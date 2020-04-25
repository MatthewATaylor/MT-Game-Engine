#include "CubeCharacterizer.h"

namespace mtge {
	//Public
	void CubeCharacterizer::addCubeType(char symbol, CubeTexture *texture) {
		cubeTypeMap.insert({ symbol, texture });
	}
	CubeTexture *CubeCharacterizer::getTextureForCubeType(char symbol) {
		return cubeTypeMap.at(symbol);
	}
}