#pragma once

#include <vector>

#include "Rendering/Chunk.h"

namespace mtge {
	class WorldMap {
	private:
		static std::vector<Chunk*> chunks;

	public:
		static unsigned int getNumChunks();
		static void addChunk(Chunk *chunk);
		static Chunk *getChunkPtr(unsigned int index);
		static void freeResources();
		static void deleteChunk(unsigned int index);
		static void deleteChunk(Chunk *chunk);
	};
}