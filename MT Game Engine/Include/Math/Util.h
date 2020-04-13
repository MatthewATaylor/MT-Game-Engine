#pragma once

#include "Vec.h"
#include "Mat.h"

namespace mtge {
	namespace math {
		class Util {
		public:
			static const float PI;

			template<typename T, unsigned int SIZE>
			static Vec<T, SIZE> normalized(Vec<T, SIZE> vecToNormalize);

			template<typename T>
			static Mat<T, 4, 4> lookAt(Vec<T, 3> cameraPosition, Vec<T, 3> cameraForward, Vec<T, 3> cameraUp);

			template<typename T>
			static T toRadians(T degrees);
			template<typename T>
			static T toDegrees(T radians);
		};

		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Util::normalized(Vec<T, SIZE> vecToNormalize) {
			T magnitude = vecToNormalize.mag();
			return vecToNormalize / magnitude;
		}

		template<typename T>
		Mat<T, 4, 4> Util::lookAt(Vec<T, 3> cameraPosition, Vec<T, 3> cameraForward, Vec<T, 3> cameraUp) {
			Vec<T, 3> forward = normalized(cameraPosition - cameraForward);
			Vec<T, 3> right = cameraUp.cross(forward);
			Vec<T, 3> up = forward.cross(right);

			Mat<T, 4, 4> outputMatrix;

			outputMatrix.set(1, 1, right.getX());
			outputMatrix.set(1, 2, right.getY());
			outputMatrix.set(1, 3, right.getZ());
			outputMatrix.set(1, 4, 1);

			outputMatrix.set(2, 1, up.getX());
			outputMatrix.set(2, 2, up.getY());
			outputMatrix.set(2, 3, up.getZ());
			outputMatrix.set(2, 4, 1);

			outputMatrix.set(3, 1, forward.getX());
			outputMatrix.set(3, 2, forward.getY());
			outputMatrix.set(3, 3, forward.getZ());
			outputMatrix.set(3, 4, 1);

			/*
			outputMatrix.set(4, 1, cameraPosition.getX());
			outputMatrix.set(4, 2, cameraPosition.getY());
			outputMatrix.set(4, 3, cameraPosition.getZ());
			*/
			outputMatrix.set(4, 1, right.dot(cameraPosition) * -1);
			outputMatrix.set(4, 2, up.dot(cameraPosition) * -1);
			outputMatrix.set(4, 3, forward.dot(cameraPosition) * -1);
			outputMatrix.set(4, 4, 1);

			return outputMatrix;
		}

		template<typename T>
		T Util::toRadians(T degrees) {
			return (degrees / 180) * PI;
		}
		template<typename T>
		T Util::toDegrees(T radians) {
			return (radians / PI) * 180;
		}
	}
}