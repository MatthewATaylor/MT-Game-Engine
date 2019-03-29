#pragma once

namespace mtge {
	//Constructor
	template<typename T>
	Vec3<T>::Vec3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	template<typename T>
	Vec3<T>::Vec3(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//Public
	template<typename T>
	Vec3<T> &Vec3<T>::operator=(const Vec3<T> &otherVec) {
		x = otherVec.x;
		y = otherVec.y;
		z = otherVec.z;
		return *this;
	}
	template<typename T>
	Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &otherVec) {
		x += otherVec.x;
		y += otherVec.y;
		z += otherVec.z;
		return *this;
	}
	template<typename T>
	Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &otherVec) {
		x -= otherVec.x;
		y -= otherVec.y;
		z -= otherVec.z;
		return *this;
	}
	template<typename T>
	Vec3<T> &Vec3<T>::operator*=(const Vec3<T> &otherVec) {
		x *= otherVec.x;
		y *= otherVec.y;
		z *= otherVec.z;
		return *this;
	}
	template<typename T>
	Vec3<T> &Vec3<T>::operator/=(const Vec3<T> &otherVec) {
		x /= otherVec.x;
		y /= otherVec.y;
		z /= otherVec.z;
		return *this;
	}

	template<typename T>
	Vec3<T> Vec3<T>::operator+(const Vec3<T> &otherVec) const {
		Vec3<T> vectorResult = *this;
		return vectorResult += otherVec;
	}
	template<typename T>
	Vec3<T> Vec3<T>::operator-(const Vec3<T> &otherVec) const {
		Vec3<T> vectorResult = *this;
		return vectorResult -= otherVec;
	}
	template<typename T>
	Vec3<T> Vec3<T>::operator*(const Vec3<T> &otherVec) const {
		Vec3<T> vectorResult = *this;
		return vectorResult *= otherVec;
	}
	template<typename T>
	Vec3<T> Vec3<T>::operator/(const Vec3<T> &otherVec) const {
		Vec3<T> vectorResult = *this;
		return vectorResult /= otherVec;
	}

	template<typename T>
	bool Vec3<T>::operator==(const Vec3<T> &otherVec) const {
		return (x == otherVec.x) && (y == otherVec.y) && (z == otherVec.z);
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec3<T> &vec) {
		outputStream << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
		return outputStream;
	}

	template<typename T>
	T Vec3<T>::dot(const Vec3<T> &otherVec) const {
		return x * otherVec.x + y * otherVec.y + z * otherVec.z;
	}
	template<typename T>
	T Vec3<T>::magSquared() const {
		return x * x + y * y + z * z;
	}
	template<typename T>
	T Vec3<T>::mag() const {
		return sqrt(magSquared());
	}
}