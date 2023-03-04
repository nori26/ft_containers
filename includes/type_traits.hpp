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

	template <typename From, typename To>
	struct is_convertible
	{
	  private:
		typedef struct
		{
			char a[2];
		} no;
		typedef char yes;

		static From f;
		static yes  test(To);
		static no   test(...);

	  public:
	  	// sizeofはオペランドの式を評価しない
		static const bool value = sizeof(test(f)) == sizeof(yes);
	};
	template <typename From, typename To>
	From is_convertible<From, To>::f;

	template <typename From, typename To>
	const bool is_convertible<From, To>::value;
} // namespace ft

#endif
