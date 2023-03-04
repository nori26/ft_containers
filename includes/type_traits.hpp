#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


} // namespace ft

#endif
