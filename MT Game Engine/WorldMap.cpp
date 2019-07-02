#include "WorldMap.h"

namespace mtge {
	Shader *WorldMap::shader = nullptr;
	Skybox *WorldMap::skybox = nullptr;
	std::vector<RenderablesSet*> WorldMap::renderablesSets = {};

	//Public
	void WorldMap::setRenderMode(RenderMode renderMode) {
		if (renderMode == RenderMode::SHAPE) {
			shader = &ResourceManager::shapeShader;
		}
		else if (renderMode == RenderMode::SKYBOX) {
			shader = &ResourceManager::skyboxShader;
		}
	}
	void WorldMap::setSkyboxTexture(Texture *texture) {
		WorldMap::skybox = new Skybox(shader, texture);
	}
	unsigned int WorldMap::getNumRenderablesSets() {
		return renderablesSets.size();
	}
	void WorldMap::appendRenderablesSet(RenderablesSet *renderablesSet) {
		renderablesSets.push_back(renderablesSet);
	}
	RenderablesSet *WorldMap::getRenderablesSetPtr(unsigned int index) {
		return renderablesSets[index];
	}

	void WorldMap::eraseRenderablesSet(unsigned int index) {
		delete renderablesSets[index];
		renderablesSets.erase(renderablesSets.begin() + index);
	}
	void WorldMap::clearRenderablesSets() {
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			delete renderablesSets[i];
		}
		renderablesSets.clear();
	}
	void WorldMap::deleteSkybox() {
		delete skybox;
	}

	void WorldMap::drawRenderablesSets(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
		shader->useShaderProgram();
		glUniformMatrix4fv(ResourceManager::shapeShader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(ResourceManager::shapeShader.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			renderablesSets[i]->drawAllShapes();
		}
	}
	void WorldMap::drawSkybox(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
		glDepthFunc(GL_LEQUAL);
		shader->useShaderProgram();
		glUniformMatrix4fv(ResourceManager::skyboxShader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));
		glUniformMatrix4fv(ResourceManager::skyboxShader.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		skybox->updateBuffers();
		skybox->draw();
		glDepthFunc(GL_LESS);
	}

	void WorldMap::specifyRenderablesSetsRenderAreas() {
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			renderablesSets[i]->specifyRenderArea();
		}
	}
}