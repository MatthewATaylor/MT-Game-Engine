#include "Cube.h"

namespace mtge {
	//Constructor
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *texture) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE), TEXTURE_S_OFFSET(0.0f), TEXTURE_T_OFFSET(0.0f) {
		for (unsigned int i = 0; i < 6; i++) {
			this->renderedSides[i] = 1;
		}
		this->texture = texture;
		textureLocation = shader->getUniformLocation("texture1");
	}
	Cube::Cube(const Cube &cube) : Shape(cube.getCenterPosition(), cube.getDimensions(), cube.shader, VERTICES, VERTICES_SIZE, cube.POSITION_ONLY_VERTICES, ShapeType::CUBE), TEXTURE_S_OFFSET(cube.TEXTURE_S_OFFSET), TEXTURE_T_OFFSET(cube.TEXTURE_T_OFFSET) {
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
			position.y + 0.5f * dimensions.y > getCenterPosition().y - 0.5f * getDimensions().y &&
			position.y - 0.5f * dimensions.y < getCenterPosition().y + 0.5f/*0.499999f*/ * getDimensions().y &&
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