#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <stb_image.h>

#include "Rendering/Shader.h"

namespace mtge {
	enum class TextureWrapSetting {
		REPEAT, REPEAT_MIRRORED, EDGE_CLAMP, BORDER_CLAMP, 
	};
	enum class TextureFilterSetting {
		NEAREST, LINEAR
	};
	enum class TextureColorSetting {
		RGB, RGBA
	};

	class Texture {
	private:
		struct TextureSettings_GL_2D {
			GLint textureWrapX;
			GLint textureWrapY;
			GLint textureFilterMin;
			GLint textureFilterMag;
			GLint colorFormat;
		} textureSettings_GL_2D;
		struct TextureSettings_GL_3D {
			GLint textureWrapX;
			GLint textureWrapY;
			GLint textureWrapZ;
			GLint textureFilterMin;
			GLint textureFilterMag;
			GLint colorFormat;
		} textureSettings_GL_3D;

		unsigned int textureID;
		GLenum target;

		void setTextureWrap_GL(TextureWrapSetting textureWrap, GLint &textureWrap_GL);
		void setTextureFilter_GL(TextureFilterSetting textureFilter, GLint &textureFilter_GL);
		void setColorFormat_GL(TextureColorSetting colorFormat, GLint &colorFormat_GL);
		void setTextureSettings_GL_2D(TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);
		void setTextureSettings_GL_3D(TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);

	public:
		void load2D(const char* textureFile, TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);
		void loadCubemap(const char *textureFiles[], TextureWrapSetting textureWrapX, TextureWrapSetting textureWrapY, TextureWrapSetting textureWrapZ, TextureFilterSetting textureFilterMin, TextureFilterSetting textureFilterMag, TextureColorSetting colorFormat);
		void setUniform(Shader* shader, unsigned int location, int textureNum);
		void activate(GLenum textureNum);
	};
}