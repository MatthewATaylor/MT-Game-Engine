#include "Rendering/Frustum.h"

namespace mtge {
	//Constructor
	Frustum::Frustum(math::Vec2 front, float angle_rad) {
		float frontAngle = atan2f(front.getY(), front.getX());
		float leftAngle = frontAngle + angle_rad;
		float rightAngle = frontAngle - angle_rad;

		leftVec = math::Vec2(cosf(leftAngle), sinf(leftAngle));
		leftNormal = math::Vec2(leftVec.getY(), -leftVec.getX());

		rightVec = math::Vec2(cosf(rightAngle), sinf(rightAngle));
		rightNormal = math::Vec2(-rightVec.getY(), rightVec.getX());
	}

	//Public
	bool Frustum::pointIsInFrustum(math::Vec2 point) {
		return point.dot(leftNormal) >= 0.0f && point.dot(rightNormal) >= 0.0f;
	}
}