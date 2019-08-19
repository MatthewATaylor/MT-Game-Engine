#include "Cube.h"

namespace mtge {
	//Constructor
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *texture) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE), texAS(0, 0, 4, 4), USES_ATLAS(false) {
		this->texture = texture;
		textureLocation = shader->getUniformLocation("texture1");
	}
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Texture *textureAtlas, TextureAtlasSegment textureAtlasSegment) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE), texAS(textureAtlasSegment), USES_ATLAS(true) {
		texture = textureAtlas;
		textureLocation = shader->getUniformLocation("texture1");
		texture->setUniform(shader, textureLocation, 0);
		texture->activate(GL_TEXTURE0);
	}
	Cube::Cube(const Cube &cube) : Shape(cube.getCenterPosition(), cube.getDimensions(), cube.shader, VERTICES, VERTICES_SIZE, cube.POSITION_ONLY_VERTICES, ShapeType::CUBE), texAS(cube.texAS), USES_ATLAS(cube.USES_ATLAS) {
		texture = cube.texture;
		textureLocation = cube.textureLocation;
		if (USES_ATLAS) {
			texture->setUniform(shader, textureLocation, 0);
			texture->activate(GL_TEXTURE0);
		}
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
		if (!USES_ATLAS) {
			texture->setUniform(shader, textureLocation, 0);
			texture->activate(GL_TEXTURE0);
		}
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}