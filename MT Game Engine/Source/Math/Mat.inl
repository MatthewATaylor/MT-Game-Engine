#pragma once

namespace mtge {
	namespace math {
		//Constructor
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS>::Mat() {
			forAllElementsMutable([&](int row, int col) -> void {
				elements[row][col] = 0;
			});
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS>::Mat(T elements[ROWS][COLS]) {
			forAllElementsMutable([&](int row, int col) -> void {
				this->elements[row][col] = elements[row][col];
			});
		}

		//Private
		template<typename T, unsigned int ROWS, unsigned int COLS>
		template<typename LambdaType>
		void Mat<T, ROWS, COLS>::forAllElements(LambdaType lambda) const {
			for (unsigned int i = 0; i < ROWS; i++) {
				for (unsigned int j = 0; j < COLS; j++) {
					lambda(i, j);
				}
			}
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		template<typename LambdaType>
		void Mat<T, ROWS, COLS>::forAllElementsMutable(LambdaType lambda) {
			for (unsigned int i = 0; i < ROWS; i++) {
				for (unsigned int j = 0; j < COLS; j++) {
					lambda(i, j);
				}
			}
		}

		//Public
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS> &Mat<T, ROWS, COLS>::operator=(const Mat<T, ROWS, COLS> &otherMat) {
			forAllElementsMutable([&](int row, int col) -> void {
				elements[row][col] = otherMat.elements[row][col];
			});
			return *this;
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS> &Mat<T, ROWS, COLS>::operator+=(const Mat<T, ROWS, COLS> &otherMat) {
			forAllElementsMutable([&](int row, int col) -> void {
				elements[row][col] += otherMat.elements[row][col];
			});
			return *this;
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS> &Mat<T, ROWS, COLS>::operator-=(const Mat<T, ROWS, COLS> &otherMat) {
			forAllElementsMutable([&](int row, int col) -> void {
				elements[row][col] -= otherMat.elements[row][col];
			});
			return *this;
		}

		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS> Mat<T, ROWS, COLS>::operator+(const Mat<T, ROWS, COLS> &otherMat) const {
			Mat<T, ROWS, COLS> newMat = *this;
			return newMat += otherMat;
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, ROWS, COLS> Mat<T, ROWS, COLS>::operator-(const Mat<T, ROWS, COLS> &otherMat) const {
			Mat<T, ROWS, COLS> newMat = *this;
			return newMat -= otherMat;
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		template<unsigned int OTHER_COLS>
		Mat<T, ROWS, OTHER_COLS> Mat<T, ROWS, COLS>::operator*(const Mat<T, COLS, OTHER_COLS> &otherMat) const {
			Mat<T, ROWS, OTHER_COLS> newMat;
			for (unsigned int i = 0; i < ROWS; i++) {
				for (unsigned int j = 0; j < OTHER_COLS; j++) {
					T newElement = 0;
					for (unsigned int k = 0; k < COLS; k++) {
						newElement += elements[i][k] * otherMat.elements[k][j];
					}
					newMat.elements[i][j] = newElement;
				}
			}
			return newMat;
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		Vec<T, ROWS> Mat<T, ROWS, COLS>::operator*(Vec<T, COLS> &vec) const {
			Vec<T, ROWS> newVec;
			for (unsigned int i = 0; i < ROWS; i++) {
				T newElement = 0;
				for (unsigned int j = 0; j < COLS; j++) {
					newElement += elements[i][j] * vec.get(j);
				}
				newVec.set(i, newElement);
			}
			return newVec;
		}

		template<typename T, unsigned int ROWS, unsigned int COLS>
		bool Mat<T, ROWS, COLS>::operator==(const Mat<T, ROWS, COLS> &otherMat) const {
			for (unsigned int i = 0; i < ROWS; i++) {
				for (unsigned int j = 0; j < COLS; j++) {
					if (elements[i][j] != otherMat.elements[i][j]) {
						return false;
					}
				}
			}
			return true;
		}

		template<typename T, unsigned int ROWS, unsigned int COLS>
		std::ostream &operator<<(std::ostream &outputStream, const Mat<T, ROWS, COLS> &mat) {
			outputStream << "[";
			for (unsigned int i = 1; i <= ROWS; i++) {
				for (unsigned int j = 1; j <= COLS; j++) {
					outputStream << mat.get(i, j);
					if (j < COLS) {
						outputStream << "  ";
					}
				}
				if (i < ROWS) {
					outputStream << std::endl << " ";
				}
			}
			outputStream << "]";
			return outputStream;
		}

		template <typename T, unsigned int ROWS, unsigned int COLS>
		T Mat<T, ROWS, COLS>::get(unsigned int row, unsigned int col) const {
			return elements[row - 1][col - 1];
		}
		template <typename T, unsigned int ROWS, unsigned int COLS>
		T *Mat<T, ROWS, COLS>::getPtr() {
			return &(elements[0][0]);
		}
		template<typename T, unsigned int ROWS, unsigned int COLS>
		void Mat<T, ROWS, COLS>::set(unsigned int row, unsigned int col, T newElement) {
			elements[row - 1][col - 1] = newElement;
		}

		template<typename T, unsigned int ROWS, unsigned int COLS>
		Mat<T, COLS, ROWS> Mat<T, ROWS, COLS>::altMajorOrder() const {
			T newElements[COLS][ROWS];
			for (unsigned int i = 0; i < ROWS; i++) {
				for (unsigned int j = 0; j < COLS; j++) {
					newElements[j][i] = elements[i][j];
				}
			}
			Mat<T, COLS, ROWS> newMat(newElements);
			return newMat;
		}
	}
}