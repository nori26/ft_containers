#ifndef ITERATOR_META_FUNCS_HPP
#define ITERATOR_META_FUNCS_HPP

#include <iterator>

#include "type_traits.hpp"
#include "iterator_traits_impl.hpp"
#include "iterator.hpp"

namespace ft
{
	// clang-format off
	template
	<
		typename From,
		typename To,
		bool = has_iterator_typedefs<From>::value
	>
	struct is_convertible_iterator : public
		is_convertible
		<
			typename iterator_traits<From>::iterator_category,
			To
		>
	{};

	template <typename From, typename To>
	struct is_convertible_iterator<From *, To, false> : public
		is_convertible
		<
			typename iterator_traits<From *>::iterator_category,
			To
		>
	{};

	template <typename From, typename To>
	struct is_convertible_iterator<From, To, false>
	{
		enum {value = 0};
	};

	template <typename T>
	struct is_forward_iterator :
		public is_convertible_iterator<T, std::forward_iterator_tag> {};

	template <typename T>
	struct is_input_iterator :
		public is_convertible_iterator<T, std::input_iterator_tag> {};
	// clang-format on
} // namespace ft

#endif
