#include "Rendering/Skybox.h"

namespace mtge {
	//Private
	const float Skybox::VERTEX_BUFFER[VERTEX_BUFFER_LENGTH] = {
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
	unsigned int Skybox::vertexArrayID = 0;
	unsigned int Skybox::vertexBufferID = 0;

	//Public
	void Skybox::init() {
		glGenVertexArrays(1, &vertexArrayID);
		glGenBuffers(1, &vertexBufferID);

		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE, VERTEX_BUFFER, GL_STATIC_DRAW);

		//Position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}
	void Skybox::render(Camera *camera, Window *window) {
		glBindVertexArray(vertexArrayID);

		if (!Texture::getSkyboxPtr()) {
			std::cout << "WARNING [FUNCTION: render]: SKYBOX TEXTURE UNINITIALIZED" << std::endl << std::endl;
		}

		Shader *shader = Shader::getSkyboxPtr();
		if (!shader) {
			std::cout << "ERROR [FUNCTION: render]: SKYBOX SHADER UNINITIALIZED" << std::endl << std::endl;
			return;
		}
		shader->useProgram();

		math::Mat<float, 4, 4> modelMatrix = math::Util::MatGen::identity<float, 4>();
		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, modelMatrix.getPtr());

		math::Mat<float, 4, 4> viewMatrix = camera->getViewMatrix();
		viewMatrix.set(1, 4, 0.0f);
		viewMatrix.set(2, 4, 0.0f);
		viewMatrix.set(3, 4, 0.0f);
		viewMatrix.set(4, 1, 0.0f);
		viewMatrix.set(4, 2, 0.0f);
		viewMatrix.set(4, 3, 0.0f);
		viewMatrix.set(4, 4, 1.0f);
		glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());

		math::Mat<float, 4, 4> projectionMatrix = camera->getProjectionMatrix(window);
		glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, projectionMatrix.getPtr());

		glDepthFunc(GL_LEQUAL);
		glDisable(GL_CULL_FACE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthFunc(GL_LESS);
	}
	void Skybox::freeResources() {
		glDeleteVertexArrays(1, &vertexArrayID);
		glDeleteBuffers(1, &vertexBufferID);
	}
}