#pragma once

#include <ostream>

namespace mtge {
	namespace math {
		template<typename T, unsigned int SIZE>
		class Vec;

		template<typename T, unsigned int SIZE>
		std::ostream &operator<<(std::ostream &outputStream, const Vec<T, SIZE> &vec);

		template<typename T, unsigned int SIZE>
		class Vec {
		private:
			T elements[SIZE];

		public:
			Vec();
			Vec(T elements[SIZE]);
			Vec(T element);

			Vec<T, SIZE> &operator=(const Vec<T, SIZE> &otherVec);
			Vec<T, SIZE> &operator+=(const Vec<T, SIZE> &otherVec);
			Vec<T, SIZE> &operator-=(const Vec<T, SIZE> &otherVec);

			Vec<T, SIZE> &operator+=(const T value);
			Vec<T, SIZE> &operator-=(const T value);
			Vec<T, SIZE> &operator*=(const T value);
			Vec<T, SIZE> &operator/=(const T value);

			Vec<T, SIZE> operator+(const Vec<T, SIZE> &otherVec) const;
			Vec<T, SIZE> operator-(const Vec<T, SIZE> &otherVec) const;

			Vec<T, SIZE> operator+(const T value) const;
			Vec<T, SIZE> operator-(const T value) const;
			Vec<T, SIZE> operator*(const T value) const;
			Vec<T, SIZE> operator/(const T value) const;

			bool operator==(const Vec<T, SIZE> &otherVec) const;

			friend std::ostream &operator<<<T, SIZE>(std::ostream &outputStream, const Vec<T, SIZE> &vec);

			T dot(const Vec<T, SIZE> &otherVec) const;
			T magSquared() const;
			T mag() const;

			T get(unsigned int index) const;
			void set(unsigned int index, T newElement);
		};

		typedef Vec<float, 2> Vec2;
		typedef Vec<float, 3> Vec3;
		typedef Vec<float, 4> Vec4;
	}
}

#include "../../Source/Math/Vec.inl"

//Template Specializations
#include "Vec_2.h"
#include "Vec_3.h"
#include "Vec_4.h"