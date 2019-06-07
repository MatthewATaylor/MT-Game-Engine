#pragma once

#include <ostream>

namespace mtge {
	template<typename T>
	class Vec4;

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec4<T> &vec);

	template<typename T>
	class Vec4 {
	public:
		T x;
		T y;
		T z;
		T w;

		Vec4();
		Vec4(T x, T y, T z, T w);

		Vec4<T> &operator=(const Vec4<T> &otherVec);
		Vec4<T> &operator+=(const Vec4<T> &otherVec);
		Vec4<T> &operator-=(const Vec4<T> &otherVec);
		Vec4<T> &operator*=(const Vec4<T> &otherVec);
		Vec4<T> &operator/=(const Vec4<T> &otherVec);

		Vec4<T> operator+(const Vec4<T> &otherVec) const;
		Vec4<T> operator-(const Vec4<T> &otherVec) const;
		Vec4<T> operator*(const Vec4<T> &otherVec) const;
		Vec4<T> operator/(const Vec4<T> &otherVec) const;

		bool operator==(const Vec4<T> &otherVec) const;

		friend std::ostream &operator<<<T>(std::ostream &outputStream, const Vec4<T> &vec);

		T magSquared() const;
		T mag() const;
	};
}

#include "Vec4.inl"