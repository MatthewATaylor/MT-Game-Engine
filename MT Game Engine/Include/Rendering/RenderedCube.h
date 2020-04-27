#pragma once

#include <vector>

#include "Cube.h"
#include "Math/Vec.h"
#include "Renderable.h"
#include "Texture/CubeTexture.h"
#include "ChunkData.h"
#include "Texture/Texture.h"
#include "Shader.h"
#include "CubeCharacterizer.h"
#include "Math/Mat.h"

namespace mtge {
	class RenderedCube : public Cube, public Renderable {
	private:
		int numVertices = 0;
		math::Vec3 position;
		math::Vec3 dimensions;
		math::Mat4 modelMatrix;

	public:
		RenderedCube(CubeTexture *texture, math::Vec3 position, math::Vec3 dimensions);
		void render(Camera *camera, Window *window) override;
	};
}