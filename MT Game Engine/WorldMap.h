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
#include "ResourceManager.h"

namespace mtge {
	class WorldMap {
	private:
		static Shader *shader;
		static Skybox *skybox;
		static std::vector<RenderablesSet*> renderablesSets;

	public:
		static void setSkyboxTexture(Texture *texture);
		static unsigned int getNumRenderablesSets();
		static void appendRenderablesSet(RenderablesSet *renderablesSet);
		static void appendRenderablesSet(RenderablesSet *renderablesSet, bool deletable);
		static RenderablesSet *getRenderablesSetPtr(unsigned int index);

		static void eraseRenderablesSet(unsigned int index);
		static void clearRenderablesSets();
		static void deleteSkybox();

		static void drawRenderablesSets(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
		static void drawSkybox(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

		static void specifyRenderablesSetsRenderAreas();
	};
}