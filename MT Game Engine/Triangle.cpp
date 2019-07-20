#include "Triangle.h"

namespace mtge {
	const float Triangle::VERTICES[] = {
		//Positions-----------Colors---------------Texture-----
		-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  1.0f,  //Top
	};

	//Constructor
	Triangle::Triangle(glm::vec3 pos, glm::vec3 dimensions, Texture *texture) : Shape(pos, dimensions, ResourceManager::getShapeShaderPtr(), VERTICES, VERTICES_SIZE, true, ShapeType::TRIANGLE) {
		this->texture = texture;
		textureLocation = shader->getUniformLocation("texture1");
	}
	Triangle::Triangle(const Triangle &triangle) : Shape(triangle.getCenterPosition(), triangle.getDimensions(), triangle.shader, VERTICES, VERTICES_SIZE, triangle.POSITION_ONLY_VERTICES, ShapeType::TRIANGLE) {
		texture = triangle.texture;
		textureLocation = triangle.textureLocation;
	}

	//Public
	void Triangle::draw() {
		glDisable(GL_CULL_FACE);
		transform();
		texture->setUniform(shader, textureLocation, 0);
		texture->activate(GL_TEXTURE0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}