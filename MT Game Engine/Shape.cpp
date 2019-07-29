#include "Shape.h"

namespace mtge {
	//Constructor
	Shape::Shape(glm::vec3 centerPosition, glm::vec3 dimensions, Shader *shader, const float *VERTICES, const unsigned int VERTICES_SIZE, const bool POSITION_ONLY_VERTICES, const ShapeType TYPE) : VERTICES_SIZE(VERTICES_SIZE), POSITION_ONLY_VERTICES(POSITION_ONLY_VERTICES), TYPE(TYPE) {
		this->centerPosition = centerPosition;
		this->dimensions = dimensions;
		this->VERTICES = VERTICES;
		this->shader = shader;
		setBuffers();
		modelLocation = shader->getModelLocation();
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
		//if (transformed) {
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		//}
		transformed = false;
	}

	//Public
	void Shape::updateBuffers() {
		buffer->updateBuffer();
	}
	void Shape::translate(glm::vec3 translation) {
		transformed = true;
		centerPosition += translation;
		model = glm::translate(model, centerPosition);
	}
	void Shape::rotate(glm::vec3 rotationAngles) {
		transformed = true;
		model = glm::rotate(model, rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	void Shape::scale(glm::vec3 scaleDimensions) {
		transformed = true;
		dimensions *= scaleDimensions;
		model = glm::scale(model, dimensions);
	}
	void Shape::setDeletable(bool deletable) {
		this->deletable = deletable;
	}
	bool Shape::getDeletable() const {
		return deletable;
	}
	const ShapeType Shape::getType() const {
		return TYPE;
	}
	glm::vec3 Shape::getCenterPosition() const {
		return centerPosition;
	}
	glm::vec3 Shape::getDimensions() const {
		return dimensions;
	}
	bool Shape::collision(glm::vec3 position, glm::vec3 dimensions) {
		return false;
	}

	//Destructor
	Shape::~Shape() {
		deleteBuffers();
	}
}