#pragma once

namespace mtge {
	namespace math {
		template<typename T>
		class Vec<T, 3>;

		template<typename T>
		std::ostream &operator<<(std::ostream &outputStream, const Vec<T, 3> &vec);

		template<typename T>
		class Vec<T, 3> {
		private:
			T elements[3];

		public:
			Vec();
			Vec(T elements[3]);
			Vec(T x, T y, T z);

			Vec<T, 3> &operator=(const Vec<T, 3> &otherVec);
			Vec<T, 3> &operator+=(const Vec<T, 3> &otherVec);
			Vec<T, 3> &operator-=(const Vec<T, 3> &otherVec);

			Vec<T, 3> operator+(const Vec<T, 3> &otherVec) const;
			Vec<T, 3> operator-(const Vec<T, 3> &otherVec) const;

			bool operator==(const Vec<T, 3> &otherVec) const;

			friend std::ostream &operator<<<T, 3>(std::ostream &outputStream, const Vec<T, 3> &vec);

			T dot(const Vec<T, 3> &otherVec) const;
			Vec<T, 3> cross(const Vec<T, 3> &otherVec) const;
			T magSquared() const;
			T mag() const;

			T get(unsigned int index) const;
			T getX() const;
			T getY() const;
			T getZ() const;
			void set(unsigned int index, T newElement);
			void setX(T newElement);
			void setY(T newElement);
			void setZ(T newElement);
		};
	}
}

#include "Vec_3.inl"