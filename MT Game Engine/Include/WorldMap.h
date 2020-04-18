#pragma once

#include <vector>

#include "Rendering/Chunk.h"

namespace mtge {
	class WorldMap {
	private:
		std::vector<Chunk*> chunks;

	public:
		unsigned int getNumChunks();
		void addChunk(Chunk *chunk);
		Chunk *getChunkPtr(unsigned int index);
		void freeResources();
		void deleteChunk(unsigned int index);
		void deleteChunk(Chunk *chunk);
	};
}