#include "Cube.h"

namespace mtge {
	const float Cube::VERTICES[] = {
		//Positions-----------Colors---------------Texture-------
		//Triangle 1, Front
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Top Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.25f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.25f,  //Bottom Right
		//Triangle 2, Front
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Top Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.25f,  //Bottom Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.50f,  //Top Right

		//Triangle 1, Back
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  1.00f,  //Top Right
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.75f,  //Bottom Left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.75f,  //Bottom Right
		//Triangle 2, Back
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  1.00f,  //Top Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  1.00f,  //Top Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.75f,  //Bottom Left
		
		//Triangle 1, Left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f,  0.75f,  //Top Left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f,  0.50f,  //Bottom Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Bottom Right
		//Triangle 2, Left
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.00f,  0.75f,  //Top Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Bottom Right
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.75f,  //Top Right

		//Triangle 1, Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.75f,  //Top Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.50f,  //Bottom Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f,  0.50f,  //Bottom Right
		//Triangle 2, Right
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.75f,  //Top Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f,  0.50f,  //Bottom Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.75f,  0.75f,  //Top Right

		//Triangle 1, Top
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.25f,  //Top Left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.00f,  //Bottom Left
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.00f,  //Bottom Right
		//Triangle 2, Top
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.25f,  //Top Left
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.00f,  //Bottom Right
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.25f,  //Top Right

		//Triangle 1, Bottom
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.75f,  //Top Right
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.75f,  //Top Left
		//Triangle 2, Bottom
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.25f,  0.50f,  //Bottom Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.50f,  //Bottom Right
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.50f,  0.75f,  //Top Right
	};

	//Constructor
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *texture) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE) {
		for (unsigned int i = 0; i < 6; i++) {
			this->renderedSides[i] = 1;
		}
		this->texture = texture;
		textureLocation = shader->getUniformLocation("texture1");
	}
	Cube::Cube(const Cube &cube) : Shape(cube.getCenterPosition(), cube.getDimensions(), cube.shader, VERTICES, VERTICES_SIZE, cube.POSITION_ONLY_VERTICES, ShapeType::CUBE) {
		for (unsigned int i = 0; i < 6; i++) {
			renderedSides[i] = cube.renderedSides[i];
		}
		texture = cube.texture;
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
		texture->setUniform(shader, textureLocation, 0);
		texture->activate(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	void Cube::setRenderedSides(bool renderedSides[6]) {
		for (unsigned int i = 0; i < 6; i++) {
			this->renderedSides[i] = renderedSides[i];
		}
	}
}