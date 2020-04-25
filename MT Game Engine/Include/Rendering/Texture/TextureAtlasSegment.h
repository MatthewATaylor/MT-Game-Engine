#pragma once

#include "Math/Vec.h"

namespace mtge {
	class TextureAtlasSegment {
	private:
		const math::Vec2 SAMPLE_BUFFER;
		const math::Vec2 OFFSET;
		const math::Vec2 SIZE;

	public:
		const math::Vec2 TOP_LEFT;
		const math::Vec2 TOP_RIGHT;
		const math::Vec2 BOTTOM_LEFT;
		const math::Vec2 BOTTOM_RIGHT;

		TextureAtlasSegment(const math::Vec<unsigned int, 2> ORIGIN_INDEX, const math::Vec<unsigned int, 2> ATLAS_DIMENS);
	};
}