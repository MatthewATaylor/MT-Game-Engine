#include "Rendering/Chunk.h"

namespace mtge {
	//Constructor
	Chunk::Chunk(TextureAtlasSegment *texAtlasSegment, math::Vec2 position) {
		this->texAtlasSegment = texAtlasSegment;
		this->position = position;
		positionIndices = math::Vec<int, 2>((int)roundf(position.getX() / CHUNK_SIZE), (int)roundf(position.getY() / CHUNK_SIZE));

		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexBufferID);

		cubes = new Cube***[LENGTH_IN_CUBES];
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			cubes[i] = new Cube**[LENGTH_IN_CUBES];
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				cubes[i][j] = new Cube*[LENGTH_IN_CUBES];
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					//if (j == LENGTH_IN_CUBES - 1 && i % 3 == 0 && k % 3 == 0) {
					//	cubes[i][j][k] = new Cube{ 'x' };
					//}
					//else {
						cubes[i][j][k] = new Cube{ 'd' };
					//}
				}
			}
		}
		
		//Origin marker
		//cubes[0][LENGTH_IN_CUBES - 1][0]->type = 'x';
		//cubes[1][LENGTH_IN_CUBES - 1][0]->type = 'x';
		//cubes[0][LENGTH_IN_CUBES - 1][1]->type = 'x';
		//cubes[1][LENGTH_IN_CUBES - 1][1]->type = 'x';

		//Hole
		//cubes[LENGTH_IN_CUBES / 2][LENGTH_IN_CUBES - 1][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2][LENGTH_IN_CUBES - 2][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2][LENGTH_IN_CUBES - 3][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2][LENGTH_IN_CUBES - 4][LENGTH_IN_CUBES / 2]->type = 'x';

		//Tunnel
		//cubes[LENGTH_IN_CUBES / 2 + 1][LENGTH_IN_CUBES - 2][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2 + 1][LENGTH_IN_CUBES - 3][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2 + 1][LENGTH_IN_CUBES - 4][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2 + 2][LENGTH_IN_CUBES - 2][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2 + 2][LENGTH_IN_CUBES - 3][LENGTH_IN_CUBES / 2]->type = 'x';
		//cubes[LENGTH_IN_CUBES / 2 + 2][LENGTH_IN_CUBES - 4][LENGTH_IN_CUBES / 2]->type = 'x';
	}

	//Private
	void Chunk::genBuffer() {
		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

		//Add each cube's vertex buffer as sub data
		ChunkData chunkData(texAtlasSegment);
		float cubeSize = 2.0f / LENGTH_IN_CUBES;
		for (unsigned int i = 0; i < LENGTH_IN_CUBES; i++) {
			for (unsigned int j = 0; j < LENGTH_IN_CUBES; j++) {
				for (unsigned int k = 0; k < LENGTH_IN_CUBES; k++) {
					float xOffset = -1.0f + cubeSize / 2 + i * cubeSize;
					float yOffset = -1.0f + cubeSize / 2 + j * cubeSize;
					float zOffset = -1.0f + cubeSize / 2 + k * cubeSize;

					if (cubes[i][j][k]->type != 'x') {
						chunkData.addCube(
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
		verticesInLastBufferGen = chunkData.getVerticesInBuffer();
		chunkData.sendBuffer();

		if (shouldSetVertexAttributes) {
			//Position vertex attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);

			//Color vertex attribute
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			shouldSetVertexAttributes = false;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	//Public
	const float Chunk::CUBE_SIZE = 0.06f;
	const float Chunk::CHUNK_SIZE = LENGTH_IN_CUBES * CUBE_SIZE;

	bool Chunk::cubeHasTopNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return yIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex + 1][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasBottomNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return yIndex != 0 && cubes[xIndex][yIndex - 1][zIndex]->type != 'x';
	}
	bool Chunk::cubeHasLeftNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return
			(xIndex != 0 && cubes[xIndex - 1][yIndex][zIndex]->type != 'x') ||
			(xIndex == 0 && leftNeighbor && leftNeighbor->getCubePtr(LENGTH_IN_CUBES - 1, yIndex, zIndex)->type != 'x');
	}
	bool Chunk::cubeHasRightNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return
			(xIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex + 1][yIndex][zIndex]->type != 'x') ||
			(xIndex == LENGTH_IN_CUBES - 1 && rightNeighbor && rightNeighbor->getCubePtr(0, yIndex, zIndex)->type != 'x');
	}
	bool Chunk::cubeHasFrontNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return
			(zIndex != LENGTH_IN_CUBES - 1 && cubes[xIndex][yIndex][zIndex + 1]->type != 'x') ||
			(zIndex == LENGTH_IN_CUBES - 1 && frontNeighbor && frontNeighbor->getCubePtr(xIndex, yIndex, 0)->type != 'x');
	}
	bool Chunk::cubeHasBackNeighbor(unsigned int xIndex, unsigned int yIndex, unsigned int zIndex) {
		return
			(zIndex != 0 && cubes[xIndex][yIndex][zIndex - 1]->type != 'x') ||
			(zIndex == 0 && backNeighbor && backNeighbor->getCubePtr(xIndex, yIndex, LENGTH_IN_CUBES - 1)->type != 'x');
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

		shouldGenBuffer = true;
		chunk->enableBufferRegenNextFrame();
	}
	void Chunk::setBackNeighbor(Chunk *chunk) {
		backNeighbor = chunk;
		chunk->frontNeighbor = this;

		shouldGenBuffer = true;
		chunk->enableBufferRegenNextFrame();
	}
	void Chunk::setLeftNeighbor(Chunk *chunk) {
		leftNeighbor = chunk;
		chunk->rightNeighbor = this;

		shouldGenBuffer = true;
		chunk->enableBufferRegenNextFrame();
	}
	void Chunk::setRightNeighbor(Chunk *chunk) {
		rightNeighbor = chunk;
		chunk->leftNeighbor = this;

		shouldGenBuffer = true;
		chunk->enableBufferRegenNextFrame();
	}
	void Chunk::enableBufferRegenNextFrame() {
		shouldGenBuffer = true;
	}
	void Chunk::render(Camera *camera, Window *window) {
		if (shouldGenBuffer) {
			genBuffer();
			shouldGenBuffer = false;
		}
		
		glBindVertexArray(vertexArrayID);

		if (!Texture::getAtlasPtr()) {
			std::cout << "WARNING [FUNCTION: render]: TEXTURE ATLAS UNINITIALIZED" << std::endl << std::endl;
		}

		Shader *shader = Shader::getTexturedShapePtr();
		if (!shader) {
			std::cout << "ERROR [FUNCTION: render]: UNINITIALIZED TEXTURED SHAPE SHADER" << std::endl << std::endl;
			return;
		}
		shader->useProgram();
		
		math::Mat4 modelMatrix = math::Util::MatGen::scale<float, 4>(math::Vec3(LENGTH_IN_CUBES * CUBE_SIZE / 2.0f));
		modelMatrix = modelMatrix * math::Util::MatGen::translation<float, 4>(
			math::Vec3(position.getX(), -(LENGTH_IN_CUBES * CUBE_SIZE / 2.0f) + CUBE_SIZE / 2.0f, position.getY())
		);
		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, modelMatrix.getPtr());

		math::Mat4 viewMatrix = camera->getViewMatrix();
		glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());

		math::Mat4 projectionMatrix = camera->getProjectionMatrix(window);
		glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, projectionMatrix.getPtr());

		glEnable(GL_CULL_FACE);
		glDrawArrays(GL_TRIANGLES, 0, verticesInLastBufferGen);
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

		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
	}
}