#include "../../Include/Renderable/Skybox.h"

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
	Skybox::Skybox(Texture *texture) : Shape(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), ResourceManager::getSkyboxShaderPtr(), VERTICES, VERTICES_SIZE, true, ShapeType::SKYBOX) {
		this->texture = texture;
		textureLocation = shader->getUniformLocation("skybox");
		texture->setUniform(shader, textureLocation, 1);
		texture->activate(GL_TEXTURE1);
	}

	//Public
	void Skybox::draw() {
		glDisable(GL_CULL_FACE);
		transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}