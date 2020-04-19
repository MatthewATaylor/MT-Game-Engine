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
	public:
		static const unsigned int LENGTH_IN_CUBES = 16;

	private:
		static const unsigned int NUM_CUBES = LENGTH_IN_CUBES * LENGTH_IN_CUBES * LENGTH_IN_CUBES;
		Cube ****cubes = nullptr; //(i, j, k) = (x, y, z)    +i -> +x    +j -> +y    +k -> +z
		unsigned int vertexArrayID;
		unsigned int vertexBufferID;
		TextureAtlasSegment *texAtlasSegment = nullptr;
		bool shouldGenBuffer = true;
		math::Vec2 position;

		void genBuffer();

	public:
		static const float CUBE_SIZE;
		static const float CHUNK_SIZE;

		Chunk(TextureAtlasSegment *texAtlasSegment, math::Vec2 position);

		bool cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		bool cubeIsSurrounded(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);

		void enableBufferRegenNextFrame();
		void render(Camera *camera, Window *window);
		Cube *getCubePtr(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex);
		math::Vec2 getPosition();

		~Chunk();
	};
}