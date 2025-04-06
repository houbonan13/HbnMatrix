#pragma once
#ifndef HBNMATRIXMID_H
#define HBNMATRIXMID_H

#include <iostream>
#include<initializer_list>
#include<stdexcept>
#include<memory>
#include "HbnMatrixBase.h"

namespace HbnTools {
	template<typename T>
	class MatrixMid : public MatrixBase<T> {

	private:
		std::unique_ptr<T[]> m_data;
		MatrixPreExam m_preexam;

	private:
		MatrixMid()
			:MatrixBase<T>()
		{
			m_data = nullptr;
			m_preexam = nullptr;
		}
		MatrixMid(size_t row, size_t col) :MatrixBase<T>(row, col)
		{
			m_data = std::make_unique<T[]>(row * col);
			m_preexam = this;
		}
		MatrixMid(std::initializer_list<std::initializer_list<T>> list) {
			m_row = list.size();
			if (m_row == 0) {
				m_column = 0;
				m_data = nullptr;
				m_size = 0;
				m_preexam = this;
				return;
			}
			m_column = list.begin()->size();
			//data = new T[row * column];
			m_data = std::make_unique<T[]>(m_row * m_column);
			int temp_row = 0;
			for (auto it = list.begin(); it != list.end(); it++) {
				int temp_col = 0;
				for (auto it2 = it->begin(); it2 != it->end(); it2++) {
					m_data[index(temp_row, temp_col)] = *it2;
					temp_col++;
				}
				temp_row++;
			}
			m_size = m_row * m_column;
			m_preexam = this;
		}
		MatrixMid(const MatrixMid& m) : MatrixBase<T>(m) {
			if (m.m_data) {
				size_t size_tmp = m_row * m_column;
				m_data = std::make_unique<T[]>(size_tmp);
				for (size_t i = 0; i < size_tmp; i++) {
					m_data[i] = m.m_data[i];
				}
			}
			m_preexam = this;
		}
	};
}


#endif