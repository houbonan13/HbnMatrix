#pragma once
#include<iostream>
#include<initializer_list>
#include<stdexcept>
#include<memory>
#include"HbnException.h"


namespace HbnTools {

//����ǰ�ȼ���һ�¾���ά���Ƿ���ϵ��쳣��
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
	//InnerCol��Ŀ�����ܹ�ʹ��˫[]��ģ�¶���ָ�������·���ĳ�����µ�ֵ
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

		void AddDimException(const Matrix<T>& m) {
			if (m_pointer->GetRow() != m.GetRow() || m_pointer->GetCol() != m.GetCol())
				throw MatrixException("The dimension of matrices don't match!");
		}
	};

private:
	size_t row, column;
	std::unique_ptr<T[]> data;
	MatrixPreExam m_preexam;

private:
	int index(int i, int j) const {
		return i * column + j;
	}
public:
	Matrix()
		:row(0), column(0)
	{
		data = nullptr;
		m_preexam = nullptr;
	}
	Matrix(int i, int j)
		:row(i), column(j)
	{
		//data = new T[i * j]();
		data = std::make_unique<T[]>(row * column);
		m_preexam = this;
	}

	//ʹ������������ֱ�Ӹ�ֵ��ʱ����øù��캯��
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
		m_preexam = this;
	}

	//�������캯�������Ը�ֵ��ʱ�����
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
		m_preexam = this;
	}

	//���������ͷ��ڴ�
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

	/*const void CheckSameDim(const Matrix& m) const {
		if (column != m.GetCol() || row != m.GetRow())
			throw DimMismatchException("The dimension of matrices don't match!");
	}*/

	//���ظ�ֵ������ţ��Ӷ�ʵ�����
	Matrix& operator=(const Matrix& m) {
		if (this != &m) {
			row = m.row;
			column = m.column;
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

