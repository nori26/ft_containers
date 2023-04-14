#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>

#include "type_traits.hpp"

namespace ft
{
	template <class T>
	struct has_difference_type
	{
	  private:
		template <class U>
		static yes_type f(typename U::difference_type *);
		template <class U>
		static no_type f(...);

	  public:
		static const bool value = sizeof(f<T>(NULL)) == sizeof(yes_type);
	};

	template <class T>
	struct has_value_type
	{
	  private:
		template <class U>
		static yes_type f(typename U::value_type *);
		template <class U>
		static no_type f(...);

	  public:
		static const bool value = sizeof(f<T>(NULL)) == sizeof(yes_type);
	};

	template <class T>
	struct has_pointer
	{
	  private:
		template <class U>
		static yes_type f(typename U::pointer *);
		template <class U>
		static no_type f(...);

	  public:
		static const bool value = sizeof(f<T>(NULL)) == sizeof(yes_type);
	};

	template <class T>
	struct has_reference
	{
	  private:
		template <class U>
		static yes_type f(typename ft::remove_reference<typename U::reference>::type *);
		template <class U>
		static no_type f(...);

	  public:
		static const bool value = sizeof(f<T>(NULL)) == sizeof(yes_type);
	};

	template <class T>
	struct has_iterator_category
	{
	  private:
		template <class U>
		static yes_type f(typename U::iterator_category *);
		template <class U>
		static no_type f(...);

	  public:
		static const bool value = sizeof(f<T>(NULL)) == sizeof(yes_type);
	};

	// clang-format off
	template
	<
		typename T,
		bool = has_difference_type<T>::value &&
				has_value_type<T>::value &&
				has_pointer<T>::value &&
				has_reference<T>::value &&
				has_iterator_category<T>::value
	>
	struct has_iterator_typedefs {enum { value = 1 };};

	template <typename T>
	struct has_iterator_typedefs<T, false> {enum { value = 0 };};
	// clang-format on

	template <typename Iter, bool = has_iterator_typedefs<Iter>::value>
	class iterator_traits;

	template <typename Iter>
	class iterator_traits<Iter, true>
	{
	  public:
		typedef typename Iter::difference_type   difference_type;
		typedef typename Iter::value_type        value_type;
		typedef typename Iter::pointer           pointer;
		typedef typename Iter::reference         reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <typename T>
	class iterator_traits<T *, false>
	{
	  public:
		typedef std::ptrdiff_t                  difference_type;
		typedef T                               value_type;
		typedef T                              *pointer;
		typedef T                              &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <typename T>
	class iterator_traits<const T *, false>
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
