#pragma once

#include <cmath>

#include <GL/glew.h>

#include "CubeCharacterizer.h"
#include "Math/Vec.h"
#include "Math/Mat.h"
#include "Math/Util.h"
#include "ResourceManager.h"
#include "Texture/CubeTexture.h"
#include "Window.h"
#include "Interaction/Camera.h"
#include "Rendering/ChunkData.h"
#include "Math/PerlinNoise.h"
#include "Shader.h"

namespace mtge {
	class Chunk {
	public:
		static const unsigned int LENGTH_IN_CUBES = 16;

	private:
		static const unsigned int NUM_CUBES = LENGTH_IN_CUBES * LENGTH_IN_CUBES * LENGTH_IN_CUBES;
		char ***cubes = nullptr; //(i, j, k) = (x, y, z)    +i -> +x    +j -> +y    +k -> +z
		
		unsigned int solidCubesVertexArrayID;
		unsigned int solidCubesVertexBufferID;
		
		unsigned int transparentCubesVertexArrayID;
		unsigned int transparentCubesVertexBufferID;

		CubeCharacterizer *cubeCharacterizer = nullptr;
		
		bool shouldGenAllBuffers = true;
		bool shouldGenSolidCubeBuffer = false;
		bool shouldGenTransparentCubeBuffer = false;
		
		bool shouldSetSolidCubeVertexAttributes = true;
		bool shouldSetTransparentCubeVertexAttributes = true;
		
		math::Vec2 position;
		math::Vec<int, 2> positionIndices;
		math::Mat4 modelMatrix;

		int solidCubeVerticesInLastBufferGen = 0;
		int transparentCubeVerticesInLastBufferGen = 0;

		void genBuffers();
		void genSolidCubeBuffer();
		void genTransparentCubeBuffer();
		static bool isCubeTransparent(char typeSymbol);

	public:
		static const float CUBE_SIZE;
		static const float CHUNK_SIZE;

		Chunk *frontNeighbor = nullptr;
		Chunk *backNeighbor = nullptr;
		Chunk *leftNeighbor = nullptr;
		Chunk *rightNeighbor = nullptr;

		Chunk(CubeCharacterizer *cubeCharacterizer, math::Vec2 position);

		bool cubeHasTopNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeHasBottomNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeHasLeftNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeHasRightNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeHasFrontNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeHasBackNeighbor(const math::Vec<unsigned int, 3> &indices);
		bool cubeIsSurrounded(const math::Vec<unsigned int, 3> &indices);

		void setFrontNeighbor(Chunk *chunk);
		void setBackNeighbor(Chunk *chunk);
		void setLeftNeighbor(Chunk *chunk);
		void setRightNeighbor(Chunk *chunk);

		void renderSolidCubes(Camera *camera, Window *window, Shader *shader);
		void renderTransparentCubes(Camera *camera, Window *window, Shader *shader);

		void enableAllBufferRegenNextFrame();
		void enableSolidCubeBufferRegenNextFrame();
		void enableTransparentCubeBufferRegenNextFrame();
		char getCube(const math::Vec<unsigned int, 3> &indices);
		math::Vec2 getPosition();
		math::Vec<int, 2> getPositionIndices();

		~Chunk();
	};
}