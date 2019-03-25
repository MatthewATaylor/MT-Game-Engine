#include "Chunk.h"

namespace mtge {
	//Constructor
	Chunk::Chunk(glm::vec3 position, Shader *shader, Texture *cubeTextures[], const unsigned int CHUNK_WIDTH, const unsigned int CHUNK_DEPTH) : CHUNK_WIDTH(CHUNK_WIDTH), CHUNK_DEPTH(CHUNK_DEPTH) {
		this->position = position;
		this->shader = shader;
		for (unsigned int i = 0; i < 6; i++) {
			this->cubeTextures[i] = cubeTextures[i];
		}
		setHeightMap();
		setShapeVector();
		hasHeightMap = true;
	}
	Chunk::Chunk(glm::vec3 position) : CHUNK_WIDTH(0), CHUNK_DEPTH(0) {
		this->position = position;
		this->shader = nullptr;
		for (unsigned int i = 0; i < 6; i++) {
			this->cubeTextures[i] = nullptr;
		}
		delete[] heightMap;
		hasHeightMap = false;
	}

	//Private
	void Chunk::setHeightMap() {
		for (unsigned int i = 0; i < CHUNK_WIDTH; i++) {
			heightMap[i] = new unsigned int[CHUNK_DEPTH];
			for (unsigned int j = 0; j < CHUNK_DEPTH; j++) {
				heightMap[i][j] = 3;
			}
		}
	}
	void Chunk::setShapeVector() {
		for (unsigned int i = 0; i < CHUNK_DEPTH; i++) {
			for (unsigned int j = 0; j < CHUNK_WIDTH; j++) {
				for (unsigned int k = 0; k < heightMap[i][j]; k++) {
					float cubeX = (float)j * CUBE_SIZE - CHUNK_WIDTH * CUBE_SIZE / 2.0f + position.x;
					float cubeY = (float)k * CUBE_SIZE * -1 + position.y;
					float cubeZ = (float)i * CUBE_SIZE - CHUNK_DEPTH * CUBE_SIZE / 2.0f + position.z;
					bool renderedSides[] = { 1, 1, 1, 1, 1, 1 }; //Front, Back, Left, Right, Top, Bottom

					if (i > 0 && i < CHUNK_DEPTH - 1) {
						renderedSides[0] = 0;
						renderedSides[1] = 0;
					}
					if (j > 0 && j < CHUNK_WIDTH - 1) {
						renderedSides[2] = 0;
						renderedSides[3] = 0;
					}
					if (k > 0 && k < heightMap[i][j] - 1) {
						renderedSides[4] = 0;
						renderedSides[5] = 0;
					}
					if (CHUNK_DEPTH > 1) {
						if (i == 0) {
							renderedSides[0] = 0;
						}
						if (i == CHUNK_DEPTH - 1) {
							renderedSides[1] = 0;
						}
					}
					if (CHUNK_WIDTH > 1) {
						if (j == 0) {
							renderedSides[3] = 0;
						}
						if (j == CHUNK_WIDTH - 1) {
							renderedSides[2] = 0;
						}
					}
					if (heightMap[i][j] > 1) {
						if (k == 0) {
							renderedSides[5] = 0;
						}
						if (k == heightMap[i][j] - 1) {
							renderedSides[4] = 0;
						}
					}

					shapes.push_back(new Cube(glm::vec3(cubeX, cubeY, cubeZ), glm::vec3(CUBE_SIZE, CUBE_SIZE, CUBE_SIZE), shader, cubeTextures, renderedSides));
				}
			}
		}
	}
	void Chunk::clearShapeVector() {
		for (unsigned int i = 0; i < shapes.size(); i++) {
			delete shapes[i];
		}
		shapes.clear();
	}
	void Chunk::deleteHeightMap() {
		for (unsigned int i = 0; i < CHUNK_WIDTH; i++) {
			delete[] heightMap[i];
		}
		delete[] heightMap;
	}

	//Public
	void Chunk::newShape(Shape *shape) {
		shapes.push_back(shape);
	}
	void Chunk::deleteShape(unsigned int index) {
		delete shapes[index];
		shapes.erase(shapes.begin() + index);
	}
	void Chunk::setVisible(bool visible) {
		this->visible = visible;
	}
	void Chunk::draw() {
		if (visible) {
			const char *prevShapeName = "";
			for (unsigned int i = 0; i < shapes.size(); i++) {
				const char *shapeName = shapes[i]->getName();
				if (strcmp(shapeName, prevShapeName) != 0) {
					shapes[i]->updateBuffers();
				}
				shapes[i]->draw();
				prevShapeName = shapeName;
			}
		}
	}
	int Chunk::collision(glm::vec3 cameraPosition, const glm::vec3 DIMENSIONS) {
		if (visible) {
			for (unsigned int i = 0; i < shapes.size(); i++) {
				if (shapes[i]->collision(cameraPosition, DIMENSIONS)) {
					return i;
				}
			}
		}
		return -1;
	}
	glm::vec3 Chunk::getPosition() {
		return position;
	}
	void Chunk::clearContents() {
		if (hasHeightMap) {
			clearShapeVector();
			deleteHeightMap();
		}
		else {
			clearShapeVector();
		}
	}
}