#pragma once

#include "Shape.h"
#include "Texture/Texture.h"
#include "ResourceManager.h"

namespace mtge {
	class Skybox : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 108;

	public:
		Skybox();
		void draw();
	};
}