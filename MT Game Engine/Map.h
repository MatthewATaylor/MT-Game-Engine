#pragma once

#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		static void drawChunks(unsigned int projectionLocation, unsigned int viewLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
		static void drawSkybox(unsigned int projectionLocation, unsigned int viewLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
	};
}