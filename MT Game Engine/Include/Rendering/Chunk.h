#pragma once

#include <GL/glew.h>

#include "Rendering/Cube.h"
#include "Rendering/CubeData.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"
#include "ResourceManager.h"
#include "Texture/TextureAtlasSegment.h"
#include "Window.h"
#include "Interaction/Camera.h"

namespace mtge {
	class Chunk {
	private:
		static const unsigned int LENGTH_IN_CUBES = 16;
		static const unsigned int NUM_CUBES = LENGTH_IN_CUBES * LENGTH_IN_CUBES * LENGTH_IN_CUBES;
		Cube ****cubes = nullptr; //(i, j, k) = (x, y, z)    +i -> further right    +j -> higher up    +k -> further forwards
		unsigned int vertexArrayID;
		unsigned int vertexBufferID;
		TextureAtlasSegment *texAtlasSegment = nullptr;
		bool shouldGenBuffer = true;

		bool cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);

		void genBuffer();

	public:
		Chunk(TextureAtlasSegment *texAtlasSegment);
		void enableBufferRegenNextFrame();
		void render(Camera *camera, Window *window);
		Cube *getCubePtr(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		~Chunk();
	};
}