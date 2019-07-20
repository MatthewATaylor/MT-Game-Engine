#include "Cube.h"

namespace mtge {
	const float Cube::VERTICES[] = {
		//Positions-----------Colors---------------Texture-----
		//Triangle 1, Front
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 2, Front
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Top Right

		//Triangle 1, Back
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Right
		//Triangle 2, Back
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Top Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Left

		//Triangle 1, Left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 2, Left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Top Right

		//Triangle 1, Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 2, Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Top Right

		//Triangle 1, Top
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 2, Top
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top Left
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Top Right

		//Triangle 1, Bottom
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Top Right
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Top Left
		//Triangle 2, Bottom
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Bottom Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Bottom Right
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Top Right
	};

	//Constructor
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *textures[]) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE) {
		for (unsigned int i = 0; i < 6; i++) {
			this->textures[i] = textures[i];
			this->renderedSides[i] = 1;
		}
		textureLocation = shader->getUniformLocation("texture1");
	}
	Cube::Cube(const Cube &cube) : Shape(cube.getCenterPosition(), cube.getDimensions(), cube.shader, VERTICES, VERTICES_SIZE, cube.POSITION_ONLY_VERTICES, ShapeType::CUBE) {
		for (unsigned int i = 0; i < 6; i++) {
			textures[i] = cube.textures[i];
			renderedSides[i] = cube.renderedSides[i];
		}
		textureLocation = cube.textureLocation;
	}

	//Public
	bool Cube::collision(glm::vec3 position, glm::vec3 dimensions) {
		if (position.x + 0.5f * dimensions.x > getCenterPosition().x - 0.5f * getDimensions().x &&
			position.x - 0.5f * dimensions.x < getCenterPosition().x + 0.5f * getDimensions().x &&
			position.y > getCenterPosition().y - 0.5f * getDimensions().y &&
			position.y - dimensions.y < getCenterPosition().y + 0.499999f * getDimensions().y &&
			position.z + 0.5f * dimensions.z > getCenterPosition().z - 0.5f * getDimensions().z &&
			position.z - 0.5f * dimensions.z < getCenterPosition().z + 0.5f * getDimensions().z) {

			return true;
		}
		return false;
	}
	void Cube::draw() {
		glEnable(GL_CULL_FACE);
		transform();
		for (unsigned int i = 0; i <= 30; i += 6) {
			if (renderedSides[i / 6]) {
				textures[i / 6]->setUniform(shader, textureLocation, 0);
				textures[i / 6]->activate(GL_TEXTURE0);

				glDrawArrays(GL_TRIANGLES, i, 6);
			}
		}
	}
	void Cube::setRenderedSides(bool renderedSides[6]) {
		for (unsigned int i = 0; i < 6; i++) {
			this->renderedSides[i] = renderedSides[i];
		}
	}
}