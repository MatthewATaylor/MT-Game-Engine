#include "Map.h"

namespace mtge {
	Shader *Map::shader = nullptr;
	Skybox *Map::skybox = nullptr;
	std::vector<Chunk*> Map::chunks = {};

	//Private
	glm::vec3 Map::getCurrentChunkPosition(glm::vec3 cameraPosition) {
		glm::vec3 currentChunkPosition(0.0f, 0.0f, 0.0f);
		currentChunkPosition.x = round(cameraPosition.x / ((float)mtge::DEFAULT_CHUNK_WIDTH * CUBE_SIZE)) * (float)mtge::DEFAULT_CHUNK_WIDTH * CUBE_SIZE;
		currentChunkPosition.z = round(cameraPosition.z / ((float)mtge::DEFAULT_CHUNK_DEPTH * CUBE_SIZE)) * (float)mtge::DEFAULT_CHUNK_DEPTH * CUBE_SIZE;
		return currentChunkPosition;
	}

	//Public
	void Map::setShader(Shader *shader) {
		Map::shader = shader;
	}
	void Map::newChunk(glm::vec3 pos, Texture *cubeTextures[], const unsigned int CHUNK_WIDTH, const unsigned int CHUNK_DEPTH) {
		chunks.push_back(new Chunk(pos, shader, cubeTextures, CHUNK_WIDTH, CHUNK_DEPTH));
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

	void Map::drawChunks() {
		for (unsigned int i = 0; i < chunks.size(); i++) {
			chunks[i]->draw();
		}
	}
	void Map::drawSkybox() {
		skybox->updateBuffers();
		skybox->draw();
	}
}