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