#ifndef ITERATOR_TRAITS_IMPL_HPP
#define ITERATOR_TRAITS_IMPL_HPP

#include <cstddef>

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
}

#endif
