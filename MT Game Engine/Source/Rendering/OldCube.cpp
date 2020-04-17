#include "Rendering/OldCube.h"

namespace mtge {
	//Constructor
	OldCube::OldCube(glm::vec3 pos, glm::vec3 dimensions, Texture *textureAtlas, TextureAtlasSegment *textureAtlasSegment) : Shape(pos, dimensions, Shader::getTexturedShapePtr(), VERTICES, VERTICES_SIZE, false, ShapeType::CUBE), texAS(textureAtlasSegment) {
		//this->textureAtlas = textureAtlas;
		//textureLocation = shader->getUniformLocation("texture1");
		//this->textureAtlas->setUniform(shader, textureLocation, 0);
		//this->textureAtlas->activate(GL_TEXTURE0);
	}
	OldCube::OldCube(const OldCube &cube) : Shape(cube.getCenterPosition(), cube.getDimensions(), cube.shader, VERTICES, VERTICES_SIZE, cube.POSITION_ONLY_VERTICES, ShapeType::CUBE), texAS(cube.texAS) {
		//textureAtlas = cube.textureAtlas;
		//textureLocation = cube.textureLocation;
		//textureAtlas->setUniform(shader, textureLocation, 0);
		//textureAtlas->activate(GL_TEXTURE0);
	}

	//Public
	bool OldCube::collision(math::Vec<float, 3> position, math::Vec<float, 3> dimensions) {
		if (position.getX() + 0.5f * dimensions.getX() > getCenterPosition().x - 0.5f * getDimensions().x &&
			position.getX() - 0.5f * dimensions.getX() < getCenterPosition().x + 0.5f * getDimensions().x &&
			position.getY() + 0.5f * dimensions.getY() > getCenterPosition().y - 0.5f * getDimensions().y &&
			position.getY() - 0.5f * dimensions.getY() < getCenterPosition().y + 0.5f/*0.499999f*/ * getDimensions().y &&
			position.getZ() + 0.5f * dimensions.getZ() > getCenterPosition().z - 0.5f * getDimensions().z &&
			position.getZ() - 0.5f * dimensions.getZ() < getCenterPosition().z + 0.5f * getDimensions().z) {

			return true;
		}
		return false;
	}
	void OldCube::draw() {
		glEnable(GL_CULL_FACE);
		transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}