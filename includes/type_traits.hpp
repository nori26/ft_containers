#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
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

	typedef char yes_type;
	typedef struct
	{
		char a[2];
	} no_type;
	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename From, typename To>
	struct is_convertible
	{
	  private:
		static From     f;
		static yes_type test(To);
		static no_type  test(...);

	  public:
		// sizeofはオペランドの式を評価しない
		static const bool value = sizeof(test(f)) == sizeof(yes_type);
	};
	template <typename From, typename To>
	From is_convertible<From, To>::f;

	template <typename From, typename To>
	const bool is_convertible<From, To>::value;
} // namespace ft

#endif
