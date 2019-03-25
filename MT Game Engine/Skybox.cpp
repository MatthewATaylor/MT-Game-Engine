#include "Skybox.h"

namespace mtge {
	const float Skybox::VERTICES[] = {
		//Triangle 1, Front
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 //Triangle 2, Front
		 -0.5f,  0.5f,  0.5f,
		  0.5f, -0.5f,  0.5f,
		  0.5f,  0.5f,  0.5f,

		  //Triangle 1, Back
		  -0.5f,  0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,
		  -0.5f, -0.5f, -0.5f,
		  //Triangle 2, Back
		  -0.5f,  0.5f, -0.5f,
		   0.5f,  0.5f, -0.5f,
		   0.5f, -0.5f, -0.5f,

		   //Triangle 1, Left
		   -0.5f,  0.5f, -0.5f,
		   -0.5f, -0.5f, -0.5f,
		   -0.5f, -0.5f,  0.5f,
		   //Triangle 2, Left
		   -0.5f,  0.5f, -0.5f,
		   -0.5f, -0.5f,  0.5f,
		   -0.5f,  0.5f,  0.5f,

		   //Triangle 1, Right
			0.5f,  0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
			0.5f, -0.5f, -0.5f,
			//Triangle 2, Right
			 0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,

			 //Triangle 1, Top
			 -0.5f,  0.5f, -0.5f,
			 -0.5f,  0.5f,  0.5f,
			  0.5f,  0.5f,  0.5f,
			  //Triangle 2, Top
			  -0.5f,  0.5f, -0.5f,
			   0.5f,  0.5f,  0.5f,
			   0.5f,  0.5f, -0.5f,

			   //Triangle 1, Bottom
			   -0.5f, -0.5f, -0.5f,
				0.5f, -0.5f,  0.5f,
			   -0.5f, -0.5f,  0.5f,
			   //Triangle 2, Bottom
			   -0.5f, -0.5f, -0.5f,
				0.5f, -0.5f, -0.5f,
				0.5f, -0.5f,  0.5f,
	};

	//Constructor
	Skybox::Skybox(Shader *shader, Texture *texture) : Shape(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), VERTICES, VERTICES_SIZE, shader, true, "SKYBOX") {
		this->texture = texture;
		textureLocation = glGetUniformLocation(shader->shaderProgramID, "skybox");
	}

	//Public
	void Skybox::draw() {
		glDisable(GL_CULL_FACE);
		transform();
		texture->setUniform(shader, textureLocation, 0);
		texture->activate(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}