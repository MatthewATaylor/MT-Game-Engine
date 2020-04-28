#include "Rendering/Chunk.h"

namespace mtge {
	//Constructor
	Chunk::Chunk(CubeCharacterizer *cubeCharacterizer, math::Vec2 position) {
		this->cubeCharacterizer = cubeCharacterizer;
		this->position = position;
		positionIndices = math::Vec<int, 2>((int)roundf(position.getX() / CHUNK_SIZE), (int)roundf(position.getY() / CHUNK_SIZE));

		modelMatrix = math::Util::MatGen::scale<float, 4>(math::Vec3(LENGTH_IN_CUBES * CUBE_SIZE / 2.0f));
		modelMatrix = modelMatrix * math::Util::MatGen::translation<float, 4>(
			math::Vec3(position.getX(), -(LENGTH_IN_CUBES * CUBE_SIZE / 2.0f) + CUBE_SIZE / 2.0f, position.getY())
		);

		glGenVertexArrays(1, &solidCubesVertexArrayID);
		glGenBuffers(1, &solidCubesVertexBufferID);

		glGenVertexArrays(1, &transparentCubesVertexArrayID);
		glGenBuffers(1, &transparentCubesVertexBufferID);

		unsigned int heights[LENGTH_IN_CUBES][LENGTH_IN_CUBES];
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				float globalCubeX = 0.0f;
				if (positionIndices.getX() >= 0) {
					globalCubeX = (float)(i + LENGTH_IN_CUBES * positionIndices.getX());
				}
				else {
					globalCubeX = (float)(-1 * (int)(LENGTH_IN_CUBES - i) + (int)(LENGTH_IN_CUBES * (positionIndices.getX() + 1)));
				}

				float globalCubeY = 0.0f;
				if (positionIndices.getY() >= 0) {
					globalCubeY = (float)(j + LENGTH_IN_CUBES * positionIndices.getY());
				}
				else {
					globalCubeY = (float)(-1 * (int)(LENGTH_IN_CUBES - j) + (int)(LENGTH_IN_CUBES * (positionIndices.getY() + 1)));
				}

				float noise = math::PerlinNoise::get2DWithOctaves(globalCubeX, globalCubeY, 0.03559f, 0.1f, 4);
				//float noise = 0.5f;
				heights[j][i] = (unsigned int)(noise * 15.0f) + 1;
			}
		}

		cubes = new Cube***[LENGTH_IN_CUBES];
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			cubes[i] = new Cube**[LENGTH_IN_CUBES];
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				cubes[i][j] = new Cube*[LENGTH_IN_CUBES];
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					if (j < heights[k][i]) {
						if (j <= 5) {
							cubes[i][j][k] = new Cube{ 's' };
						}
						else if (j == heights[k][i] - 1) {
							cubes[i][j][k] = new Cube{ 'g' };
						}
						else {
							cubes[i][j][k] = new Cube{ 'd' };
						}
					}
					else {
						cubes[i][j][k] = nullptr;
					}
				}
			}
		}

		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 1; k < 6; k++) {
					if (!cubes[i][k][j]) {
						cubes[i][k][j] = new Cube{ 'w' };
					}
				}
			}
		}
	}

	//Private
	void Chunk::genBuffers() {
		ChunkData solidCubeChunkData;
		ChunkData transparentCubeChunkData;
		float cubeSize = 2.0f / LENGTH_IN_CUBES;
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					float xOffset = -1.0f + cubeSize / 2 + i * cubeSize;
					float yOffset = -1.0f + cubeSize / 2 + j * cubeSize;
					float zOffset = -1.0f + cubeSize / 2 + k * cubeSize;

					if (cubes[i][j][k]) {
						if (isCubeTransparent(cubes[i][j][k]->type)) {
							transparentCubeChunkData.addCube(
								cubeCharacterizer->getTextureForCubeType(cubes[i][j][k]->type),
								math::Vec3(xOffset, yOffset, zOffset),
								LENGTH_IN_CUBES,
								cubeHasTopNeighbor(i, j, k),
								cubeHasBottomNeighbor(i, j, k),
								cubeHasLeftNeighbor(i, j, k),
								cubeHasRightNeighbor(i, j, k),
								cubeHasFrontNeighbor(i, j, k),
								cubeHasBackNeighbor(i, j, k)
							);
						}
						else {
							solidCubeChunkData.addCube(
								cubeCharacterizer->getTextureForCubeType(cubes[i][j][k]->type),
								math::Vec3(xOffset, yOffset, zOffset),
								LENGTH_IN_CUBES,
								cubeHasTopNeighbor(i, j, k),
								cubeHasBottomNeighbor(i, j, k),
								cubeHasLeftNeighbor(i, j, k),
								cubeHasRightNeighbor(i, j, k),
								cubeHasFrontNeighbor(i, j, k),
								cubeHasBackNeighbor(i, j, k)
							);
						}
					}
				}
			}
		}
		solidCubeVerticesInLastBufferGen = solidCubeChunkData.getVerticesInBuffer();
		transparentCubeVerticesInLastBufferGen = transparentCubeChunkData.getVerticesInBuffer();

		glBindVertexArray(solidCubesVertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, solidCubesVertexBufferID);
		solidCubeChunkData.sendBuffer();
		if (shouldSetSolidCubeVertexAttributes) {
			//Position vertex attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Color vertex attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			shouldSetSolidCubeVertexAttributes = false;
		}

		glBindVertexArray(transparentCubesVertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, transparentCubesVertexBufferID);
		transparentCubeChunkData.sendBuffer();
		if (shouldSetTransparentCubeVertexAttributes) {
			//Position vertex attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Color vertex attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			shouldSetTransparentCubeVertexAttributes = false;
		}
	}
	void Chunk::genSolidCubeBuffer() {
		ChunkData solidCubeChunkData;
		float cubeSize = 2.0f / LENGTH_IN_CUBES;
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					float xOffset = -1.0f + cubeSize / 2 + i * cubeSize;
					float yOffset = -1.0f + cubeSize / 2 + j * cubeSize;
					float zOffset = -1.0f + cubeSize / 2 + k * cubeSize;

					if (cubes[i][j][k]) {
						if (!isCubeTransparent(cubes[i][j][k]->type)) {
							solidCubeChunkData.addCube(
								cubeCharacterizer->getTextureForCubeType(cubes[i][j][k]->type),
								math::Vec3(xOffset, yOffset, zOffset),
								LENGTH_IN_CUBES,
								cubeHasTopNeighbor(i, j, k),
								cubeHasBottomNeighbor(i, j, k),
								cubeHasLeftNeighbor(i, j, k),
								cubeHasRightNeighbor(i, j, k),
								cubeHasFrontNeighbor(i, j, k),
								cubeHasBackNeighbor(i, j, k)
							);
						}
					}
				}
			}
		}
		solidCubeVerticesInLastBufferGen = solidCubeChunkData.getVerticesInBuffer();

		glBindVertexArray(solidCubesVertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, solidCubesVertexBufferID);
		solidCubeChunkData.sendBuffer();
		if (shouldSetSolidCubeVertexAttributes) {
			//Position vertex attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Color vertex attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			shouldSetSolidCubeVertexAttributes = false;
		}
	}
	void Chunk::genTransparentCubeBuffer() {
		ChunkData transparentCubeChunkData;
		float cubeSize = 2.0f / LENGTH_IN_CUBES;
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					float xOffset = -1.0f + cubeSize / 2 + i * cubeSize;
					float yOffset = -1.0f + cubeSize / 2 + j * cubeSize;
					float zOffset = -1.0f + cubeSize / 2 + k * cubeSize;

					if (cubes[i][j][k]) {
						if (isCubeTransparent(cubes[i][j][k]->type)) {
							transparentCubeChunkData.addCube(
								cubeCharacterizer->getTextureForCubeType(cubes[i][j][k]->type),
								math::Vec3(xOffset, yOffset, zOffset),
								LENGTH_IN_CUBES,
								cubeHasTopNeighbor(i, j, k),
								true,
								true,
								true,
								true,
								true
							);
						}
					}
				}
			}
		}
		transparentCubeVerticesInLastBufferGen = transparentCubeChunkData.getVerticesInBuffer();

		glBindVertexArray(transparentCubesVertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, transparentCubesVertexBufferID);
		transparentCubeChunkData.sendBuffer();
		if (shouldSetTransparentCubeVertexAttributes) {
			//Position vertex attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Color vertex attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			shouldSetTransparentCubeVertexAttributes = false;
		}
	}
	bool Chunk::isCubeTransparent(char typeSymbol) {
		return typeSymbol == 'w' || typeSymbol == 'l';
	}

	//Public
	const float Chunk::CUBE_SIZE = 0.06f;
	const float Chunk::CHUNK_SIZE = LENGTH_IN_CUBES * CUBE_SIZE;

	bool Chunk::cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return yIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex + 1][zIndex];
		}
		return yIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex + 1][zIndex] && !isCubeTransparent(cubes[xIndex][yIndex + 1][zIndex]->type);
	}
	bool Chunk::cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (yIndex == 0) {
			return true;
		}
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return yIndex != 0 && cubes[xIndex][yIndex - 1][zIndex];
		}
		return yIndex != 0 && cubes[xIndex][yIndex - 1][zIndex] && !isCubeTransparent(cubes[xIndex][yIndex - 1][zIndex]->type);
	}
	bool Chunk::cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (!leftNeighbor && xIndex == 0) {
			return true;
		}
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return
				(xIndex != 0 && cubes[xIndex - 1][yIndex][zIndex]) ||
				(xIndex == 0 && leftNeighbor && leftNeighbor->getCubePtr(LENGTH_IN_CUBES - 1, yIndex, zIndex));
		}
		return
			(xIndex != 0 && cubes[xIndex - 1][yIndex][zIndex] && !isCubeTransparent(cubes[xIndex - 1][yIndex][zIndex]->type)) ||
			(xIndex == 0 && leftNeighbor && leftNeighbor->getCubePtr(LENGTH_IN_CUBES - 1, yIndex, zIndex) && 
				!isCubeTransparent(leftNeighbor->getCubePtr(LENGTH_IN_CUBES - 1, yIndex, zIndex)->type));
	}
	bool Chunk::cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (!rightNeighbor && xIndex == LENGTH_IN_CUBES - 1) {
			return true;
		}
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return
				(xIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex + 1][yIndex][zIndex]) ||
				(xIndex == LENGTH_IN_CUBES - 1 && rightNeighbor && rightNeighbor->getCubePtr(0, yIndex, zIndex));
		}
		return
			(xIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex + 1][yIndex][zIndex] && !isCubeTransparent(cubes[xIndex + 1][yIndex][zIndex]->type)) ||
			(xIndex == LENGTH_IN_CUBES - 1 && rightNeighbor && rightNeighbor->getCubePtr(0, yIndex, zIndex) &&
				!isCubeTransparent(rightNeighbor->getCubePtr(0, yIndex, zIndex)->type));
	}
	bool Chunk::cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (!frontNeighbor && zIndex == LENGTH_IN_CUBES - 1) {
			return true;
		}
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return
				(zIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex][zIndex + 1]) ||
				(zIndex == LENGTH_IN_CUBES - 1 && frontNeighbor && frontNeighbor->getCubePtr(xIndex, yIndex, 0));
		}
		return
			(zIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex][zIndex + 1] && !isCubeTransparent(cubes[xIndex][yIndex][zIndex + 1]->type)) ||
			(zIndex == LENGTH_IN_CUBES - 1 && frontNeighbor && frontNeighbor->getCubePtr(xIndex, yIndex, 0) && 
				!isCubeTransparent(frontNeighbor->getCubePtr(xIndex, yIndex, 0)->type));
	}
	bool Chunk::cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (!backNeighbor && zIndex == 0) {
			return true;
		}
		if (cubes[xIndex][yIndex][zIndex] && isCubeTransparent(cubes[xIndex][yIndex][zIndex]->type)) {
			return
				(zIndex != 0 && cubes[xIndex][yIndex][zIndex - 1]) ||
				(zIndex == 0 && backNeighbor && backNeighbor->getCubePtr(xIndex, yIndex, LENGTH_IN_CUBES - 1));
		}
		return
			(zIndex != 0 && cubes[xIndex][yIndex][zIndex - 1] && !isCubeTransparent(cubes[xIndex][yIndex][zIndex - 1]->type)) ||
			(zIndex == 0 && backNeighbor && backNeighbor->getCubePtr(xIndex, yIndex, LENGTH_IN_CUBES - 1) && 
				!isCubeTransparent(backNeighbor->getCubePtr(xIndex, yIndex, LENGTH_IN_CUBES - 1)->type));
	}
	bool Chunk::cubeIsSurrounded(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return
			cubeHasTopNeighbor(xIndex, yIndex, zIndex) &&
			cubeHasBottomNeighbor(xIndex, yIndex, zIndex) &&
			cubeHasLeftNeighbor(xIndex, yIndex, zIndex) &&
			cubeHasRightNeighbor(xIndex, yIndex, zIndex) &&
			cubeHasFrontNeighbor(xIndex, yIndex, zIndex) &&
			cubeHasBackNeighbor(xIndex, yIndex, zIndex);
	}
	void Chunk::setFrontNeighbor(Chunk *chunk) {
		frontNeighbor = chunk;
		chunk->backNeighbor = this;

		shouldGenAllBuffers = true;
		chunk->enableAllBufferRegenNextFrame();
	}
	void Chunk::setBackNeighbor(Chunk *chunk) {
		backNeighbor = chunk;
		chunk->frontNeighbor = this;

		shouldGenAllBuffers = true;
		chunk->enableAllBufferRegenNextFrame();
	}
	void Chunk::setLeftNeighbor(Chunk *chunk) {
		leftNeighbor = chunk;
		chunk->rightNeighbor = this;

		shouldGenAllBuffers = true;
		chunk->enableAllBufferRegenNextFrame();
	}
	void Chunk::setRightNeighbor(Chunk *chunk) {
		rightNeighbor = chunk;
		chunk->leftNeighbor = this;

		shouldGenAllBuffers = true;
		chunk->enableAllBufferRegenNextFrame();
	}
	void Chunk::renderSolidCubes(Camera *camera, Window *window, Shader *shader) {
		if (shouldGenAllBuffers && leftNeighbor && rightNeighbor && frontNeighbor && backNeighbor) {
			genBuffers();
			shouldGenAllBuffers = false;
		}
		else if (shouldGenSolidCubeBuffer && leftNeighbor && rightNeighbor && frontNeighbor && backNeighbor) {
			genSolidCubeBuffer();
			shouldGenSolidCubeBuffer = false;
		}

		glBindVertexArray(solidCubesVertexArrayID);

		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, modelMatrix.getPtr());

		glDrawArrays(GL_TRIANGLES, 0, solidCubeVerticesInLastBufferGen);
	}
	void Chunk::renderTransparentCubes(Camera *camera, Window *window, Shader *shader) {
		if (shouldGenAllBuffers && leftNeighbor && rightNeighbor && frontNeighbor && backNeighbor) {
			genBuffers();
			shouldGenAllBuffers = false;
		}
		else if (shouldGenTransparentCubeBuffer && leftNeighbor && rightNeighbor && frontNeighbor && backNeighbor) {
			genTransparentCubeBuffer();
			shouldGenTransparentCubeBuffer = false;
		}

		glBindVertexArray(transparentCubesVertexArrayID);

		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, modelMatrix.getPtr());

		glDrawArrays(GL_TRIANGLES, 0, transparentCubeVerticesInLastBufferGen);
	}
	void Chunk::enableAllBufferRegenNextFrame() {
		shouldGenAllBuffers = true;
	}
	void Chunk::enableSolidCubeBufferRegenNextFrame() {
		shouldGenSolidCubeBuffer = true;
	}
	void Chunk::enableTransparentCubeBufferRegenNextFrame() {
		shouldGenTransparentCubeBuffer = true;
	}
	Cube *Chunk::getCubePtr(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		if (xIndex >= LENGTH_IN_CUBES || yIndex >= LENGTH_IN_CUBES || zIndex >= LENGTH_IN_CUBES) {
			return nullptr;
		}
		if (xIndex < 0 || yIndex < 0 || zIndex < 0) {
			return nullptr;
		}
		return cubes[xIndex][yIndex][zIndex];
	}
	math::Vec2 Chunk::getPosition() {
		return position;
	}
	math::Vec<int, 2> Chunk::getPositionIndices() {
		return positionIndices;
	}

	//Destructor
	Chunk::~Chunk() {
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				delete[] cubes[i][j];
			}
			delete[] cubes[i];
		}
		delete[] cubes;

		glDeleteVertexArrays(1, &solidCubesVertexArrayID);
		glDeleteBuffers(1, &solidCubesVertexBufferID);

		glDeleteVertexArrays(1, &transparentCubesVertexArrayID);
		glDeleteBuffers(1, &transparentCubesVertexBufferID);
	}
}