#include "Elem.hpp"

namespace ft_containers
{
	Elem::Elem(int i) : n(i) {}

	bool operator==(const Elem &a, const Elem &b)
	{
		return a.n == b.n;
	}

	bool operator<(const Elem &a, const Elem &b)
	{
		return a.n < b.n;
	}
} // namespace ft_containers
