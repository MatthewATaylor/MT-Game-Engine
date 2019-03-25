#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <stb_image.h>

#include "Shader.h"

namespace mtge {
	class Texture {
	private:
		unsigned int textureID;
		GLenum target;

	public:
		void load2D(const char* textureFile, GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels);
		void loadCubemap(const char *textureFiles[], GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamZ, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels);
		void loadSkybox(const std::string FOLDER_NAME, GLenum target, GLint textureParamX, GLint textureParamY, GLint textureParamZ, GLint textureParamMin, GLint textureParamMag, GLenum colorFormat, GLenum totalChannels);
		void setUniform(Shader* shader, unsigned int location, int textureNum);
		void activate(GLenum textureNum);
	};
}