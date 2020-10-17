#pragma once

#include <ostream>

#include "Vec.h"

namespace mtge {
	namespace math {
		template<typename T, unsigned int ROWS, unsigned int COLS>
		class Mat;

		template<typename T, unsigned int ROWS, unsigned int COLS>
		std::ostream &operator<<(std::ostream &outputStream, const Mat<T, ROWS, COLS> &mat);

		template<typename T, unsigned int ROWS, unsigned int COLS>
		class Mat {
		private:
			template<typename LambdaType>
			void forAllElements(LambdaType lambda) const;

			template<typename LambdaType>
			void forAllElementsMutable(LambdaType lambda);

		public:
			T elements[ROWS][COLS];

			Mat();
			Mat(T elements[ROWS][COLS]);

			Mat<T, ROWS, COLS> &operator=(const Mat<T, ROWS, COLS> &otherMat);
			Mat<T, ROWS, COLS> &operator+=(const Mat<T, ROWS, COLS> &otherMat);
			Mat<T, ROWS, COLS> &operator-=(const Mat<T, ROWS, COLS> &otherMat);

			Mat<T, ROWS, COLS> operator+(const Mat<T, ROWS, COLS> &otherMat) const;
			Mat<T, ROWS, COLS> operator-(const Mat<T, ROWS, COLS> &otherMat) const;
			template<unsigned int OTHER_COLS>
			Mat<T, ROWS, OTHER_COLS> operator*(const Mat<T, COLS, OTHER_COLS> &otherMat) const;
			Vec<T, ROWS> operator*(Vec<T, COLS> &vec) const;

			bool operator==(const Mat<T, ROWS, COLS> &otherMat) const;

			friend std::ostream &operator<<<T, ROWS, COLS>(std::ostream &outputStream, const Mat<T, ROWS, COLS> &mat);

			T get(unsigned int row, unsigned int col) const;
			T *getPtr();
			void set(unsigned int row, unsigned int col, T newElement);

			Mat<T, COLS, ROWS> transpose() const;
		};

		typedef Mat<float, 2, 2> Mat2;
		typedef Mat<float, 3, 3> Mat3;
		typedef Mat<float, 4, 4> Mat4;
	}
}

#include "../../Source/Math/Mat.inl"