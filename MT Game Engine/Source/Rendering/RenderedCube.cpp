#include "Rendering/RenderedCube.h"

namespace mtge {
	//Constructor
	RenderedCube::RenderedCube(CubeTexture *texture, math::Vec3 position, math::Vec3 dimensions) : Renderable() {
		this->position = position;
		this->dimensions = dimensions;

		ChunkData data;
		data.addCube(
			texture,
			math::Vec3(0.0f),
			2.0f,
			false,
			false,
			false,
			false,
			false,
			false
		);
		numVertices = data.getVerticesInBuffer();

		glBindVertexArray(vertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		data.sendBuffer();

		//Position vertex attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Color vertex attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	//Public
	void RenderedCube::render(Camera *camera, Window *window) {
		if (!Texture::getAtlasPtr()) {
			std::cout << "WARNING [FUNCTION: render]: TEXTURE ATLAS UNINITIALIZED" << std::endl << std::endl;
		}

		Shader *shader = Shader::getTexturedShapePtr();
		if (!shader) {
			std::cout << "ERROR [FUNCTION: render]: UNINITIALIZED TEXTURED SHAPE SHADER" << std::endl << std::endl;
			return;
		}
		shader->useProgram();

		math::Mat4 viewMatrix = camera->getViewMatrix();
		glUniformMatrix4fv(shader->getViewLocation(), 1, GL_FALSE, viewMatrix.getPtr());

		math::Mat4 projectionMatrix = camera->getProjectionMatrix(window);
		glUniformMatrix4fv(shader->getProjectionLocation(), 1, GL_FALSE, projectionMatrix.getPtr());

		math::Mat4 modelMatrix = math::Util::MatGen::scale<float, 4>(dimensions);
		modelMatrix = modelMatrix * math::Util::MatGen::translation<float, 4>(position);
		glUniformMatrix4fv(shader->getModelLocation(), 1, GL_FALSE, modelMatrix.getPtr());

		glBindVertexArray(vertexArrayID);
		glDisable(GL_CULL_FACE);
		glDrawArrays(GL_TRIANGLES, 0, numVertices);
	}
}