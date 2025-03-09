#pragma once
#include<iostream>

namespace HbnTools {

template <typename T>
class Matrix {
private:
	int row, column;
	T* data;

	class InnerCol {
	private:
		T* rowindex;
	public:
		InnerCol(T* data)
			:rowindex(data) {};
		T& operator[](int incol) {
			return rowindex[incol];
		}
		const T& operator[](int incol) const {
			return rowindex[incol];
		}
	};
public:
	Matrix()
		:row(0), column(0)
	{
		data = nullptr;
	}
	Matrix(int i, int j)
		:row(i), column(j)
	{
		data = new T[i * j]();
	}
	~Matrix() {
		delete[] data;
	}

	InnerCol operator[](int inrow) {
		return InnerCol(data + inrow * column);
	}
	const InnerCol operator[](int inrow) const {
		return InnerCol(data + inrow * column);
	}

	const int GetRow() const {
		return row;
	}
	const int GetCol() const {
		return column;
	}
};

}

