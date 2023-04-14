#ifndef MINIMAL_HPP
#define MINIMAL_HPP

namespace ft_containers
{
	class Elem
	{
	  public:
		int n;
		Elem(int i = 0);
	};
	bool operator==(const Elem &a, const Elem &b);
	bool operator<(const Elem &a, const Elem &b);
} // namespace ft_containers

#endif
