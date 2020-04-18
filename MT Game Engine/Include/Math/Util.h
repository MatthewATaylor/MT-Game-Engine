#pragma once

#include <cmath>

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
			static T toRadians(T degrees);

			template<typename T>
			static T toDegrees(T radians);

			struct MatGen {
				template<typename T, unsigned int SIZE>
				static Mat<T, SIZE, SIZE> identity();

				template<typename T, unsigned int SIZE>
				static Mat<T, SIZE, SIZE> scale(Vec<T, SIZE - 1> scaleValues);

				template<typename T, unsigned int SIZE>
				static Mat<T, SIZE, SIZE> translation(Vec<T, SIZE - 1> translationValues);

				template<typename T, unsigned int SIZE>
				static Mat<T, SIZE, SIZE> rotation(Vec<T, SIZE - 1> rotationValues);

				template<typename T>
				static Mat<T, 4, 4> lookAt(Vec<T, 3> cameraPosition, Vec<T, 3> cameraForward, Vec<T, 3> cameraUp);

				template<typename T>
				static Mat<T, 4, 4> perspective(T fovYRadians, T screenWidth, T screenHeight, T near, T far);
			};
		};

		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Util::normalized(Vec<T, SIZE> vecToNormalize) {
			T magnitude = vecToNormalize.mag();
			return vecToNormalize / magnitude;
		}

		template<typename T>
		T Util::toRadians(T degrees) {
			return (degrees / 180) * PI;
		}

		template<typename T>
		T Util::toDegrees(T radians) {
			return (radians / PI) * 180;
		}

		template<typename T, unsigned int SIZE>
		Mat<T, SIZE, SIZE> Util::MatGen::identity() {
			Mat<T, SIZE, SIZE> outputMatrix;
			for (unsigned int i = 1; i <= SIZE; i++) {
				outputMatrix.set(i, i, 1);
			}
			return outputMatrix;
		}

		template<typename T, unsigned int SIZE>
		Mat<T, SIZE, SIZE> Util::MatGen::scale(Vec<T, SIZE - 1> scaleValues) {
			Mat<T, SIZE, SIZE> outputMatrix;
			for (unsigned int i = 1; i <= SIZE - 1; i++) {
				outputMatrix.set(i, i, scaleValues.get(i - 1));
			}
			outputMatrix.set(SIZE, SIZE, 1);
			return outputMatrix;
		}

		template<typename T, unsigned int SIZE>
		Mat<T, SIZE, SIZE> Util::MatGen::translation(Vec<T, SIZE - 1> translationValues) {
			Mat<T, SIZE, SIZE> outputMatrix = identity<T, SIZE>();
			for (unsigned int i = 1; i < SIZE - 1; i++) {
				outputMatrix.set(SIZE, i, translationValues.get(i - 1));
			}
			return outputMatrix;
		}

		template<typename T, unsigned int SIZE>
		Mat<T, SIZE, SIZE> Util::MatGen::rotation(Vec<T, SIZE - 1> rotationValues) {
			return identity<T, SIZE>;
		}

		template<typename T>
		Mat<T, 4, 4> Util::MatGen::lookAt(Vec<T, 3> cameraPosition, Vec<T, 3> cameraForward, Vec<T, 3> cameraUp) {
			/*
			Perform 2 transformations:
				1.) Change basis vectors to camera coordinates
				2.) Translate points according to camera position

				Because we are going from coordinates in one coordinate space to the view space using the camera axes,
				the final transformation is equal to the inverse of the product of the two matrices.

			Below is the product of the above two transformation matrices
			*/
			Vec<T, 3> forward = normalized(cameraPosition - cameraForward);
			Vec<T, 3> right = normalized(cameraUp.cross(forward));
			Vec<T, 3> up = forward.cross(right);

			Mat<T, 4, 4> outputMatrix;

			outputMatrix.set(1, 1, right.getX());
			outputMatrix.set(2, 1, right.getY());
			outputMatrix.set(3, 1, right.getZ());

			outputMatrix.set(1, 2, up.getX());
			outputMatrix.set(2, 2, up.getY());
			outputMatrix.set(3, 2, up.getZ());

			outputMatrix.set(1, 3, forward.getX());
			outputMatrix.set(2, 3, forward.getY());
			outputMatrix.set(3, 3, forward.getZ());

			outputMatrix.set(4, 1, right.dot(cameraPosition) * -1);
			outputMatrix.set(4, 2, up.dot(cameraPosition) * -1);
			outputMatrix.set(4, 3, forward.dot(cameraPosition) * -1);
			outputMatrix.set(4, 4, 1);

			return outputMatrix;
		}

		template<typename T>
		Mat<T, 4, 4> Util::MatGen::perspective(T fovYRadians, T screenWidth, T screenHeight, T near, T far) {
			T aspectRatio = screenWidth / screenHeight;
			T topOverNear = tan(fovYRadians / 2);
			T top = topOverNear * near;
			T bottom = -top;
			T right = top * aspectRatio;
			T left = -right;

			Mat<T, 4, 4> outputMatrix;
			outputMatrix.set(1, 1, 1 / (aspectRatio * topOverNear));
			outputMatrix.set(2, 2, 1 / topOverNear);
			outputMatrix.set(3, 3, -(far + near) / (far - near));
			outputMatrix.set(3, 4, -1);
			outputMatrix.set(4, 3, -2 * far * near / (far - near));

			return outputMatrix;
		}
	}
}