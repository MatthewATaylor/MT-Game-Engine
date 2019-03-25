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
#include "GlobalConstants.h"

namespace mtge {
	class Map {
	private:
		static const int CHUNK_RENDER_DISTANCE_MULTIPLIER = 4;

		static Shader *shader;
		static Skybox *skybox;

		static glm::vec3 getCurrentChunkPosition(glm::vec3 cameraPosition);

	public:
		static std::vector<Chunk*> chunks;

		static void setShader(Shader *shader);
		static void newChunk(glm::vec3 pos, Texture *cubeTextures[], const unsigned int CHUNK_WIDTH, const unsigned int CHUNK_DEPTH);
		static void newSkybox(Texture *texture);

		static void deleteAllChunks();
		static void deleteSkybox();

		static void drawChunks();
		static void drawSkybox();
	};
}