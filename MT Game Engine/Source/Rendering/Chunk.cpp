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

		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					if (cubes[i][j][k]) {
						CubeTexture *texture = cubeCharacterizer->getTextureForID(cubes[i][j][k]->type);
						math::Vec<unsigned int, 3> indexVec(i, j, k);
						if (isCubeTransparent(cubes[i][j][k]->type)) {
							transparentCubeChunkData.addCube(
								texture,
								indexVec,
								cubeHasTopNeighbor(indexVec),
								cubeHasBottomNeighbor(indexVec),
								cubeHasLeftNeighbor(indexVec),
								cubeHasRightNeighbor(indexVec),
								cubeHasFrontNeighbor(indexVec),
								cubeHasBackNeighbor(indexVec)
							);
						}
						else {
							solidCubeChunkData.addCube(
								texture,
								indexVec,
								cubeHasTopNeighbor(indexVec),
								cubeHasBottomNeighbor(indexVec),
								cubeHasLeftNeighbor(indexVec),
								cubeHasRightNeighbor(indexVec),
								cubeHasFrontNeighbor(indexVec),
								cubeHasBackNeighbor(indexVec)
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

		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					if (cubes[i][j][k]) {
						if (!isCubeTransparent(cubes[i][j][k]->type)) {
							math::Vec<unsigned int, 3> indexVec(i, j, k);
							solidCubeChunkData.addCube(
								cubeCharacterizer->getTextureForID(cubes[i][j][k]->type),
								indexVec,
								cubeHasTopNeighbor(indexVec),
								cubeHasBottomNeighbor(indexVec),
								cubeHasLeftNeighbor(indexVec),
								cubeHasRightNeighbor(indexVec),
								cubeHasFrontNeighbor(indexVec),
								cubeHasBackNeighbor(indexVec)
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

		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					if (cubes[i][j][k]) {
						if (isCubeTransparent(cubes[i][j][k]->type)) {
							transparentCubeChunkData.addCube(
								cubeCharacterizer->getTextureForID(cubes[i][j][k]->type),
								math::Vec<unsigned int, 3>(i, j, k),
								cubeHasTopNeighbor(math::Vec<unsigned int, 3>(i, j, k)),
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

	bool Chunk::cubeHasTopNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return indices.getY() != LENGTH_IN_CUBES - 1 && cubes[indices.getX()][indices.getY() + 1][indices.getZ()];
		}
		return indices.getY() != LENGTH_IN_CUBES - 1 && cubes[indices.getX()][indices.getY() + 1][indices.getZ()] && 
			!isCubeTransparent(cubes[indices.getX()][indices.getY() + 1][indices.getZ()]->type);
	}
	bool Chunk::cubeHasBottomNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (indices.getY() == 0) {
			return true;
		}
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return indices.getY() != 0 && cubes[indices.getX()][indices.getY() - 1][indices.getZ()];
		}
		return indices.getY() != 0 && cubes[indices.getX()][indices.getY() - 1][indices.getZ()] && 
			!isCubeTransparent(cubes[indices.getX()][indices.getY() - 1][indices.getZ()]->type);
	}
	bool Chunk::cubeHasLeftNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (!leftNeighbor && indices.getX() == 0) {
			return true;
		}
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return
				(indices.getX() != 0 && cubes[indices.getX() - 1][indices.getY()][indices.getZ()]) ||
				(indices.getX() == 0 && leftNeighbor && 
					leftNeighbor->getCubePtr(math::Vec<unsigned int, 3>(LENGTH_IN_CUBES - 1, indices.getY(), indices.getZ())));
		}
		return
			(indices.getX() != 0 && cubes[indices.getX() - 1][indices.getY()][indices.getZ()] && 
				!isCubeTransparent(cubes[indices.getX() - 1][indices.getY()][indices.getZ()]->type)) ||
			(indices.getX() == 0 && leftNeighbor && 
				leftNeighbor->getCubePtr(math::Vec<unsigned int, 3>(LENGTH_IN_CUBES - 1, indices.getY(), indices.getZ())) &&
				!isCubeTransparent(leftNeighbor->getCubePtr(math::Vec<unsigned int, 3>(LENGTH_IN_CUBES - 1, indices.getY(), indices.getZ()))->type));
	}
	bool Chunk::cubeHasRightNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (!rightNeighbor && indices.getX() == LENGTH_IN_CUBES - 1) {
			return true;
		}
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return
				(indices.getX() != LENGTH_IN_CUBES - 1 && cubes[indices.getX() + 1][indices.getY()][indices.getZ()]) ||
				(indices.getX() == LENGTH_IN_CUBES - 1 && rightNeighbor && 
					rightNeighbor->getCubePtr(math::Vec<unsigned int, 3>(0, indices.getY(), indices.getZ())));
		}
		return
			(indices.getX() != LENGTH_IN_CUBES - 1 && cubes[indices.getX() + 1][indices.getY()][indices.getZ()] && 
				!isCubeTransparent(cubes[indices.getX() + 1][indices.getY()][indices.getZ()]->type)) ||
			(indices.getX() == LENGTH_IN_CUBES - 1 && rightNeighbor && 
				rightNeighbor->getCubePtr(math::Vec<unsigned int, 3>(0, indices.getY(), indices.getZ())) &&
				!isCubeTransparent(rightNeighbor->getCubePtr(math::Vec<unsigned int, 3>(0, indices.getY(), indices.getZ()))->type));
	}
	bool Chunk::cubeHasFrontNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (!frontNeighbor && indices.getZ() == LENGTH_IN_CUBES - 1) {
			return true;
		}
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return
				(indices.getZ() != LENGTH_IN_CUBES - 1 && cubes[indices.getX()][indices.getY()][indices.getZ() + 1]) ||
				(indices.getZ() == LENGTH_IN_CUBES - 1 && frontNeighbor && 
					frontNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), 0)));
		}
		return
			(indices.getZ() != LENGTH_IN_CUBES - 1 && cubes[indices.getX()][indices.getY()][indices.getZ() + 1] && 
				!isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ() + 1]->type)) ||
			(indices.getZ() == LENGTH_IN_CUBES - 1 && frontNeighbor && 
				frontNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), 0)) && 
				!isCubeTransparent(frontNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), 0))->type));
	}
	bool Chunk::cubeHasBackNeighbor(const math::Vec<unsigned int, 3> &indices) {
		if (!backNeighbor && indices.getZ() == 0) {
			return true;
		}
		if (cubes[indices.getX()][indices.getY()][indices.getZ()] && isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ()]->type)) {
			return
				(indices.getZ() != 0 && cubes[indices.getX()][indices.getY()][indices.getZ() - 1]) ||
				(indices.getZ() == 0 && backNeighbor && 
					backNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), LENGTH_IN_CUBES - 1)));
		}
		return
			(indices.getZ() != 0 && cubes[indices.getX()][indices.getY()][indices.getZ() - 1] && !
				isCubeTransparent(cubes[indices.getX()][indices.getY()][indices.getZ() - 1]->type)) ||
			(indices.getZ() == 0 && backNeighbor && 
				backNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), LENGTH_IN_CUBES - 1)) && 
				!isCubeTransparent(backNeighbor->getCubePtr(math::Vec<unsigned int, 3>(indices.getX(), indices.getY(), LENGTH_IN_CUBES - 1))->type));
	}
	bool Chunk::cubeIsSurrounded(const math::Vec<unsigned int, 3> &indices) {
		return
			cubeHasTopNeighbor(indices) &&
			cubeHasBottomNeighbor(indices) &&
			cubeHasLeftNeighbor(indices) &&
			cubeHasRightNeighbor(indices) &&
			cubeHasFrontNeighbor(indices) &&
			cubeHasBackNeighbor(indices);
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
	Cube *Chunk::getCubePtr(const math::Vec<unsigned int, 3> &indices) {
		if (indices.getX() >= LENGTH_IN_CUBES || indices.getY() >= LENGTH_IN_CUBES || indices.getZ() >= LENGTH_IN_CUBES) {
			return nullptr;
		}
		if (indices.getX() < 0 || indices.getY() < 0 || indices.getZ() < 0) {
			return nullptr;
		}
		return cubes[indices.getX()][indices.getY()][indices.getZ()];
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