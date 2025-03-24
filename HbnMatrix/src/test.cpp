#include<iostream>
#include<string>
#include "HbnTools.h"


int main() {
	HbnTools::Matrix<int>m(4, 6);
	m[2][3] = 4;
	std::cout << m[2][3] << std::endl;
	HbnTools::Matrix<int>n = { {1,3,5}, {2,5,1} };
	HbnTools::Matrix<int>t = { {2,1},{4,9},{5,2} };
	n.Print();
	HbnTools::Matrix<int>q = n.rSlice(0, 1);
	q.Print();
	HbnTools::Matrix<int>r = n.cSlice(0, 1);
	r.Print();
	HbnTools::Matrix<int>s = n.Slice(0, 2, 0, 2);
	s.Print();
	HbnTools::Matrix<int>u = n * t;
	u.Print();
	std::cin.get();
}