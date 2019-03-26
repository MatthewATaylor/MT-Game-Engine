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
	void Map::newChunk(Chunk *chunk) {
		chunks.push_back(chunk);
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
	void Map::clearContents() {
		deleteAllChunks();
		deleteSkybox();
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