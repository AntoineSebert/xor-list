#include <iostream>

import xorlist;

int main(int argc, char **argv) {
	std::cout << "Hello CMake.\n";

	auto test = xorlist<int>(2, -1);

	return 0;
}