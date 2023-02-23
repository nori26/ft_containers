#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

// TODO test
namespace ft
{
	template <typename Iter>
	class iterator_traits
	{
	  public:
		typedef typename Iter::difference_type   difference_type;
		typedef typename Iter::value_type        value_type;
		typedef typename Iter::pointer           pointer;
		typedef typename Iter::reference         reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <typename T>
	class iterator_traits<T *>
	{
	  public:
		typedef std::ptrdiff_t                  difference_type;
		typedef T                               value_type;
		typedef T                              *pointer;
		typedef T                              &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	class iterator_traits<const T *>
	{
	  public:
		typedef std::ptrdiff_t                  difference_type;
		typedef T                               value_type;
		typedef const T                        *pointer;
		typedef const T                        &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
} // namespace ft

#endif
