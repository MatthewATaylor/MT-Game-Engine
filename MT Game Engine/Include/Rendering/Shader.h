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

		static Shader *texturedShape;
		static Shader *skybox;

		void checkShaderCompileErrors(unsigned int ID, ShaderType shaderType);
		void checkShaderLinkErrors(unsigned int ID);
		void readShadersFromFiles(std::string vertexShaderFile, std::string fragmentShaderFile);
		void readShaders(std::string vertexShader, std::string fragmentShader);

	public:
		Shader(std::string vertexShaderSource, std::string fragmentShaderSource, bool fromFiles);

		void useProgram();
		void setBoolUniform(unsigned int location, bool newValue);
		void setIntUniform(unsigned int location, int newValue);
		void setFloatUniform(unsigned int location, float newValue);

		unsigned int getUniformLocation(const char *uniformName);
		unsigned int getID();
		unsigned int getProjectionLocation();
		unsigned int getViewLocation();
		unsigned int getModelLocation();

		static void loadShaders(
			std::string texturedShapeVertexShaderPath, 
			std::string texturedShapeFragmentShaderPath, 
			std::string skyboxVertexShaderPath, 
			std::string skyboxFragmentShaderPath
		);
		static void loadDefaultShaders();

		static Shader *getTexturedShapePtr();
		static Shader *getSkyboxPtr();
		static void freeResources();
	};
}