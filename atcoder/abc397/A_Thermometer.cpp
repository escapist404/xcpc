#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
	double tem;
	std::cin >> tem;
  	if (tem < 37.5) {
    	std::cout << 3;
  	} else if (tem < 38.0) {
		std::cout << 2;
	} else {
		std::cout << 1;
	}
}