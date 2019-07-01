#pragma once

#include <vector>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "RenderablesSet.h"
#include "Shader.h"
#include "Texture.h"
#include "Skybox.h"

namespace mtge {
	class WorldMap {
	private:
		static Shader *shader;
		static Skybox *skybox;
		static std::vector<RenderablesSet*> renderablesSets;

	public:
		static void setShader(Shader *shader);
		static void setSkyboxTexture(Texture *texture);
		static unsigned int getNumRenderablesSets();
		static void appendRenderablesSet(RenderablesSet *renderablesSet);
		static RenderablesSet *getRenderablesSetPtr(unsigned int index);

		static void eraseRenderablesSet(unsigned int index);
		static void clearRenderablesSets();
		static void deleteSkybox();

		static void drawRenderablesSets(glm::mat4 projectionMatrix, unsigned int shapeProjectionLocation, glm::mat4 viewMatrix, unsigned int shapeViewLocation);
		static void drawSkybox(glm::mat4 projectionMatrix, unsigned int skyboxProjectionLocation, glm::mat4 viewMatrix, unsigned int skyboxViewLocation);

		static void specifyRenderablesSetsRenderAreas();
	};
}