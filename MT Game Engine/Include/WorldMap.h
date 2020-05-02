#pragma once

#include <unordered_map>
#include <utility>
#include <stdexcept>

#include "Rendering/Chunk.h"
#include "Rendering/ChunkData.h"
#include "Window.h"
#include "Interaction/Camera.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shader.h"
#include "Math/Mat.h"
#include "Math/Vec.h"

namespace mtge {
	class WorldMap {
	private:
		struct ChunkIndexPairHash {
			std::size_t operator()(const math::Vec<int, 2> &chunkIndices) const noexcept;
		};
		static std::unordered_map<const math::Vec<int, 2>, Chunk*, ChunkIndexPairHash> chunks;

	public:
		static std::unordered_map<const math::Vec<int, 2>, Chunk*>::iterator getChunksBegin();
		static std::unordered_map<const math::Vec<int, 2>, Chunk*>::iterator getChunksEnd();
		static void addChunk(Chunk *chunk);
		static Chunk *getChunkPtr(math::Vec<int, 2> chunkIndices);

		static void renderScene(Camera *camera, Window *window);

		static void freeResources();
		static void deleteChunk(math::Vec<int, 2> chunkIndices);
	};
}