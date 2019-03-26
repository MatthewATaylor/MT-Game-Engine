#pragma once

#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Chunk.h"
#include "Shader.h"
#include "Texture.h"
#include "Skybox.h"

namespace mtge {
	class Map {
	private:
		static Shader *shader;
		static Skybox *skybox;

	public:
		static std::vector<Chunk*> chunks;

		static void setShader(Shader *shader);
		static void newSkybox(Texture *texture);

		static void deleteAllChunks();
		static void deleteSkybox();

		static void drawChunks();
		static void drawSkybox();
	};
}