#pragma once

#include <cmath>

#include "Vec.h"
#include "Mat.h"

namespace mtge {
	namespace math {
		class Util {
		public:
			static const float PI;

			template<unsigned int SIZE>
			void genPerlinNoise2D(unsigned int numOctaves, float scaleBias, float seed[SIZE][SIZE], float output[SIZE][SIZE]);

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
	}
}

#include "../../Source/Math/Util.inl"