#include "WorldMap.h"

namespace mtge {
	Shader *WorldMap::shader = nullptr;
	Skybox *WorldMap::skybox = nullptr;
	std::vector<RenderablesSet*> WorldMap::renderablesSets = {};

	//Public
	void WorldMap::setShader(Shader *shader) {
		WorldMap::shader = shader;
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

	void WorldMap::drawRenderablesSets(glm::mat4 projectionMatrix, unsigned int shapeProjectionLocation, glm::mat4 viewMatrix, unsigned int shapeViewLocation) {
		shader->useShaderProgram();
		glUniformMatrix4fv(shapeProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shapeViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			renderablesSets[i]->drawAllShapes();
		}
	}
	void WorldMap::drawSkybox(glm::mat4 projectionMatrix, unsigned int skyboxProjectionLocation, glm::mat4 viewMatrix, unsigned int skyboxViewLocation) {
		glDepthFunc(GL_LEQUAL);
		shader->useShaderProgram();
		glUniformMatrix4fv(skyboxProjectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));
		glUniformMatrix4fv(skyboxViewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
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