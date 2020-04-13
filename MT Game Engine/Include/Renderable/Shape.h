#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Shader.h"
#include "../Buffer.h"
#include "../Math/Vec.h"

namespace mtge {
	enum class ShapeType {
		CUBE, PYRAMID, TRIANGLE, SKYBOX, UNDEFINED
	};

	class Shape {
	private:
		Buffer *buffer;
		const float *VERTICES = nullptr;
		const unsigned int VERTICES_SIZE;
		const ShapeType TYPE;
		unsigned int modelLocation;
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 centerPosition;
		glm::vec3 dimensions;
		bool deletable = false;

		void transformInit();
		void setBuffers();
		void deleteBuffers();

	protected:
		const bool POSITION_ONLY_VERTICES;
		Shader *shader = nullptr;
		unsigned int textureLocation;

		Shape(glm::vec3 position, glm::vec3 dimensions, Shader *shader, const float *VERTICES, const unsigned int VERTICES_SIZE, const bool POSITION_ONLY_VERTICES, const ShapeType TYPE);
		void transform();

	public:
		void updateBuffers();
		void translate(glm::vec3 translation);
		void rotate(glm::vec3 rotationAngles);
		void scale(glm::vec3 scaleDimensions);
		void setDeletable(bool deletable);
		bool getDeletable() const;
		const ShapeType getType() const;
		glm::vec3 getCenterPosition() const;
		glm::vec3 getDimensions() const;

		virtual bool collision(math::Vec<float, 3> position, math::Vec<float, 3> dimensions);

		~Shape();

		virtual void draw() = 0;
	};
}