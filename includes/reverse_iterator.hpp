#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	class reverse_iterator : public std::iterator<
								 typename iterator_traits<Iter>::iterator_category,
								 typename iterator_traits<Iter>::value_type,
								 typename iterator_traits<Iter>::difference_type,
								 typename iterator_traits<Iter>::pointer,
								 typename iterator_traits<Iter>::reference>
	{
	  protected:
		Iter current;

	  public:
		reverse_iterator() : current() {}

		template <typename T>
		reverse_iterator(const reverse_iterator<T> &other) : current()
		{
			(void)other;
		}
	};
} // namespace ft
#endif
