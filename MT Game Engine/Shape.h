#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Buffer.h"

namespace mtge {
	class Shape {
	private:
		Buffer *buffer;
		const float *VERTICES = nullptr;
		const unsigned int VERTICES_SIZE;
		const bool POSITION_ONLY_VERTICES;
		const char *NAME;
		unsigned int modelLocation;
		glm::mat4 model = glm::mat4(1.0f);

		void transformInit();
		void setBuffers();
		void deleteBuffers();

	protected:
		glm::vec3 pos;
		glm::vec3 dimensions;
		Shader *shader = nullptr;
		unsigned int textureLocation;

		Shape(glm::vec3 pos, glm::vec3 dimensions, const float *VERTICES, const unsigned int VERTICES_SIZE, Shader *shader, const bool POSITION_ONLY_VERTICES, const char *NAME);
		void transform();

	public:
		glm::vec3 translatedPos;
		glm::vec3 scaledDimensions;

		~Shape();
		void updateBuffers();
		void translate(glm::vec3 translation);
		void rotate(glm::vec3 rotationAngles);
		void scale(glm::vec3 scaleDimensions);
		const char *getName();
		virtual bool collision(glm::vec3 position, glm::vec3 dimensions);
		virtual void draw() = 0;
	};
}