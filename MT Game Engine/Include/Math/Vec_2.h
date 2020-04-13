#pragma once

namespace mtge {
	namespace math {
		template<typename T>
		class Vec<T, 2>;

		template<typename T>
		std::ostream &operator<<(std::ostream &outputStream, const Vec<T, 2> &vec);

		template<typename T>
		class Vec<T, 2> {
		private:
			T elements[2];

		public:
			Vec();
			Vec(T elements[2]);
			Vec(T x, T y);

			Vec<T, 2> &operator=(const Vec<T, 2> &otherVec);
			Vec<T, 2> &operator+=(const Vec<T, 2> &otherVec);
			Vec<T, 2> &operator-=(const Vec<T, 2> &otherVec);

			Vec<T, 2> operator+(const Vec<T, 2> &otherVec) const;
			Vec<T, 2> operator-(const Vec<T, 2> &otherVec) const;

			bool operator==(const Vec<T, 2> &otherVec) const;

			friend std::ostream &operator<<<T, 2>(std::ostream &outputStream, const Vec<T, 2> &vec);

			T dot(const Vec<T, 2> &otherVec) const;
			T magSquared() const;
			T mag() const;

			T get(unsigned int index) const;
			T getX() const;
			T getY() const;
			void set(unsigned int index, T newElement);
			void setX(T newElement);
			void setY(T newElement);
		};
	}
}

#include "../Source/Math/Vec_2.inl"