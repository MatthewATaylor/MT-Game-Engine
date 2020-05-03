#pragma once

#include <cmath>

#include "Math/Vec.h"

namespace mtge {
	class Frustum {
	private:
		math::Vec2 leftVec;
		math::Vec2 leftNormal;

		math::Vec2 rightVec;
		math::Vec2 rightNormal;

	public:
		Frustum(math::Vec2 front, float angle_rad);
		bool pointIsInFrustum(math::Vec2 point);
	};
}