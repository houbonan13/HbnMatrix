#pragma once
#include<iostream>
#include<exception>
#include<string>


namespace HbnTools {
	class MatrixException : public std::exception {
	private:
		std::string m_ErrorMessage;
	public:
		MatrixException(const std::string& message)
			:m_ErrorMessage(message){}
		const char* what() const noexcept override {
			return m_ErrorMessage.c_str();
		}
	};

//	template<typename T>
//	class MatrixPreExam {
//	private:
//		Matrix<T>* m_pointer;
//	public:
//		MatrixPreExam()
//			:m_pointer(nullptr){}
//
//		MatrixPreExam(const Matrix<T>* ptr)
//			:m_pointer(ptr){}
//
//		void AddDimException(const Matrix<T>& m) {
//			if (m_pointer->GetRow()!=m.GetRow()||m_pointer->GetCol()!=m.GetCol())
//				throw MatrixException("The dimension of matrices don't match!");
//		}
//	};
//
}