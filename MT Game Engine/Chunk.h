#pragma once

#include <vector>

#include "Cube.h"
#include "Shader.h"
#include "Shape.h"
#include "Texture.h"
#include "GlobalConstants.h"

namespace mtge {
	class Chunk {
	public:
		const unsigned int CHUNK_WIDTH;
		const unsigned int CHUNK_DEPTH;

	private:
		unsigned int **heightMap = new unsigned int*[CHUNK_WIDTH];
		glm::vec3 position;
		Shader *shader = nullptr;
		Texture *cubeTextures[6];
		bool visible = true;
		bool hasHeightMap;

		void setHeightMap();
		void setShapeVector();
		void clearShapeVector();
		void deleteHeightMap();

	public:
		std::vector<Shape*> shapes = {};

		Chunk(glm::vec3 position, Shader *shader, Texture *cubeTextures[], const unsigned int CHUNK_WIDTH, const unsigned int CHUNK_DEPTH);
		Chunk(glm::vec3 position);
		void newShape(Shape *shape);
		void deleteShape(unsigned int index);
		void setVisible(bool visible);
		void draw();
		int collision(glm::vec3 cameraPosition, const glm::vec3 DIMENSIONS);
		glm::vec3 getPosition();
		void clearContents();
	};
}