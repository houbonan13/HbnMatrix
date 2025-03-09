#include<iostream>
#include<string>
#include "HbnTools.h"


int main() {
	HbnTools::Matrix<int>m(4, 6);
	m[2][3] = 4;
	std::cout << m[2][3] << std::endl;
	std::cin.get();
}