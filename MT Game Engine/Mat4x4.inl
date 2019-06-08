#pragma once

namespace mtge {
	//Constructor
	template<typename T>
	Mat4x4<T>::Mat4x4() {
		forAllElementsMutable([&](int row, int col) -> void {
			elements[row][col] = 0;
		});
	}
	template<typename T>
	Mat4x4<T>::Mat4x4(T elements[SIZE][SIZE]) {
		forAllElementsMutable([&](int row, int col) -> void {
			this->elements[row][col] = elements[row][col];
		});
	}

	//Private
	template<typename T>
	template<typename LambdaType>
	void Mat4x4<T>::forAllElements(LambdaType lambda) const{
		for (unsigned int i = 0; i < SIZE; i++) {
			for (unsigned int j = 0; j < SIZE; j++) {
				lambda(i, j);
			}
		}
	}
	template<typename T>
	template<typename LambdaType>
	void Mat4x4<T>::forAllElementsMutable(LambdaType lambda) {
		for (unsigned int i = 0; i < SIZE; i++) {
			for (unsigned int j = 0; j < SIZE; j++) {
				lambda(i, j);
			}
		}
	}

	//Public
	template<typename T>
	Mat4x4<T> &Mat4x4<T>::operator=(const Mat4x4<T> &otherMat) {
		forAllElementsMutable([&](int row, int col) -> void {
			elements[row][col] = otherMat.elements[row][col];
		});
		return *this;
	}
	template<typename T>
	Mat4x4<T> &Mat4x4<T>::operator+=(const Mat4x4<T> &otherMat) {
		forAllElementsMutable([&](int row, int col) -> void {
			elements[row][col] += otherMat.elements[row][col];
		});
		return *this;
	}
	template<typename T>
	Mat4x4<T> &Mat4x4<T>::operator-=(const Mat4x4<T> &otherMat) {
		forAllElementsMutable([&](int row, int col) -> void {
			elements[row][col] -= otherMat.elements[row][col];
		});
		return *this;
	}
	template<typename T>
	Mat4x4<T> &Mat4x4<T>::operator*=(const Mat4x4<T> &otherMat) {
		forAllElementsMutable([&](int row, int col) -> void {
			T newElement = 0;
			for (unsigned int i = 0; i < SIZE; i++) {
				newElement += elements[row][i] * otherMat.elements[i][col];
			}
			elements[row][col] = newElement;
		});
		return *this;
	}

	template<typename T>
	Mat4x4<T> Mat4x4<T>::operator+(const Mat4x4<T> &otherMat) const {
		Mat4x4<T> newMat = *this;
		return newMat += otherMat;
	}
	template<typename T>
	Mat4x4<T> Mat4x4<T>::operator-(const Mat4x4<T> &otherMat) const {
		Mat4x4<T> newMat = *this;
		return newMat -= otherMat;
	}
	template<typename T>
	Mat4x4<T> Mat4x4<T>::operator*(const Mat4x4<T> &otherMat) const {
		Mat4x4<T> newMat = *this;
		return newMat *= otherMat;
	}
	template<typename T>
	Vec4<T> Mat4x4<T>::operator*(Vec4<T> &vec) const {
		T vecElements[SIZE] = { vec.x, vec.y, vec.z, vec.w };
		T newVecElements[SIZE];

		forAllElements([&](int row, int col) -> void {
			newVecElements[row] += elements[row][col] * vecElements[col];
		});

		Vec4<T> newVec(newVecElements[0], newVecElements[1], newVecElements[2], newVecElements[3]);
		return newVec;
	}

	template<typename T>
	bool Mat4x4<T>::operator==(const Mat4x4<T> &otherMat) const {
		for (unsigned int i = 0; i < SIZE; i++) {
			for (unsigned int j = 0; j < SIZE; j++) {
				if (elements[i][j] != otherMat.elements[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Mat4x4<T> &mat) {
		outputStream << "[";
		for (unsigned int i = 1; i <= Mat4x4<T>::SIZE; i++) {
			for (unsigned int j = 1; j <= Mat4x4<T>::SIZE; j++) {
				outputStream << mat.get(i, j);
				if (j < Mat4x4<T>::SIZE) {
					outputStream << "  ";
				}
			}
			if (i < Mat4x4<T>::SIZE) {
				outputStream << std::endl << " ";
			}
		}
		outputStream << "]";
		return outputStream;
	}

	template <typename T>
	T Mat4x4<T>::get(unsigned int row, unsigned int col) const {
		return elements[row - 1][col - 1];
	}
	template<typename T>
	void Mat4x4<T>::set(unsigned int row, unsigned int col, T newElement) {
		elements[row - 1][col - 1] = newElement;
	}
}