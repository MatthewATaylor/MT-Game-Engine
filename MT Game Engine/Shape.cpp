#include "Shape.h"

namespace mtge {
	//Constructor
	Shape::Shape(glm::vec3 pos, glm::vec3 dimensions, const float *VERTICES, const unsigned int VERTICES_SIZE, Shader *shader, const bool POSITION_ONLY_VERTICES, const char *NAME) : VERTICES_SIZE(VERTICES_SIZE), POSITION_ONLY_VERTICES(POSITION_ONLY_VERTICES), NAME(NAME) {
		this->pos = pos;
		this->dimensions = dimensions;
		this->VERTICES = VERTICES;
		this->shader = shader;
		setBuffers();
		modelLocation = glGetUniformLocation(shader->shaderProgramID, "model");
		transformInit();
	}

	//Private
	void Shape::transformInit() {
		translate(glm::vec3(0.0f, 0.0f, 0.0f));
		scale(glm::vec3(1.0f, 1.0f, 1.0f));
	}
	void Shape::setBuffers() {
		buffer = new Buffer(VERTICES, VERTICES_SIZE, POSITION_ONLY_VERTICES);
		buffer->useBuffer();
	}
	void Shape::deleteBuffers() {
		buffer->deleteBuffer();
		delete buffer;
	}

	//Protected
	void Shape::transform() {
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
	}

	//Public
	void Shape::updateBuffers() {
		buffer->updateBuffer();
	}
	void Shape::translate(glm::vec3 translation) {
		translatedPos = pos + translation;
		model = glm::translate(model, pos + translation);
	}
	void Shape::rotate(glm::vec3 rotationAngles) {
		model = glm::rotate(model, rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	void Shape::scale(glm::vec3 scaleDimensions) {
		scaledDimensions = dimensions * scaleDimensions;
		model = glm::scale(model, dimensions * scaleDimensions);
	}
	const char *Shape::getName() {
		return NAME;
	}
	bool Shape::collision(glm::vec3 position, glm::vec3 dimensions) {
		return false;
	}

	//Destructor
	Shape::~Shape() {
		deleteBuffers();
	}
}