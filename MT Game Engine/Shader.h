#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>

namespace mtge {
	class Shader {
	private:
		void checkShaderErrors(unsigned int ID, const char *errorType);
		void readShaderFiles(const char* vertexShaderSource, const char* fragmentShaderSource);
	public:
		unsigned int shaderProgramID;

		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

		void useShaderProgram();
		void setBoolUniform(unsigned int location, bool newValue);
		void setIntUniform(unsigned int location, int newValue);
		void setFloatUniform(unsigned int location, float newValue);
		unsigned int getUniformLocation(const char *uniformName);
	};
}