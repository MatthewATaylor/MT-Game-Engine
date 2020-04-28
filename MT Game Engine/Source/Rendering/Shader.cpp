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
		std::string defaultTexturedShapeVertexShader = R"(
			#version 330 core

			layout(location = 0) in vec3 vertexPosition;
			layout(location = 1) in vec2 vertexTextureCoord;

			out vec2 fragmentTextureCoord;
			out float visibility;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			const float FOG_DENSITY = 0.25f;
			const float FOG_GRADIENT = 9.0f;

			void main() {
				vec4 eyePosition = view * model * vec4(vertexPosition, 1.0f);
				gl_Position = projection * eyePosition;
				fragmentTextureCoord = vertexTextureCoord;
				
				float distance = length(eyePosition.xyz);
				visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
				visibility = clamp(visibility, 0.0f, 1.0f);
			}
		)";

		std::string defaultTexturedShapeFragmentShader = R"(
			#version 330 core

			in vec2 fragmentTextureCoord;
			in float visibility;

			out vec4 finalFragmentColor;

			uniform sampler2D texture1;

			void main() {
				finalFragmentColor = texture(texture1, fragmentTextureCoord);
				finalFragmentColor = mix(vec4(0.0f, 0.0f, 0.0f, 1.0f), finalFragmentColor, visibility);
			}
		)";

		std::string defaultSkyboxVertexShader = R"(
			#version 330 core

			layout(location = 0) in vec3 vertexPositions;

			out vec3 fragmentTextureCoord;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;

			void main() {
				vec4 transformedPosition = projection * view * model * vec4(vertexPositions, 1.0f);
				gl_Position = transformedPosition.xyww;
				fragmentTextureCoord = vertexPositions;
			}
		)";

		std::string defaultSkyboxFragmentShader = R"(
			#version 330 core

			in vec3 fragmentTextureCoord;

			out vec4 finalFragmentColor;

			uniform samplerCube skybox;

			void main() {
				finalFragmentColor = texture(skybox, fragmentTextureCoord);
			}
		)";

		texturedShape = new Shader(defaultTexturedShapeVertexShader, defaultTexturedShapeFragmentShader, false);
		skybox = new Shader(defaultSkyboxVertexShader, defaultSkyboxFragmentShader, false);
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