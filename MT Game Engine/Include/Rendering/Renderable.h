#pragma once

#include "GL/glew.h"

#include "CubeData.h"
#include "Interaction/Camera.h"
#include "Window.h"

namespace mtge {
	class Renderable {
	protected:
		unsigned int vertexArrayID;
		unsigned int vertexBufferID;

		Renderable();

	public:
		virtual void render(Camera *camera, Window *window) = 0;
		~Renderable();
	};
}