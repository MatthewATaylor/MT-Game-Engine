#pragma once

#include <iostream>
#include <cmath>

namespace mtge {
	template<typename T>
	class Vec3;

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec3<T> &otherVec);

	template<typename T>
	class Vec3 {
	public:
		T x;
		T y;
		T z;

		Vec3();
		Vec3(T x, T y, T z);

		Vec3<T> &operator=(const Vec3<T> &otherVec);
		Vec3<T> &operator+=(const Vec3<T> &otherVec);
		Vec3<T> &operator-=(const Vec3<T> &otherVec);
		Vec3<T> &operator*=(const Vec3<T> &otherVec);
		Vec3<T> &operator/=(const Vec3<T> &otherVec);

		Vec3<T> operator+(const Vec3<T> &otherVec) const;
		Vec3<T> operator-(const Vec3<T> &otherVec) const;
		Vec3<T> operator*(const Vec3<T> &otherVec) const;
		Vec3<T> operator/(const Vec3<T> &otherVec) const;

		bool operator==(const Vec3<T> &otherVec) const;

		friend std::ostream &operator<<<T>(std::ostream &outputStream, const Vec3<T> &vec);

		T dot(const Vec3<T> &otherVec) const;
		T magSquared() const;
		T mag() const;
	};
}

#include "Vec3.inl"