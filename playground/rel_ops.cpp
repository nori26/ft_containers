#include "../includes/iterator_wrapper.hpp"
#include <iostream>
#include <utility>
#include <vector>

using namespace std::rel_ops;

int main()
{
	ft::iterator_wrapper<char *, std::vector<int>>       p1;
	const ft::iterator_wrapper<char *, std::vector<int>> p2;

	std::cout << (p1 != p2) << std::endl;
}
