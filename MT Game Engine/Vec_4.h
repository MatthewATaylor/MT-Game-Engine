#pragma once

namespace mtge {
	namespace math {
		template<typename T>
		class Vec<T, 4>;

		template<typename T>
		std::ostream &operator<<(std::ostream &outputStream, const Vec<T, 4> &vec);

		template<typename T>
		class Vec<T, 4> {
		private:
			T elements[4];

		public:
			Vec();
			Vec(T elements[4]);
			Vec(T x, T y, T z, T w);

			Vec<T, 4> &operator=(const Vec<T, 4> &otherVec);
			Vec<T, 4> &operator+=(const Vec<T, 4> &otherVec);
			Vec<T, 4> &operator-=(const Vec<T, 4> &otherVec);

			Vec<T, 4> operator+(const Vec<T, 4> &otherVec) const;
			Vec<T, 4> operator-(const Vec<T, 4> &otherVec) const;

			bool operator==(const Vec<T, 4> &otherVec) const;

			friend std::ostream &operator<<<T, 4>(std::ostream &outputStream, const Vec<T, 4> &vec);

			T dot(const Vec<T, 4> &otherVec) const;
			T magSquared() const;
			T mag() const;

			T get(unsigned int index) const;
			T getX() const;
			T getY() const;
			T getZ() const;
			T getW() const;
			void set(unsigned int index, T newElement);
			void setX(T newElement);
			void setY(T newElement);
			void setZ(T newElement);
			void setW(T newElement);
		};
	}
}

#include "Vec_4.inl"