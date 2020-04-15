#include "../Include/Chunk.h"

namespace mtge {
	//Private
	bool Chunk::cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return yIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex + 1][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return yIndex != 0 && cubes[xIndex][yIndex - 1][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return xIndex != 0 && cubes[xIndex - 1][yIndex][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return xIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex + 1][yIndex][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return zIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex][zIndex + 1]->type != 'x';
	}
	bool Chunk::cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return zIndex != 0 && cubes[xIndex][yIndex][zIndex - 1]->type != 'x';
	}

	//Public
	Chunk::Chunk() {
		cubes = new Cube***[LENGTH_IN_CUBES];
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			cubes[i] = new Cube**[LENGTH_IN_CUBES];
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				cubes[i][j] = new Cube*[LENGTH_IN_CUBES];
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					cubes[i][j][k] = new Cube{ 'd' };
				}
			}
		}
	}
	Chunk::~Chunk() {
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				delete[] cubes[i][j];
			}
			delete[] cubes[i];
		}
		delete[] cubes;
	}
	void Chunk::genBuffer() {
		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexBufferID);

		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

		glBufferData(GL_ARRAY_BUFFER, NUM_CUBES * CubeData::VERTEX_BUFFER_SIZE, 0, GL_STATIC_DRAW);

		//Add each cube's vertex buffer as sub data
		float cubeSize = 2.0f / LENGTH_IN_CUBES;
		unsigned int cubeNum = 0;
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					float xOffset = -1.0f + cubeSize / 2 + i * cubeSize;
					float yOffset = -1.0f + cubeSize / 2 + j * cubeSize;
					float zOffset = -1.0f + cubeSize / 2 + k * cubeSize;

					CubeData cubeData(
						math::Vec<float, 3>(xOffset, yOffset, zOffset), 
						LENGTH_IN_CUBES,
						cubeHasTopNeighbor(i, j, k),
						cubeHasBottomNeighbor(i, j, k),
						cubeHasLeftNeighbor(i, j, k),
						cubeHasRightNeighbor(i, j, k),
						cubeHasFrontNeighbor(i, j, k),
						cubeHasBackNeighbor(i, j, k)
					);
					glBufferSubData(GL_ARRAY_BUFFER, cubeNum * CubeData::VERTEX_BUFFER_SIZE, CubeData::VERTEX_BUFFER_SIZE, cubeData.vertexBuffer);
					cubeNum++;
				}
			}
		}

		//Position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Color vertex attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
	void Chunk::render(glm::mat4 projectionMatrix, math::Mat<float, 4, 4> viewMatrix) {
		Shader *shader = ResourceManager::getShapeShaderPtr();
		shader->useProgram();

		glUniformMatrix4fv(ResourceManager::getShapeShaderPtr()->getProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(ResourceManager::getShapeShaderPtr()->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());

		//glEnable(GL_CULL_FACE);
		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
		glDrawArrays(GL_TRIANGLES, 0, 36 * NUM_CUBES);
	}
}