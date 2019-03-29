#pragma once

namespace mtge {
	//Constructor
	template<typename T>
	Vec2<T>::Vec2() {
		this->x = 0;
		this->y = 0;
	}
	template<typename T>
	Vec2<T>::Vec2(T x, T y) {
		this->x = x;
		this->y = y;
	}

	//Public
	template<typename T>
	Vec2<T> &Vec2<T>::operator=(const Vec2<T> &otherVec) {
		x = otherVec.x;
		y = otherVec.y;
		return *this;
	}
	template<typename T>
	Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &otherVec) {
		x += otherVec.x;
		y += otherVec.y;
		return *this;
	}
	template<typename T>
	Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &otherVec) {
		x -= otherVec.x;
		y -= otherVec.y;
		return *this;
	}
	template<typename T>
	Vec2<T> &Vec2<T>::operator*=(const Vec2<T> &otherVec) {
		x *= otherVec.x;
		y *= otherVec.y;
		return *this;
	}
	template<typename T>
	Vec2<T> &Vec2<T>::operator/=(const Vec2<T> &otherVec) {
		x /= otherVec.x;
		y /= otherVec.y;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator+(const Vec2<T> &otherVec) const {
		Vec2<T> vectorResult = *this;
		return vectorResult += otherVec;
	}
	template<typename T>
	Vec2<T> Vec2<T>::operator-(const Vec2<T> &otherVec) const {
		Vec2<T> vectorResult = *this;
		return vectorResult -= otherVec;
	}
	template<typename T>
	Vec2<T> Vec2<T>::operator*(const Vec2<T> &otherVec) const {
		Vec2<T> vectorResult = *this;
		return vectorResult *= otherVec;
	}
	template<typename T>
	Vec2<T> Vec2<T>::operator/(const Vec2<T> &otherVec) const {
		Vec2<T> vectorResult = *this;
		return vectorResult /= otherVec;
	}

	template<typename T>
	bool Vec2<T>::operator==(const Vec2<T> &otherVec) const {
		return (x == otherVec.x) && (y == otherVec.y);
	}

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec2<T> &vec) {
		outputStream << "<" << vec.x << ", " << vec.y << ">";
		return outputStream;
	}

	template<typename T>
	T Vec2<T>::dot(const Vec2<T> &otherVec) const {
		return x * otherVec.x + y * otherVec.y;
	}
	template<typename T>
	T Vec2<T>::magSquared() const {
		return x * x + y * y;
	}
	template<typename T>
	T Vec2<T>::mag() const {
		return sqrt(magSquared());
	}
}