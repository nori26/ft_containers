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
	struct remove_const
	{
		typedef T type;
	};

	template <typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};

	template <typename T>
	struct remove_volatile
	{
		typedef T type;
	};

	template <typename T>
	struct remove_volatile<volatile T>
	{
		typedef T type;
	};

	template <typename T>
	struct remove_cv
	{
	  private:
		typedef typename remove_volatile<T>::type non_volatile_type;

	  public:
		typedef typename remove_const<non_volatile_type>::type type;
	};

	// clang-format off
	// long long は C++11
	template <typename>
	struct is_integral_base : public false_type {};

	template <> struct is_integral_base<bool>           : public true_type {};
	template <> struct is_integral_base<char>           : public true_type {};
	template <> struct is_integral_base<wchar_t>        : public true_type {};
	template <> struct is_integral_base<short>          : public true_type {};
	template <> struct is_integral_base<int>            : public true_type {};
	template <> struct is_integral_base<long>           : public true_type {};
	template <> struct is_integral_base<signed char>    : public true_type {};
	template <> struct is_integral_base<unsigned char>  : public true_type {};
	template <> struct is_integral_base<unsigned short> : public true_type {};
	template <> struct is_integral_base<unsigned int>   : public true_type {};
	template <> struct is_integral_base<unsigned long>  : public true_type {};

	template <typename T>
	struct is_integral : is_integral_base<typename remove_cv<T>::type> {};
	// clang-format on
} // namespace ft

#endif
