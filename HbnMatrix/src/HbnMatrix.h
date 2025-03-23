#pragma once
#ifndef HBNMATRIX_H
#define HBNMATRIX_H

#include<iostream>
#include<initializer_list>
#include<stdexcept>
#include<memory>
#include"HbnException.h"
#include"HbnMatrixMultiply.h"


namespace HbnTools {

//计算前先检验一下矩阵维度是否符合的异常类
//class DimMismatchException : public std::exception {
//private:
//	std::string errormessage;
//public:
//	DimMismatchException(const std::string& message)
//		:errormessage(message) {}
//	const char* what() const noexcept override {
//		return errormessage.c_str();
//	}
//	};


template <typename T>
class Matrix {

private:
	//InnerCol类目的是能够使用双[]，模仿多重指针的情况下返回某索引下的值
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
		T& operator*() {
			return *rowindex;
		}
		const T& operator*() const {
			return *rowindex;
		}
	};

	class MatrixPreExam {
	private:
		const Matrix<T>* m_pointer;
	public:
		MatrixPreExam()
			:m_pointer(nullptr) {}

		MatrixPreExam(const Matrix<T>* ptr)
			:m_pointer(ptr) {}

		const void AddDimException (const Matrix<T>& m) const {
			if (m_pointer->GetRow() != m.GetRow() || m_pointer->GetCol() != m.GetCol())
				throw MatrixException("The dimension of matrices don't match!");
		}

		const void rSliceDimException(size_t r_begin, size_t r_end) const {
			if (r_end <= r_begin || r_begin<0 || r_end>m_pointer->GetRow()) {
				throw MatrixException("The required dimension is not correct!");
			}
		}

		const void cSliceDimException(size_t c_begin, size_t c_end) const {
			if (c_end <= c_begin || c_begin<0 || c_end > m_pointer->GetCol()) {
				throw MatrixException("The required dimension is not correct!");
			}
		}

		const void SliceDimException(size_t r_begin, size_t r_end, size_t c_begin, size_t c_end) const {
			if (r_end <= r_begin || r_begin<0 || r_end>m_pointer->GetRow()) {
				throw MatrixException("The required dimension is not correct!");
			}
			if (c_end <= c_begin || c_begin<0 || c_end > m_pointer->GetCol()) {
				throw MatrixException("The required dimension is not correct!");
			}
		}
	};

private:
	size_t row, column;
	size_t m_size;
	std::unique_ptr<T[]> data;
	MatrixPreExam m_preexam;

private:
	int index(int i, int j) const {
		return i * column + j;
	}
public:
	Matrix()
		:row(0), column(0), m_size(0)
	{
		data = nullptr;
		m_preexam = nullptr;
	}
	Matrix(int i, int j)
		:row(i), column(j), m_size(i*j)
	{
		//data = new T[i * j]();
		data = std::make_unique<T[]>(row * column);
		m_preexam = this;
	}

	//使用两个大括号直接赋值的时候调用该构造函数
	Matrix(std::initializer_list<std::initializer_list<T>> list) {
		row = list.size();
		if (row == 0) {
			column = 0;
			data = nullptr;
			return;
		}
		column = list.begin()->size();
		//data = new T[row * column];
		data = std::make_unique<T[]>(row * column);
		int temp_row = 0;
		for (auto it = list.begin(); it != list.end(); it++) {
			int temp_col = 0;
			for (auto it2 = it->begin(); it2 != it->end(); it2++) {
				data[index(temp_row, temp_col)] = *it2;
				temp_col++;
			}
			temp_row++;
		}
		m_size = row * column;
		m_preexam = this;
	}

	//拷贝构造函数，可以赋值的时候调用
	Matrix(const Matrix& m)
		:row(m.row), column(m.column)
	{
		if (m.data) {
			size_t size_tmp = row * column;
			data = std::make_unique<T[]>(size_tmp);
			for (size_t i = 0; i < size_tmp; i++) {
				data[i] = m.data[i];
			}
		}
		/*data = new T[row * column];
		memcpy(data, m.data, row * column * sizeof(T));*/
		m_size = m.m_size;
		m_preexam = this;
	}

	//析构函数释放内存
	~Matrix() {
	}

	InnerCol operator[](int inrow) {
		return InnerCol(data.get() + inrow * column);
	}
	const InnerCol operator[](int inrow) const {
		return InnerCol(data.get() + inrow * column);
	}

	const int GetRow() const noexcept {
		return row;
	}
	const int GetCol() const noexcept {
		return column;
	}
	const int GetValue(size_t r, size_t c) const {
		return data[index(r, c)];
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

	const Matrix rSlice(size_t row_begin, size_t row_end) const {
		try {
			m_preexam.rSliceDimException(row_begin, row_end);
		}
		catch (const MatrixException& e) {
			std::cerr << "Mismatch Exception caught: " << e.what() << std::endl;
			return Matrix();
		}
		Matrix res(row_end - row_begin, column);
		for (int i = 0; i < res.m_size; i++) {
			res.data[i] = data[row_begin * column + i];
		}
		return res;
	}

	const Matrix cSlice(size_t col_begin, size_t col_end) const {
		try {
			m_preexam.cSliceDimException(col_begin, col_end);
		}
		catch (const MatrixException& e) {
			std::cerr << "Mismatch Exception caught: " << e.what() << std::endl;
			return Matrix();
		}
		Matrix res(row, col_end - col_begin);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col_end - col_begin; j++) {
				res.data[i * (col_end - col_begin) + j] = data[i * column + col_begin + j];
			}
		}
		return res;
	}

	const Matrix Slice(size_t r_begin, size_t r_end, size_t c_begin, size_t c_end) const {
		try {
			m_preexam.SliceDimException(c_begin, c_end);
		}
		catch (const MatrixException& e) {
			std::cerr << "Mismatch Exception caught: " << e.what() << std::endl;
			return Matrix();
		}
	}

	/*const void CheckSameDim(const Matrix& m) const {
		if (column != m.GetCol() || row != m.GetRow())
			throw DimMismatchException("The dimension of matrices don't match!");
	}*/

	//重载赋值运算符号，从而实现深拷贝
	Matrix& operator=(const Matrix& m) {
		if (this != &m) {
			row = m.row;
			column = m.column;
			m_size = m.m_size;
			size_t size_tmp = row * column;
			data = std::make_unique<T[]>(size_tmp);
			for (int i = 0; i < size_tmp; i++)
				data[i] = m.data[i];
			m_preexam = this;
		}
		return *this;
	}


	Matrix operator+(const Matrix& m) {
		try {
			m_preexam.AddDimException(m);
		}
		catch (const MatrixException& e) {
			std::cerr << "Mismatch Exception caught: " << e.what() << std::endl;
			return Matrix();
		}
		Matrix sum(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				sum[i][j] = this->GetValue(i,j) + m.GetValue(i,j);
			}
		}
		return sum;
	}

	Matrix operator-(const Matrix& m) {
		try {
			m_preexam.AddDimException(m);
		}
		catch (const MatrixException& e) {
			std::cerr << "Mismatch Exception caught: " << e.what() << std::endl;
			return Matrix();
		}
		Matrix sum(row, column);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				sum[i][j] = this->GetValue(i, j) - m.GetValue(i, j);
			}
		}
		return sum;
	}
};

}

#endif