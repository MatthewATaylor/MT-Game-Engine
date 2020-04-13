#include "../Include/WorldMap.h"

namespace mtge {
	Shader *WorldMap::shader = nullptr;
	Skybox *WorldMap::skybox = nullptr;
	std::vector<RenderablesSet*> WorldMap::renderablesSets = {};

	//Public
	void WorldMap::setSkyboxTexture(Texture *texture) {
		WorldMap::skybox = new Skybox(texture);
	}
	unsigned int WorldMap::getNumRenderablesSets() {
		return renderablesSets.size();
	}
	void WorldMap::appendRenderablesSet(RenderablesSet *renderablesSet) {
		renderablesSets.push_back(renderablesSet);
	}
	void WorldMap::appendRenderablesSet(RenderablesSet *renderablesSet, bool deletable) {
		if (deletable) {
			renderablesSet->setDeletable(true);
		}
		renderablesSets.push_back(renderablesSet);
	}
	RenderablesSet *WorldMap::getRenderablesSetPtr(unsigned int index) {
		return renderablesSets[index];
	}
	
	void WorldMap::eraseRenderablesSet(unsigned int index) {
		if (renderablesSets[index]->getDeletable()) {
			delete renderablesSets[index];
		}
		renderablesSets.erase(renderablesSets.begin() + index);
	}
	void WorldMap::clearRenderablesSets() {
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			if (renderablesSets[i]->getDeletable()) {
				delete renderablesSets[i];
			}
		}
		renderablesSets.clear();
	}
	void WorldMap::deleteSkybox() {
		delete skybox;
	}

	void WorldMap::drawRenderablesSets(glm::mat4 projectionMatrix, math::Mat<float, 4, 4> viewMatrix) {
		if (shader != ResourceManager::getShapeShaderPtr()) {
			shader = ResourceManager::getShapeShaderPtr();
			shader->useProgram();
		}

		glUniformMatrix4fv(ResourceManager::getShapeShaderPtr()->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(ResourceManager::getShapeShaderPtr()->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());
		for (unsigned int i = 0; i < renderablesSets.size(); i++) {
			renderablesSets[i]->drawAllShapes();
		}
	}
	void WorldMap::drawSkybox(glm::mat4 projectionMatrix, math::Mat<float, 4, 4> viewMatrix) {
		if (shader != ResourceManager::getSkyboxShaderPtr()) {
			shader = ResourceManager::getSkyboxShaderPtr();
			shader->useProgram();
		}

		glDepthFunc(GL_LEQUAL);
		glUniformMatrix4fv(ResourceManager::getSkyboxShaderPtr()->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		
		//Remove translation
		viewMatrix.set(1, 4, 0.0f);
		viewMatrix.set(2, 4, 0.0f);
		viewMatrix.set(3, 4, 0.0f);
		viewMatrix.set(4, 1, 0.0f);
		viewMatrix.set(4, 2, 0.0f);
		viewMatrix.set(4, 3, 0.0f);
		viewMatrix.set(4, 4, 1.0f);

		glUniformMatrix4fv(ResourceManager::getSkyboxShaderPtr()->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());
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