#pragma once

#include <ostream>

namespace mtge {
	template<typename T>
	class Vec2;

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Vec2<T> &vec);
	
	template<typename T>
	class Vec2 {
	public:
		T x;
		T y;

		Vec2();
		Vec2(T x, T y);

		Vec2<T> &operator=(const Vec2<T> &otherVec);
		Vec2<T> &operator+=(const Vec2<T> &otherVec);
		Vec2<T> &operator-=(const Vec2<T> &otherVec);
		Vec2<T> &operator*=(const Vec2<T> &otherVec);
		Vec2<T> &operator/=(const Vec2<T> &otherVec);
		
		Vec2<T> operator+(const Vec2<T> &otherVec) const;
		Vec2<T> operator-(const Vec2<T> &otherVec) const;
		Vec2<T> operator*(const Vec2<T> &otherVec) const;
		Vec2<T> operator/(const Vec2<T> &otherVec) const;

		bool operator==(const Vec2<T> &otherVec) const;

		friend std::ostream &operator<<<T>(std::ostream &outputStream, const Vec2<T> &vec);

		T dot(const Vec2<T> &otherVec) const;
		T magSquared() const;
		T mag() const;
	};
}

#include "Vec2.inl"