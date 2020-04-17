#include "Rendering/Shader.h"

namespace mtge {
	//Constructor
	Shader::Shader(std::string vertexShaderSource, std::string fragmentShaderSource, bool fromFiles) {
		if (fromFiles) {
			readShadersFromFiles(vertexShaderSource, fragmentShaderSource);
		}
		else {
			readShaders(vertexShaderSource, fragmentShaderSource);
		}
		projectionLocation = getUniformLocation("projection");
		viewLocation = getUniformLocation("view");
		modelLocation = getUniformLocation("model");
	}
	
	//Private
	Shader *Shader::texturedShape = nullptr;
	Shader *Shader::skybox = nullptr;

	void Shader::checkShaderCompileErrors(unsigned int ID, ShaderType shaderType) {
		const int ERROR_BUFFER_SIZE = 512;
		int success;
		char infoLog[ERROR_BUFFER_SIZE];
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(ID, ERROR_BUFFER_SIZE, 0, infoLog);
			const char *shaderTypeStr = "[UNDEFINED SHADER TYPE]";
			if (shaderType == ShaderType::VERTEX) {
				shaderTypeStr = "VERTEX";
			}
			else if (shaderType == ShaderType::FRAGMENT) {
				shaderTypeStr = "FRAGMENT";
			}
			std::cout << "ERROR: " << shaderTypeStr << " SHADER FAILED TO COMPILE"  << std::endl << infoLog << std::endl;
		}
	}
	void Shader::checkShaderLinkErrors(unsigned int ID) {
		int success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);

		if (!success) {
			std::cout << "ERROR: SHADERS FAILED TO LINK" << std::endl << std::endl;
		}
	}
	void Shader::readShadersFromFiles(std::string vertexShaderFile, std::string fragmentShaderFile) {
		std::ifstream vertexFileInput, fragmentFileInput;

		vertexFileInput.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		fragmentFileInput.exceptions(std::ifstream::badbit | std::ifstream::failbit);

		std::string vertexReadString;
		std::string fragmentReadString;

		//Extract GLSL Code from Files
		try {
			vertexFileInput.open(vertexShaderFile);
			fragmentFileInput.open(fragmentShaderFile);

			std::stringstream vertexStream, fragmentStream;
			vertexStream << vertexFileInput.rdbuf();
			fragmentStream << fragmentFileInput.rdbuf();

			vertexFileInput.close();
			fragmentFileInput.close();

			vertexReadString = vertexStream.str();
			fragmentReadString = fragmentStream.str();
		}
		catch (const std::ifstream::failure e) {
			std::cout << "ERROR [FUNCTION: readShaderFiles]: SHADER FILES COULD NOT BE READ" << std::endl << std::endl;
		}

		readShaders(vertexReadString, fragmentReadString);
	}
	void Shader::readShaders(std::string vertexShader, std::string fragmentShader) {
		const char* vertexShader_cstr = vertexShader.c_str();
		const char* fragmentShader_cstr = fragmentShader.c_str();
		
		//Compile Vertex Shader
		unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexShader_cstr, NULL);
		glCompileShader(vertexShaderID);
		checkShaderCompileErrors(vertexShaderID, ShaderType::VERTEX);

		//Compile Fragment Shader
		unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShader_cstr, NULL);
		glCompileShader(fragmentShaderID);
		checkShaderCompileErrors(fragmentShaderID, ShaderType::FRAGMENT);

		//Link Shaders
		unsigned int shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, vertexShaderID);
		glAttachShader(shaderProgramID, fragmentShaderID);
		glLinkProgram(shaderProgramID);
		this->ID = shaderProgramID;
		checkShaderLinkErrors(ID);

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	//Public
	void Shader::useProgram() {
		glUseProgram(ID);
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
		return glGetUniformLocation(ID, uniformName);
	}
	unsigned int Shader::getID() {
		return ID;
	}
	unsigned int Shader::getProjectionLocation() {
		return projectionLocation;
	}
	unsigned int Shader::getViewLocation() {
		return viewLocation;
	}
	unsigned int Shader::getModelLocation() {
		return modelLocation;
	}
	void Shader::loadShaders(
		std::string texturedShapeVertexShaderPath,
		std::string texturedShapeFragmentShaderPath,
		std::string skyboxVertexShaderPath,
		std::string skyboxFragmentShaderPath) {

		texturedShape = new Shader(texturedShapeVertexShaderPath, texturedShapeFragmentShaderPath, true);
		skybox = new Shader(skyboxVertexShaderPath, skyboxFragmentShaderPath, true);
	}
	void Shader::loadDefaultShaders() {

	}
	Shader *Shader::getTexturedShapePtr() {
		return texturedShape;
	}
	Shader *Shader::getSkyboxPtr() {
		return skybox;
	}
	void Shader::freeResources() {
		if (texturedShape) {
			delete texturedShape;
		}
		if (skybox) {
			delete skybox;
		}
	}
}