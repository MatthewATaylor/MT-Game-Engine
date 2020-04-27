#include "WorldMap.h"

namespace mtge {
	//Private
	std::vector<Chunk*> WorldMap::chunks;

	//Public
	unsigned int WorldMap::getNumChunks() {
		return chunks.size();
	}
	void WorldMap::addChunk(Chunk *chunk) {
		chunk->indexInMap = chunks.size();
		chunks.push_back(chunk);
	}
	Chunk *WorldMap::getChunkPtr(unsigned int index) {
		return chunks[index];
	}
	void WorldMap::renderScene(Camera *camera, Window *window) {
		if (!Texture::getAtlasPtr()) {
			std::cout << "WARNING [FUNCTION: render]: TEXTURE ATLAS UNINITIALIZED" << std::endl << std::endl;
		}

		Shader *shader = Shader::getTexturedShapePtr();
		if (!shader) {
			std::cout << "ERROR [FUNCTION: render]: UNINITIALIZED TEXTURED SHAPE SHADER" << std::endl << std::endl;
			return;
		}
		shader->useProgram();

		math::Mat4 viewMatrix = camera->getViewMatrix();
		glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());

		math::Mat4 projectionMatrix = camera->getProjectionMatrix(window);
		glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, projectionMatrix.getPtr());

		glEnable(GL_CULL_FACE);

		for (unsigned int i = 0; i < chunks.size(); i++) {
			chunks[i]->renderSolidCubes(camera, window, shader);
		}

		for (unsigned int i = 0; i < chunks.size(); i++) {
			chunks[i]->renderTransparentCubes(camera, window, shader);
		}
	}
	void WorldMap::freeResources() {
		for (unsigned int i = 0; i < chunks.size(); i++) {
			delete chunks[i];
		}
		chunks.clear();
	}
	void WorldMap::deleteChunk(unsigned int index) {
		delete chunks[index];
		chunks.erase(chunks.begin() + index);
	}
	void WorldMap::deleteChunk(Chunk *chunk) {
		for (unsigned int i = 0; i < chunks.size(); i++) {
			if (chunks[i] == chunk) {
				delete chunks[i];
				chunks.erase(chunks.begin() + i);
				break;
			}
		}
	}
}