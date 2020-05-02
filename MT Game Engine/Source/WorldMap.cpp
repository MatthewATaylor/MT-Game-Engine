#include "WorldMap.h"

namespace mtge {
	//Private
	std::size_t WorldMap::ChunkIndexPairHash::operator()(const math::Vec<int, 2> &chunkIndices) const noexcept {
		int chunkXIndex = chunkIndices.getX();
		int chunkZIndex = chunkIndices.getY();
		chunkXIndex = chunkXIndex >= 0 ? chunkXIndex * 2 : chunkXIndex * -2 - 1;
		chunkZIndex = chunkZIndex >= 0 ? chunkZIndex * 2 : chunkZIndex * -2 - 1;
		return chunkXIndex >= chunkZIndex ? chunkXIndex * chunkXIndex + chunkXIndex + chunkZIndex : chunkXIndex + chunkZIndex * chunkZIndex;
	}
	std::unordered_map<const math::Vec<int, 2>, Chunk*, WorldMap::ChunkIndexPairHash> WorldMap::chunks;

	//Public
	std::unordered_map<const math::Vec<int, 2>, Chunk*>::iterator WorldMap::getChunksBegin() {
		return chunks.begin();
	}
	std::unordered_map<const math::Vec<int, 2>, Chunk*>::iterator WorldMap::getChunksEnd() {
		return chunks.end();
	}
	void WorldMap::addChunk(Chunk *chunk) {
		math::Vec<int, 2> chunkIndices = chunk->getPositionIndices();
		chunks[chunkIndices] = chunk;

		Chunk *frontNeighbor = getChunkPtr(math::Vec<int, 2>(chunkIndices.getX(), chunkIndices.getY() + 1));
		if (frontNeighbor) {
			chunk->setFrontNeighbor(frontNeighbor);
		}

		Chunk *backNeighbor = getChunkPtr(math::Vec<int, 2>(chunkIndices.getX(), chunkIndices.getY() - 1));
		if (backNeighbor) {
			chunk->setBackNeighbor(backNeighbor);
		}

		Chunk *leftNeighbor = getChunkPtr(math::Vec<int, 2>(chunkIndices.getX() - 1, chunkIndices.getY()));
		if (leftNeighbor) {
			chunk->setLeftNeighbor(leftNeighbor);
		}

		Chunk *rightNeighbor = getChunkPtr(math::Vec<int, 2>(chunkIndices.getX() + 1, chunkIndices.getY()));
		if (rightNeighbor) {
			chunk->setRightNeighbor(rightNeighbor);
		}
	}
	Chunk *WorldMap::getChunkPtr(math::Vec<int, 2> chunkIndices) {
		Chunk *chunk = nullptr;
		try {
			chunk = chunks.at(chunkIndices);
		}
		catch (std::out_of_range) {
			return nullptr;
		}
		return chunk;
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

		for (std::pair<math::Vec<int, 2>, Chunk*> element : chunks) {
			element.second->renderSolidCubes(camera, window, shader);
		}
		for (std::pair<math::Vec<int, 2>, Chunk*> element : chunks) {
			element.second->renderTransparentCubes(camera, window, shader);
		}
	}
	void WorldMap::freeResources() {
		for (std::pair<math::Vec<int, 2>, Chunk*> element : chunks) {
			if (element.second) {
				delete element.second;
			}
		}
		chunks.clear();
	}
	void WorldMap::deleteChunk(math::Vec<int, 2> chunkIndices) {
		Chunk *chunk = getChunkPtr(chunkIndices);
		if (chunk) {
			if (chunk->frontNeighbor) {
				chunk->frontNeighbor->backNeighbor = nullptr;
			}
			if (chunk->backNeighbor) {
				chunk->backNeighbor->frontNeighbor = nullptr;
			}
			if (chunk->leftNeighbor) {
				chunk->leftNeighbor->rightNeighbor = nullptr;
			}
			if (chunk->rightNeighbor) {
				chunk->rightNeighbor->leftNeighbor = nullptr;
			}
			delete chunk;
		}
		chunks.erase(chunkIndices);
	}
}