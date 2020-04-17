#include "Rendering/Texture/SkyboxTextureContainer.h"

namespace mtge {
	//Constructor
	SkyboxTextureContainer::SkyboxTextureContainer(
		std::string frontTexFile,
		std::string backTexFile,
		std::string upTexFile,
		std::string downTexFile,
		std::string rightTexFile,
		std::string leftTexFile) {

		files[0] = frontTexFile;
		files[1] = backTexFile;
		files[2] = upTexFile;
		files[3] = downTexFile;
		files[4] = rightTexFile;
		files[5] = leftTexFile;
	}
}