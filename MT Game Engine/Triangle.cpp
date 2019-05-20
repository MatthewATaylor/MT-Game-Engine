#include "Triangle.h"

namespace mtge {
	const float Triangle::VERTICES[] = {
		//Positions-----------Colors---------------Texture-----
		-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.5f,  1.0f,  //Top
	};

	//Constructor
	Triangle::Triangle(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *texture) : Shape(pos, dimensions, VERTICES, VERTICES_SIZE, shader, true, Shape::Type::TRIANGLE) {
		this->texture = texture;
		textureLocation = glGetUniformLocation(shader->shaderProgramID, "texture1");
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