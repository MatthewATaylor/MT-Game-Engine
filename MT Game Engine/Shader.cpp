#include "Shader.h"

namespace mtge {
	//Constructor
	Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource) {
		readShaderFiles(vertexShaderSource, fragmentShaderSource);
	}

	//Private
	void Shader::checkShaderErrors(unsigned int ID, const char *errorType) {
		int success;
		char infoLog[512];
		if (errorType == "PROGRAM") {
			glGetProgramiv(ID, GL_LINK_STATUS, &success);
		}
		else {
			glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		}

		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR: " << errorType << " SHADER UNSUCCESSFUL\n" << infoLog << std::endl;
		}
	}
	void Shader::readShaderFiles(const char* vertexShaderSource, const char* fragmentShaderSource) {
		std::ifstream vertexFileInput, fragmentFileInput;

		vertexFileInput.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		fragmentFileInput.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		std::string vertexReadString;
		std::string fragmentReadString;

		//Extract GLSL Code from Files
		try {
			vertexFileInput.open(vertexShaderSource);
			fragmentFileInput.open(fragmentShaderSource);

			std::stringstream vertexStream, fragmentStream;
			vertexStream << vertexFileInput.rdbuf();
			fragmentStream << fragmentFileInput.rdbuf();

			vertexFileInput.close();
			fragmentFileInput.close();

			vertexReadString = vertexStream.str();
			fragmentReadString = fragmentStream.str();
		}
		catch (const std::ifstream::failure e) {
			std::cout << "ERROR: SHADER FILES COULD NOT BE READ" << std::endl;
		}

		const char* vertexShader = vertexReadString.c_str();
		const char* fragmentShader = fragmentReadString.c_str();

		//Compile Vertex Shader
		unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
		glCompileShader(vertexShaderID);
		checkShaderErrors(vertexShaderID, "VERTEX");

		//Compile Fragment Shader
		unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
		glCompileShader(fragmentShaderID);
		checkShaderErrors(fragmentShaderID, "FRAGMENT");

		//Link Shaders
		unsigned int shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glLinkProgram(shaderProgramID);
		this->shaderProgramID = shaderProgramID;
		checkShaderErrors(shaderProgramID, "PROGRAM");

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	//Public
	void Shader::useShaderProgram() {
		glUseProgram(shaderProgramID);
	}
	void Shader::setBoolUniform(unsigned int location, bool newValue) {
		glUniform1i(location, (int)newValue);
	}
	void Shader::setIntUniform(unsigned int location, int newValue) {
		glUniform1i(location, newValue);
	}
	void Shader::setFloatUniform(unsigned int location, float newValue) {
		glUniform1f(location, newValue);
	}
	unsigned int Shader::getUniformLocation(const char *uniformName) {
		return glGetUniformLocation(shaderProgramID, uniformName);
	}
}