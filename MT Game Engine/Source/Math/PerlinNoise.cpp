#include "Math/PerlinNoise.h"

namespace mtge {
	namespace math {
		//Private
		const unsigned int PerlinNoise::permutation[512] = {
			151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
			8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
			35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
			134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
			55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18,
			169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
			124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189,
			28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
			129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
			251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
			49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
			138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180,
			151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
			8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117,
			35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71,
			134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41,
			55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18,
			169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250,
			124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189,
			28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
			129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
			251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
			49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
			138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
		};

		float PerlinNoise::fade(float x) {
			return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
		}
		int PerlinNoise::incrementAndWrap(int num, int sizeToWrap) {
			num++;
			if (sizeToWrap > 0) {
				num %= sizeToWrap;
			}
			return num;
		}
		float PerlinNoise::gradientDotVec(int hash, float vecX, float vecY) {
			switch (hash & 3) {
			case 0:
				return vecX + vecY;
			case 1:
				return -vecX + vecY;
			case 2:
				return vecX - vecY;
			case 3:
				return -vecX - vecY;
			default:
				return 0.0f;
			}
		}
		float PerlinNoise::lerp(float value1, float value2, float fraction) {
			return value1 + fraction * (value2 - value1);
		}

		//Public
		float PerlinNoise::get2D(float x, float y, float frequency, int sizeToWrap) {
			x *= frequency;
			y *= frequency;
			
			int squareX = (int)std::floor(x) & 255;
			int squareY = (int)std::floor(y) & 255;

			float pointInSquareX = x - (int)std::floor(x);
			float pointInSquareY = y - (int)std::floor(y);

			float pointInSquareFadeX = fade(pointInSquareX);
			float pointInSquareFadeY = fade(pointInSquareY);

			int hash1 = permutation[(int)permutation[squareX] + squareY];
			int hash2 = permutation[(int)permutation[incrementAndWrap(squareX, sizeToWrap)] + squareY];
			int hash3 = permutation[(int)permutation[squareX] + incrementAndWrap(squareY, sizeToWrap)];
			int hash4 = permutation[(int)permutation[incrementAndWrap(squareX, sizeToWrap)] + incrementAndWrap(squareY, sizeToWrap)];

			float dot1 = gradientDotVec(hash1, pointInSquareX, pointInSquareY);
			float dot2 = gradientDotVec(hash2, pointInSquareX - 1, pointInSquareY);
			float dot3 = gradientDotVec(hash3, pointInSquareX, pointInSquareY - 1);
			float dot4 = gradientDotVec(hash4, pointInSquareX - 1, pointInSquareY - 1);

			float bottomLerpX = lerp(dot1, dot2, pointInSquareFadeX);
			float  topLerpX = lerp(dot3, dot4, pointInSquareFadeX);
			float lerpY = lerp(bottomLerpX, topLerpX, pointInSquareFadeY);

			return (lerpY + 1.0f) / 2.0f;
		}
		float PerlinNoise::get2DWithOctaves(float x, float y, float startFrequency, float persistence, unsigned int numOctaves, int sizeToWrap) {
			float total = 0.0f;
			float maxValue = 0.0f;
			float frequency = startFrequency;
			float amplitude = 1.0f;

			for (unsigned int i = 0; i < numOctaves; i++) {
				total += get2D(x, y, frequency, sizeToWrap) * amplitude;
				maxValue += amplitude;
				frequency /= 2.0f;
				amplitude *= persistence;
			}

			return total / maxValue;
		}
	}
}