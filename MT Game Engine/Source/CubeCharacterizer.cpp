#include "CubeCharacterizer.h"

namespace mtge {
	//Public
	void CubeCharacterizer::addCubeType(unsigned char id, CubeTexture *texture) {
		if (cubeTypesSize == 0) {
			//No textures added yet, create textures array that can hold ID
			cubeTypes = new CubeTexture*[id + 1];
			cubeTypes[id] = texture;
			cubeTypesSize = id + 1;
		}
		else {
			//Textures array must be expanded
			if (cubeTypesSize <= id) {
				CubeTexture **newCubeTypes = new CubeTexture*[id + 1];
				std::copy(cubeTypes, cubeTypes + cubeTypesSize, newCubeTypes);
				newCubeTypes[id] = texture;
				delete[] cubeTypes;
				cubeTypes = newCubeTypes;
				cubeTypesSize = id + 1;
			}
			//Textures array already large enough
			else {
				cubeTypes[id] = texture;
			}
		}
	}
	CubeTexture *CubeCharacterizer::getTextureForID(unsigned char id) {
		return cubeTypes[id];
	}
}