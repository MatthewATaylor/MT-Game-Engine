#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>

namespace mtge {
	enum class ShaderType {
		VERTEX, FRAGMENT
	};

	class Shader {
	private:
		unsigned int ID;
		unsigned int projectionLocation;
		unsigned int viewLocation;
		unsigned int modelLocation;

		void checkShaderCompileErrors(unsigned int ID, ShaderType shaderType);
		void checkShaderLinkErrors(unsigned int ID);
		void readShaderFiles(const char* vertexShaderSource, const char* fragmentShaderSource);

	public:
		Shader(const char* vertexShaderSource, const char* fragmentShaderSource);

		void useProgram();
		void setBoolUniform(unsigned int location, bool newValue);
		void setIntUniform(unsigned int location, int newValue);
		void setFloatUniform(unsigned int location, float newValue);

		unsigned int getUniformLocation(const char *uniformName);
		unsigned int getID();
		unsigned int getProjectionLocation();
		unsigned int getViewLocation();
		unsigned int getModelLocation();
	};
}