#pragma once

#include <cmath>
#include <iostream>

namespace mtge {
	namespace math {
		class PerlinNoise {
		private:
			static const unsigned int permutation[512];

			static float fade(float x);
			static int incrementAndWrap(int num, int sizeToWrap);
			static float gradientDotVec(int hash, float vecX, float vecY);
			static float lerp(float value1, float value2, float fraction);

		public:
			static float get2D(float x, float y, float frequency, int sizeToWrap = 0);
			static float get2DWithOctaves(float x, float y, float startFrequency, float persistence, unsigned int numOctaves, int sizeToWrap = 0);
		};
	}
}