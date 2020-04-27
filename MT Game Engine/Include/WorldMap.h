#pragma once

#include <vector>

#include "Rendering/Chunk.h"
#include "Rendering/ChunkData.h"
#include "Window.h"
#include "Interaction/Camera.h"
#include "Rendering/Texture/Texture.h"
#include "Rendering/Shader.h"
#include "Math/Mat.h"

namespace mtge {
	class WorldMap {
	private:
		static std::vector<Chunk*> chunks;

	public:
		static unsigned int getNumChunks();
		static void addChunk(Chunk *chunk);
		static Chunk *getChunkPtr(unsigned int index);
		static void deleteChunk(unsigned int index);
		static void deleteChunk(Chunk *chunk);

		static void renderScene(Camera *camera, Window *window);

		static void freeResources();
	};
}