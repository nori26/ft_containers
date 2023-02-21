#include <iostream>
#include <stdexcept>

#include "cmp.hpp"

Cmp::Cmp(bool b) : b_(b) {}

Cmp::operator bool() const
{
	return b_;
}

bool Cmp::operator!() const
{
	return true;
}

CommaTest::CommaTest() {}

bool CommaTest::operator==(const CommaTest &c) const
{
	(void)c;
	return true;
}

std::vector<CommaTest>::iterator operator,(
	std::vector<CommaTest>::iterator it1, std::vector<CommaTest>::iterator it2
)
{
	(void)it2;
	std::cout << "op comma" << std::endl;
	throw std::runtime_error("");
	return it1;
}

bool operator<(const CommaTest &, const CommaTest &)
{
	return true;
}
