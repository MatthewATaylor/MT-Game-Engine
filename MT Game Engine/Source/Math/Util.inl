#pragma once

namespace mtge {
	namespace math {
		template<unsigned int SIZE>
		void Util::genPerlinNoise2D(unsigned int numOctaves, float scaleBias, float seed[SIZE][SIZE], float output[SIZE][SIZE]) {
			const unsigned int MAX_NUM_OCTAVES = (int)(log(SIZE) / log(2));
			if (numOctaves > MAX_NUM_OCTAVES) {
				std::cout << "WARNING [FUNCTION: genPerlinNoise2D]: OCTAVE COUNT TOO HIGH, REDUCED TO " << MAX_NUM_OCTAVES << std::endl;
				numOctaves = MAX_NUM_OCTAVES;
			}

			for (unsigned int xPos = 0; xPos < SIZE; xPos++) {
				for (unsigned int yPos = 0; yPos < SIZE; yPos++) {
					float value = 0.0f;
					float accumulatedScale = 0.0f;
					float scale = 1.0f;
					unsigned int pitch = SIZE;

					for (unsigned int octave = 0; octave < numOctaves; octave++) {
						//Column indices for seed array
						unsigned int sampleX1 = (xPos / pitch) * pitch;
						unsigned int sampleX2 = (sampleX1 + pitch) % SIZE;

						//Row indices for seed array
						unsigned int sampleY1 = (yPos / pitch) * pitch;
						unsigned int sampleY2 = (sampleY1 + pitch) % SIZE;

						//Fraction (0 to 1) of distance between sample 1 and sample 2
						float normalizedXPos = (float)(xPos - sampleX1) / (float)pitch;
						float normalizedYPos = (float)(yPos - sampleY1) / (float)pitch;

						//Linear interpolations across each each row of seeds
						float row1Interpolation = (1.0f - normalizedXPos) * seed[sampleY1][sampleX1] + normalizedXPos * seed[sampleY1][sampleX2];
						float row2Interpolation = (1.0f - normalizedXPos) * seed[sampleY2][sampleX1] + normalizedXPos * seed[sampleY2][sampleX2];

						//Linear interpolation between rows
						float newValue = (1.0f - normalizedYPos) * row1Interpolation + normalizedYPos * row2Interpolation;

						value += newValue * scale;
						accumulatedScale += scale;
						scale /= scaleBias;
						pitch /= 2;
					}

					output[yPos][xPos] = value / accumulatedScale;
				}
			}
		}

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
			for (unsigned int i = 1; i <= SIZE - 1; i++) {
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