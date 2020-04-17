#pragma once

#include <string>

namespace mtge {
	struct SkyboxTextureContainer {
		std::string files[6];
		SkyboxTextureContainer(
			std::string frontTexFile,
			std::string backTexFile,
			std::string upTexFile,
			std::string downTexFile,
			std::string rightTexFile,
			std::string leftTexFile
		);
	};
}