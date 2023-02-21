#ifndef CMP_HPP
#define CMP_HPP

#include <vector>

class Cmp
{
	bool b_;

  public:
	Cmp(bool b);

	operator bool() const;

	bool operator!() const;
};

template <typename T>
Cmp is_eq(const T &a, const T &b)
{
	return a == b;
}

template <typename T>
Cmp cmp(const T &a, const T &b)
{
	return a < b;
}

class CommaTest
{
  public:
	CommaTest();
	bool operator==(const CommaTest &c) const;
};

std::vector<CommaTest>::iterator operator,(
	std::vector<CommaTest>::iterator it1, std::vector<CommaTest>::iterator it2
);

bool operator<(const CommaTest &, const CommaTest &);

#endif
