#include<iostream>
#include<string>
#include "HbnTools.h"


int main() {
	HbnTools::Matrix<int>m(4, 6);
	m[2][3] = 4;
	std::cout << m[2][3] << std::endl;
	HbnTools::Matrix<int>n = { {1,3,5}, {2,5,1} };
	n.Print();
	HbnTools::Matrix<int>q = n.rSlice(0, 1);
	q.Print();
	std::cin.get();
}