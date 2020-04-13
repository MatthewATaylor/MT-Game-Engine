#pragma once

namespace mtge {
	namespace math {
		//Constructor
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE>::Vec() {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] = 0;
			}
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE>::Vec(T elements[SIZE]) {
			for (unsigned int i = 0; i < SIZE; i++) {
				this->elements[i] = elements[i];
			}
		}

		//Public
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator=(const Vec<T, SIZE> &otherVec) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] = otherVec.elements[i];
			}
			return *this;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator+=(const Vec<T, SIZE> &otherVec) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] += otherVec.elements[i];
			}
			return *this;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator-=(const Vec<T, SIZE> &otherVec) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] -= otherVec.elements[i];
			}
			return *this;
		}

		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator+=(const T addend) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] += addend;
			}
			return *this;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator-=(const T addend) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] -= addend;
			}
			return *this;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator*=(const T addend) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] *= addend;
			}
			return *this;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> &Vec<T, SIZE>::operator/=(const T addend) {
			for (unsigned int i = 0; i < SIZE; i++) {
				elements[i] /= addend;
			}
			return *this;
		}

		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator+(const Vec<T, SIZE> &otherVec) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult += otherVec;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator-(const Vec<T, SIZE> &otherVec) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult -= otherVec;
		}

		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator+(const T addend) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult += addend;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator-(const T addend) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult -= addend;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator*(const T addend) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult *= addend;
		}
		template<typename T, unsigned int SIZE>
		Vec<T, SIZE> Vec<T, SIZE>::operator/(const T addend) const {
			Vec<T, SIZE> vectorResult = *this;
			return vectorResult /= addend;
		}

		template<typename T, unsigned int SIZE>
		bool Vec<T, SIZE>::operator==(const Vec<T, SIZE> &otherVec) const {
			for (unsigned int i = 0; i < SIZE; i++) {
				if (elements[i] != otherVec.elements[i]) {
					return false;
				}
			}
			return true;
		}

		template<typename T, unsigned int SIZE>
		std::ostream &operator<<(std::ostream &outputStream, const Vec<T, SIZE> &vec) {
			outputStream << "<";
			for (unsigned int i = 0; i < SIZE; i++) {
				outputStream << vec.elements[i];
				if (i < SIZE - 1) {
					outputStream << ", ";
				}
			}
			outputStream << ">";
			return outputStream;
		}

		template<typename T, unsigned int SIZE>
		T Vec<T, SIZE>::dot(const Vec<T, SIZE> &otherVec) const {
			T result = 0;
			for (unsigned int i = 0; i < SIZE; i++) {
				result += elements[i] * otherVec.elements[i];
			}
			return result;
		}
		template<typename T, unsigned int SIZE>
		T Vec<T, SIZE>::magSquared() const {
			T result = 0;
			for (unsigned int i = 0; i < SIZE; i++) {
				result += elements[i] * elements[i];
			}
			return result;
		}
		template<typename T, unsigned int SIZE>
		T Vec<T, SIZE>::mag() const {
			return sqrt(magSquared());
		}

		template<typename T, unsigned int SIZE>
		T Vec<T, SIZE>::get(unsigned int index) const {
			return elements[index];
		}
		template<typename T, unsigned int SIZE>
		void Vec<T, SIZE>::set(unsigned int index, T newElement) {
			elements[index] = newElement;
		}
	}
}