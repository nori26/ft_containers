#include "gtest.h"

#include <typeinfo>

#include "type_traits.hpp"
#include "type_utils.hpp"

// #ifndef FT_TEST
// namespace ft = std;
// #endif

namespace ftc = ft_containers;

template <typename T>
typename ft::enable_if<ftc::is_const<T>::value, int>::type enable_if_func()
{
	return 0;
}

template <typename T>
typename ft::enable_if<!ftc::is_const<T>::value, int>::type enable_if_func()
{
	return 1;
}

TEST(enable_if, basic)
{
	EXPECT_EQ(typeid(ft::enable_if<true, bool>::type), typeid(bool));
	EXPECT_EQ(typeid(ft::enable_if<true>::type), typeid(void));
	EXPECT_EQ(enable_if_func<const char>(), 0);
	EXPECT_EQ(enable_if_func<char>(), 1);
}

TEST(is_convertible, basic)
{
	EXPECT_TRUE((ft::is_convertible<char *, char *>::value));
	EXPECT_TRUE((ft::is_convertible<const char *, const char *>::value));
	EXPECT_TRUE((ft::is_convertible<char *, const char *>::value));
	EXPECT_FALSE((ft::is_convertible<const char *, char *>::value));
}
