#include <ostream>

#include "Vec4.h"

namespace mtge {
	template<typename T>
	class Mat4x4;

	template<typename T>
	std::ostream &operator<<(std::ostream &outputStream, const Mat4x4<T> &mat);

	template<typename T>
	class Mat4x4 {
	private:
		template<typename LambdaType>
		void forAllElements(LambdaType lambda) const;

		template<typename LambdaType>
		void forAllElementsMutable(LambdaType lambda);

	public:
		T elements[4][4];

		Mat4x4();
		Mat4x4(T elements[4][4]);

		Mat4x4<T> &operator=(const Mat4x4<T> &otherMat);
		Mat4x4<T> &operator+=(const Mat4x4<T> &otherMat);
		Mat4x4<T> &operator-=(const Mat4x4<T> &otherMat);
		Mat4x4<T> &operator*=(const Mat4x4<T> &otherMat);

		Mat4x4<T> operator+(const Mat4x4<T> &otherMat) const;
		Mat4x4<T> operator-(const Mat4x4<T> &otherMat) const;
		Mat4x4<T> operator*(const Mat4x4<T> &otherMat) const;
		Vec4<T> operator*(Vec4<T> &vec) const;

		bool operator==(const Mat4x4<T> &otherMat) const;

		friend std::ostream &operator<<<T>(std::ostream &outputStream, const Mat4x4<T> &mat);

		T get(unsigned int row, unsigned int col) const;
		void set(unsigned int row, unsigned int col, T newElement);
	};
};

#include "Mat4x4.inl"