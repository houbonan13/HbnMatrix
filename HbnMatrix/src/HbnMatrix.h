#pragma once
#include<iostream>
#include<initializer_list>

namespace HbnTools {

template <typename T>
class Matrix {
private:
	size_t row, column;
	T* data;
private:
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
private:
	int index(int i, int j) const {
		return i * column + j;
	}
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
	Matrix(std::initializer_list<std::initializer_list<T>> list) {
		row = list.size();
		if (row == 0) {
			column = 0;
			data = nullptr;
			return;
		}
		column = list.begin()->size();
		data = new T[row * column];
		int temp_row = 0;
		for (auto it = list.begin(); it != list.end(); it++) {
			int temp_col = 0;
			for (auto it2 = it->begin(); it2 != it->end(); it2++) {
				data[index(temp_row, temp_col)] = *it2;
				temp_col++;
			}
			temp_row++;
		}
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

	const int GetRow() const noexcept {
		return row;
	}
	const int GetCol() const noexcept {
		return column;
	}

	const void Print() const noexcept {
		if (data == NULL) {
			std::cout << "The matrix is empty!\n";
			return;
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				std::cout << data[index(i, j)] << " ";
			}
			std::cout << std::endl;
		}
		return;
	}
};

}

