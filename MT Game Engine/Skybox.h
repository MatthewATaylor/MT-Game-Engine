#pragma once

#include "Shape.h"
#include "Texture.h"
#include "ResourceManager.h"

namespace mtge {
	class Skybox : public Shape {
	private:
		static const float VERTICES[];
		static const unsigned int VERTICES_SIZE = sizeof(float) * 108;
		Texture *texture;

	public:
		Skybox(Texture *texture);
		void draw();
	};
}