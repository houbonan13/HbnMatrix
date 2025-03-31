#pragma once
#ifndef HBNMATRIXBASE_H
#define HBNMATRIXBASE_H

#include "HbnException.h"

namespace HbnTools {

	//目的是实现一个矩阵的基类，希望后面可以通过继承这个类来实现一些基础功能
	template<typename T>
	class MatrixBase {

	protected:
		size_t m_row, m_column;
		size_t m_size;

	protected:
		size_t index(size_t i, size_t j) const {
			return i * m_column + j;
		}

	protected:
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
			const MatrixBase<T>* m_pointer;
		public:
			MatrixPreExam()
				:m_pointer(nullptr) {}

			MatrixPreExam(const MatrixBase<T>* ptr)
				:m_pointer(ptr) {}

			const void AddDimException(const MatrixBase<T>& m) const {
				if (m_pointer->GetRow() != m.GetRow() || m_pointer->GetCol() != m.GetCol())
					throw MatrixException("The dimension of matrices don't match!");
			}

			const void MultiplyDimException(const MatrixBase<T>& m) const {
				if (m_pointer->GetCol() != m.GetRow())
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

	public:
		MatrixBase()
			:m_row(0), m_column(0), m_size(0){}
		MatrixBase(size_t row, size_t col)
			:m_row(row), m_column(col), m_size(row*col){}
		MatrixBase(const MatrixBase& m)
			:m_row(m.m_row), m_column(m.m_column), m_size(m.m_size){}
		MatrixBase(MatrixBase&& m)
			:m_row(m.m_row), m_column(m.m_column), m_size(m.m_size){}
		virtual ~MatrixBase() = 0;

	public:
		virtual const size_t GetRow() const noexcept {
			return m_row;
		}
		virtual const size_t GetCol() const noexcept {
			return m_column;
		}
		virtual const T GetValue(size_t r, size_t c) const noexcept = 0;
		virtual const void Print() const noexcept = 0;
		
		virtual const MatrixBase<T> rSlice(size_t row_begin, size_t row_end) const = 0;
		virtual const MatrixBase<T> cSlice(size_t col_begin, size_t col_end) const = 0;
		virtual const MatrixBase<T> Slice(size_t r_begin, size_t r_end, size_t c_begin, size_t c_end) const = 0;
		
		MatrixBase& operator=(const MatrixBase& m) = 0;
		MatrixBase& operator+(const MatrixBase& m) = 0;
		MatrixBase& operator-(const MatrixBase& m) = 0;
		MatrixBase& operator*(const MatrixBase& m) = 0;

	};

}


#endif