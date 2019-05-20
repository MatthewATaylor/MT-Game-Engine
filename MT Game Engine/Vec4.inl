#pragma once

namespace mtge {
	//Constructor
	template<typename T>
	Vec4<T>::Vec4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	template<typename T>
	Vec4<T>::Vec4(T x, T y, T z, T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//Public
	template<typename T>
	Vec4<T> &Vec4<T>::operator=(const Vec4<T> &otherVec) {
		x = otherVec.x;
		y = otherVec.y;
		z = otherVec.z;
		w = otherVec.w;
		return *this;
	}
	template<typename T>
	Vec4<T> &Vec4<T>::operator+=(const Vec4<T> &otherVec) {
		x += otherVec.x;
		y += otherVec.y;
		z += otherVec.z;
		w += otherVec.w;
		return *this;
	}
	template<typename T>
	Vec4<T> &Vec4<T>::operator-=(const Vec4<T> &otherVec) {
		x -= otherVec.x;
		y -= otherVec.y;
		z -= otherVec.z;
		w -= otherVec.w;
		return *this;
	}
	template<typename T>
	Vec4<T> &Vec4<T>::operator*=(const Vec4<T> &otherVec) {
		x *= otherVec.x;
		y *= otherVec.y;
		z *= otherVec.z;
		w *= otherVec.w;
		return *this;
	}
	template<typename T>
	Vec4<T> &Vec4<T>::operator/=(const Vec4<T> &otherVec) {
		x /= otherVec.x;
		y /= otherVec.y;
		z /= otherVec.z;
		w /= otherVec.w;
		return *this;
	}

	template<typename T>
	Vec4<T> Vec4<T>::operator+(const Vec4<T> &otherVec) const {
		Vec4<T> vectorResult = *this;
		return vectorResult += otherVec;
	}
	template<typename T>
	Vec4<T> Vec4<T>::operator-(const Vec4<T> &otherVec) const {
		Vec4<T> vectorResult = *this;
		return vectorResult -= otherVec;
	}
	template<typename T>
	Vec4<T> Vec4<T>::operator*(const Vec4<T> &otherVec) const {
		Vec4<T> vectorResult = *this;
		return vectorResult *= otherVec;
	}
	template<typename T>
	Vec4<T> Vec4<T>::operator/(const Vec4<T> &otherVec) const {
		Vec4<T> vectorResult = *this;
		return vectorResult /= otherVec;
	}

	template<typename T>
	bool Vec4<T>::operator==(const Vec4<T> &otherVec) const {
		return (x == otherVec.x) && (y == otherVec.y) && (z == otherVec.z) && (w == otherVec.w);
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec4<T> &vec) {
		outputStream << "<" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ">";
		return outputStream;
	}

	template<typename T>
	T Vec4<T>::magSquared() const {
		return x * x + y * y + z * z;
	}
	template<typename T>
	T Vec4<T>::mag() const {
		return sqrt(magSquared());
	}
}