#include <iostream>
#include <iterator>
#include <map>
#include <typeinfo>
#include <vector>

#ifndef FT
namespace ft = std;
#else
  #include "../includes/vector_iterator.hpp"
  #include "../includes/iterator.hpp"
#endif
namespace std
{
	class A
	{
	  public:
		typedef int difference_type;
		typedef int value_type;
		typedef int pointer;
		typedef int reference;
		typedef int iterator_category;
	};
} // namespace std

namespace ft
{
	template <typename T>
	class B
	{
	  public:
		typedef typename T::difference_type   difference_type;
		typedef typename T::value_type        value_type;
		typedef typename T::pointer           pointer;
		typedef typename T::reference         reference;
		typedef typename T::iterator_category iterator_category;
	};
} // namespace ft

template <typename T>
void print(T)
{
	std::cout << "difference_type   " << typeid(typename T::difference_type).name() << std::endl;
	std::cout << "value_type        " << typeid(typename T::value_type).name() << std::endl;
	std::cout << "pointer           " << typeid(typename T::pointer).name() << std::endl;
	std::cout << "reference         " << typeid(typename T::reference).name() << std::endl;
	std::cout << "iterator_category " << typeid(typename T::iterator_category).name() << std::endl;
}

int main()
{
	// ft::iterator_traits<std::map<int, int>::iterator > p;
	// ft::iterator_traits<std::vector<int> > p;
	// ft::iterator_traits<std::vector<int>::iterator > p;
	// ft::iterator_traits<void *> p;
	// ft::iterator_traits<char *> p;
	// ft::iterator_traits<A> p;
	// ft::vector_iterator<std::vector<int>::iterator > i;
	// ft::vector_iterator<ft::B<std::A> > i;
	ft::vector_iterator<std::A > i;
	(void)i;
	// print(p);
	// (void)p;
}
