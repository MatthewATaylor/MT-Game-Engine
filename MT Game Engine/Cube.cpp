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
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *textures[], bool renderedSides[]) : Shape(pos, dimensions, VERTICES, VERTICES_SIZE, shader, false, "CUBE") {
		for (unsigned int i = 0; i < 6; i++) {
			this->textures[i] = textures[i];
			this->renderedSides[i] = renderedSides[i];
		}
		textureLocation = glGetUniformLocation(shader->shaderProgramID, "texture1");
	}
	Cube::Cube(glm::vec3 pos, glm::vec3 dimensions, Shader *shader, Texture *textures[]) : Shape(pos, dimensions, VERTICES, VERTICES_SIZE, shader, false, "CUBE") {
		for (unsigned int i = 0; i < 6; i++) {
			this->textures[i] = textures[i];
			this->renderedSides[i] = 1;
		}
		textureLocation = glGetUniformLocation(shader->shaderProgramID, "texture1");
	}

	//Public
	bool Cube::collision(glm::vec3 cameraPosition, const glm::vec3 CAMERA_DIMENSIONS) {
		if (cameraPosition.x + 0.5f * CAMERA_DIMENSIONS.x > translatedPos.x - 0.5f * scaledDimensions.x &&
			cameraPosition.x - 0.5f * CAMERA_DIMENSIONS.x < translatedPos.x + 0.5f * scaledDimensions.x &&
			cameraPosition.y > translatedPos.y - 0.5f * scaledDimensions.y &&
			cameraPosition.y - CAMERA_DIMENSIONS.y < translatedPos.y + 0.499999f * scaledDimensions.y &&
			cameraPosition.z + 0.5f * CAMERA_DIMENSIONS.z > translatedPos.z - 0.5f * scaledDimensions.z &&
			cameraPosition.z - 0.5f * CAMERA_DIMENSIONS.z < translatedPos.z + 0.5f * scaledDimensions.z) {

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
}