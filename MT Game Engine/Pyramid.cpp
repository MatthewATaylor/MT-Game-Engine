#include "Pyramid.h"

namespace mtge {
	const float Pyramid::VERTICES[] = {
		//Positions-----------Colors---------------Texture-----
		//Triangle 1, Bottom
		 0.0f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 2
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Bottom Left
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 3
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top
		 0.0f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  //Bottom Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
		//Triangle 4
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  //Top
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  //Bottom Left
		 0.0f, -0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,  //Bottom Right
	};

	//Constructor
	Pyramid::Pyramid(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *textures[]) : Shape(pos, dimensions, VERTICES, VERTICES_SIZE, shader, false, ShapeType::PYRAMID) {
		for (unsigned int i = 0; i < 4; i++) {
			this->textures[i] = textures[i];
		}
		textureLocation = glGetUniformLocation(shader->shaderProgramID, "texture1");
	}

	//Public
	void Pyramid::draw() {
		glEnable(GL_CULL_FACE);
		transform();
		for (unsigned int i = 0; i <= 9; i += 3) {
			textures[i / 3]->setUniform(shader, textureLocation, 0);
			textures[i / 3]->activate(GL_TEXTURE0);

			glDrawArrays(GL_TRIANGLES, i, 3);
		}
	}
}