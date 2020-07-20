#include "CubeCharacterizer.h"

namespace mtge {
	//Public
	void CubeCharacterizer::addCubeType(unsigned char id, CubeTexture *texture) {
		if (cubeTypesLength == 0) {
			//No textures added yet, create textures array that can hold ID
			cubeTypes = new CubeTexture*[id + 1];
			cubeTypes[id] = texture;
			cubeTypesLength = id + 1;
		}
		else {
			//Textures array must be expanded
			if (cubeTypesLength <= id) {
				CubeTexture **newCubeTypes = new CubeTexture*[id + 1];
				std::copy(cubeTypes, cubeTypes + cubeTypesLength, newCubeTypes);
				newCubeTypes[id] = texture;
				delete[] cubeTypes;
				cubeTypes = newCubeTypes;
				cubeTypesLength = id + 1;
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