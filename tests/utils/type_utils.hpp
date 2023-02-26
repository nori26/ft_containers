#ifndef TYPE_UTILS_HPP
#define TYPE_UTILS_HPP

namespace ft_containers
{
	template <typename T, T v>
	struct bool_type
	{
		static const T value = v;
	};

	template <typename T, T v>
	const T bool_type<T, v>::value;

	typedef bool_type<bool, true>  true_type;
	typedef bool_type<bool, false> false_type;

	template <typename T>
	struct remove_reference
	{
		typedef T type;
	};

	template <typename T>
	struct remove_reference<T &>
	{
		typedef T type;
	};

	template <typename T>
	struct is_const : false_type
	{};

	template <typename T>
	struct is_const<const T> : true_type
	{};

	template <typename T>
	struct is_reference : false_type
	{};

	template <typename T>
	struct is_reference<T &> : true_type
	{};

	template < class T >
	struct remove_pointer
	{
		typedef T type;
	};

	template < class T >
	struct remove_pointer<T *>
	{
		typedef T type;
	};

	template < class T >
	struct remove_pointer<T *const>
	{
		typedef T type;
	};

	template < class T >
	struct remove_pointer<T *volatile>
	{
		typedef T type;
	};

	template < class T >
	struct remove_pointer<T *const volatile>
	{
		typedef T type;
	};

} // namespace ft_containers
#endif
