#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
	template <class T>
	void swap(T &a, T &b)
	{
		T tmp = a;
		a     = b;
		b     = tmp;
	}
} // namespace ft

#endif
