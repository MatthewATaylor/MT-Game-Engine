#include "Map.h"

namespace mtge {
	Shader *Map::shader = nullptr;
	Skybox *Map::skybox = nullptr;
	std::vector<Chunk*> Map::chunks = {};

	//Public
	void Map::setShader(Shader *shader) {
		Map::shader = shader;
	}
	void Map::newSkybox(Texture *texture) {
		skybox = new Skybox(shader, texture);
	}

	void Map::deleteAllChunks() {
		for (unsigned int i = 0; i < chunks.size(); i++) {
			chunks[i]->clearContents();
			delete chunks[i];
		}
		chunks.clear();
	}
	void Map::deleteSkybox() {
		delete skybox;
	}

	void Map::drawChunks(unsigned int projectionLocation, unsigned int viewLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
		shader->useShaderProgram();
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		for (unsigned int i = 0; i < chunks.size(); i++) {
			chunks[i]->draw();
		}
	}
	void Map::drawSkybox(unsigned int projectionLocation, unsigned int viewLocation, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
		glDepthFunc(GL_LEQUAL);
		shader->useShaderProgram();
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		skybox->updateBuffers();
		skybox->draw();
		glDepthFunc(GL_LESS);
	}
}