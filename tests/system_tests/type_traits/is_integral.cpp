// #include <iostream>
// #include <type_traits>

// int main()
// {
// 	// std::cout << std::is_integral<bool>::value << std::endl;
// 	// std::cout << std::is_integral<char>::value << std::endl;
// 	// std::cout << std::is_integral<wchar_t>::value << std::endl;
// 	// std::cout << std::is_integral<short>::value << std::endl;
// 	// std::cout << std::is_integral<int>::value << std::endl;
// 	// std::cout << std::is_integral<long>::value << std::endl;

// 	// std::cout << std::is_integral<signed char>::value << std::endl;
// 	// std::cout << std::is_integral<unsigned char>::value << std::endl;
// 	// std::cout << std::is_integral<unsigned short>::value << std::endl;
// 	// std::cout << std::is_integral<unsigned int>::value << std::endl;
// 	// std::cout << std::is_integral<unsigned long>::value << std::endl;

// 	class A
// 	{
// 	//   public:
// 	// 	operator int()
// 	// 	{
// 	// 		return 0;
// 	// 	}
// 	};
// 	std::cout << std::is_integral<A>::value << std::endl;
// 	std::cout << std::is_integral<int[]>::value << std::endl;
// }

#include "gtest.h"

#include <typeinfo>

#include "type_traits.hpp"
#include "type_utils.hpp"

namespace ftc = ft_containers;

namespace IsIntegralTest
{
	class A
	{
	  public:
		operator int()
		{
			return 0;
		}
	};
} // namespace IsIntegralTest

TEST(is_integral, integral_constant)
{
	ft::is_integral<int>               i;
	ft::integral_constant<bool, true> &p = i;

	EXPECT_TRUE(i);
	EXPECT_TRUE(p);
	EXPECT_EQ(typeid(ft::is_integral<int>::value_type), typeid(bool));
	EXPECT_EQ(typeid(ft::is_integral<int>::type), typeid(ft::integral_constant<bool, true>));
}

TEST(is_integral, unqualified_true)
{
	EXPECT_TRUE(ft::is_integral<bool>::value);
	EXPECT_TRUE(ft::is_integral<char>::value);
	EXPECT_TRUE(ft::is_integral<wchar_t>::value);
	EXPECT_TRUE(ft::is_integral<short>::value);
	EXPECT_TRUE(ft::is_integral<int>::value);
	EXPECT_TRUE(ft::is_integral<long>::value);

	EXPECT_TRUE(ft::is_integral<signed char>::value);
	EXPECT_TRUE(ft::is_integral<unsigned char>::value);
	EXPECT_TRUE(ft::is_integral<unsigned short>::value);
	EXPECT_TRUE(ft::is_integral<unsigned int>::value);
	EXPECT_TRUE(ft::is_integral<unsigned long>::value);
}

TEST(is_integral, const_true)
{
	EXPECT_TRUE(ft::is_integral<const bool>::value);
	EXPECT_TRUE(ft::is_integral<const char>::value);
	EXPECT_TRUE(ft::is_integral<const wchar_t>::value);
	EXPECT_TRUE(ft::is_integral<const short>::value);
	EXPECT_TRUE(ft::is_integral<const int>::value);
	EXPECT_TRUE(ft::is_integral<const long>::value);

	EXPECT_TRUE(ft::is_integral<const signed char>::value);
	EXPECT_TRUE(ft::is_integral<const unsigned char>::value);
	EXPECT_TRUE(ft::is_integral<const unsigned short>::value);
	EXPECT_TRUE(ft::is_integral<const unsigned int>::value);
	EXPECT_TRUE(ft::is_integral<const unsigned long>::value);
}

TEST(is_integral, volatile_true)
{
	EXPECT_TRUE(ft::is_integral<volatile bool>::value);
	EXPECT_TRUE(ft::is_integral<volatile char>::value);
	EXPECT_TRUE(ft::is_integral<volatile wchar_t>::value);
	EXPECT_TRUE(ft::is_integral<volatile short>::value);
	EXPECT_TRUE(ft::is_integral<volatile int>::value);
	EXPECT_TRUE(ft::is_integral<volatile long>::value);

	EXPECT_TRUE(ft::is_integral<volatile signed char>::value);
	EXPECT_TRUE(ft::is_integral<volatile unsigned char>::value);
	EXPECT_TRUE(ft::is_integral<volatile unsigned short>::value);
	EXPECT_TRUE(ft::is_integral<volatile unsigned int>::value);
	EXPECT_TRUE(ft::is_integral<volatile unsigned long>::value);
}

TEST(is_integral, volatile_const_true)
{
	EXPECT_TRUE(ft::is_integral<volatile const bool>::value);
	EXPECT_TRUE(ft::is_integral<volatile const char>::value);
	EXPECT_TRUE(ft::is_integral<volatile const wchar_t>::value);
	EXPECT_TRUE(ft::is_integral<volatile const short>::value);
	EXPECT_TRUE(ft::is_integral<volatile const int>::value);
	EXPECT_TRUE(ft::is_integral<volatile const long>::value);

	EXPECT_TRUE(ft::is_integral<volatile const signed char>::value);
	EXPECT_TRUE(ft::is_integral<volatile const unsigned char>::value);
	EXPECT_TRUE(ft::is_integral<volatile const unsigned short>::value);
	EXPECT_TRUE(ft::is_integral<volatile const unsigned int>::value);
	EXPECT_TRUE(ft::is_integral<volatile const unsigned long>::value);
}

TEST(is_integral, unqualified_false)
{
	EXPECT_FALSE(ft::is_integral<float>::value);
	EXPECT_FALSE(ft::is_integral<double>::value);

	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A>::value);

	EXPECT_FALSE(ft::is_integral<bool[]>::value);
	EXPECT_FALSE(ft::is_integral<char[]>::value);
	EXPECT_FALSE(ft::is_integral<wchar_t[]>::value);
	EXPECT_FALSE(ft::is_integral<short[]>::value);
	EXPECT_FALSE(ft::is_integral<int[]>::value);
	EXPECT_FALSE(ft::is_integral<long[]>::value);

	EXPECT_FALSE(ft::is_integral<signed char[]>::value);
	EXPECT_FALSE(ft::is_integral<unsigned char[]>::value);
	EXPECT_FALSE(ft::is_integral<unsigned short[]>::value);
	EXPECT_FALSE(ft::is_integral<unsigned int[]>::value);
	EXPECT_FALSE(ft::is_integral<unsigned long[]>::value);

	EXPECT_FALSE(ft::is_integral<float[]>::value);
	EXPECT_FALSE(ft::is_integral<double[]>::value);
	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A[]>::value);
}

TEST(is_integral, const_false)
{
	EXPECT_FALSE(ft::is_integral<const float>::value);
	EXPECT_FALSE(ft::is_integral<const double>::value);

	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A>::value);

	EXPECT_FALSE(ft::is_integral<const bool[]>::value);
	EXPECT_FALSE(ft::is_integral<const char[]>::value);
	EXPECT_FALSE(ft::is_integral<const wchar_t[]>::value);
	EXPECT_FALSE(ft::is_integral<const short[]>::value);
	EXPECT_FALSE(ft::is_integral<const int[]>::value);
	EXPECT_FALSE(ft::is_integral<const long[]>::value);

	EXPECT_FALSE(ft::is_integral<const signed char[]>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned char[]>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned short[]>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned int[]>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned long[]>::value);

	EXPECT_FALSE(ft::is_integral<const float[]>::value);
	EXPECT_FALSE(ft::is_integral<const double[]>::value);
	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A[]>::value);
}

TEST(is_integral, volatile_false)
{
	EXPECT_FALSE(ft::is_integral<volatile float>::value);
	EXPECT_FALSE(ft::is_integral<volatile double>::value);

	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A>::value);

	EXPECT_FALSE(ft::is_integral<volatile bool[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile wchar_t[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile short[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile int[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile long[]>::value);

	EXPECT_FALSE(ft::is_integral<volatile signed char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned short[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned int[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned long[]>::value);

	EXPECT_FALSE(ft::is_integral<volatile float[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile double[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A[]>::value);
}

TEST(is_integral, volatile_const_false)
{
	EXPECT_FALSE(ft::is_integral<volatile const float>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double>::value);

	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A>::value);

	EXPECT_FALSE(ft::is_integral<volatile const bool[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const wchar_t[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const short[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const int[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const long[]>::value);

	EXPECT_FALSE(ft::is_integral<volatile const signed char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned char[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned short[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned int[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned long[]>::value);

	EXPECT_FALSE(ft::is_integral<volatile const float[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double[]>::value);
	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A[]>::value);
}

TEST(is_integral, unqualified_ptr)
{
	EXPECT_FALSE(ft::is_integral<bool *>::value);
	EXPECT_FALSE(ft::is_integral<char *>::value);
	EXPECT_FALSE(ft::is_integral<wchar_t *>::value);
	EXPECT_FALSE(ft::is_integral<short *>::value);
	EXPECT_FALSE(ft::is_integral<int *>::value);
	EXPECT_FALSE(ft::is_integral<long *>::value);

	EXPECT_FALSE(ft::is_integral<signed char *>::value);
	EXPECT_FALSE(ft::is_integral<unsigned char *>::value);
	EXPECT_FALSE(ft::is_integral<unsigned short *>::value);
	EXPECT_FALSE(ft::is_integral<unsigned int *>::value);
	EXPECT_FALSE(ft::is_integral<unsigned long *>::value);

	EXPECT_FALSE(ft::is_integral<float *>::value);
	EXPECT_FALSE(ft::is_integral<double *>::value);

	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A *>::value);
}

TEST(is_integral, unqualified_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<const bool *>::value);
	EXPECT_FALSE(ft::is_integral<const char *>::value);
	EXPECT_FALSE(ft::is_integral<const wchar_t *>::value);
	EXPECT_FALSE(ft::is_integral<const short *>::value);
	EXPECT_FALSE(ft::is_integral<const int *>::value);
	EXPECT_FALSE(ft::is_integral<const long *>::value);

	EXPECT_FALSE(ft::is_integral<const signed char *>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned char *>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned short *>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned int *>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned long *>::value);

	EXPECT_FALSE(ft::is_integral<const float *>::value);
	EXPECT_FALSE(ft::is_integral<const double *>::value);

	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A *>::value);
}

TEST(is_integral, unqualified_volatile_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile bool *>::value);
	EXPECT_FALSE(ft::is_integral<volatile char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile wchar_t *>::value);
	EXPECT_FALSE(ft::is_integral<volatile short *>::value);
	EXPECT_FALSE(ft::is_integral<volatile int *>::value);
	EXPECT_FALSE(ft::is_integral<volatile long *>::value);

	EXPECT_FALSE(ft::is_integral<volatile signed char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned short *>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned int *>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned long *>::value);

	EXPECT_FALSE(ft::is_integral<volatile float *>::value);
	EXPECT_FALSE(ft::is_integral<volatile double *>::value);

	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A *>::value);
}

TEST(is_integral, unqualified_volatile_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile const bool *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const wchar_t *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const short *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const int *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const long *>::value);

	EXPECT_FALSE(ft::is_integral<volatile const signed char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned char *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned short *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned int *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned long *>::value);

	EXPECT_FALSE(ft::is_integral<volatile const float *>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double *>::value);

	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A *>::value);
}

TEST(is_integral, const_ptr)
{
	EXPECT_FALSE(ft::is_integral<bool *const>::value);
	EXPECT_FALSE(ft::is_integral<char *const>::value);
	EXPECT_FALSE(ft::is_integral<wchar_t *const>::value);
	EXPECT_FALSE(ft::is_integral<short *const>::value);
	EXPECT_FALSE(ft::is_integral<int *const>::value);
	EXPECT_FALSE(ft::is_integral<long *const>::value);

	EXPECT_FALSE(ft::is_integral<signed char *const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned char *const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned short *const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned int *const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned long *const>::value);

	EXPECT_FALSE(ft::is_integral<float *const>::value);
	EXPECT_FALSE(ft::is_integral<double *const>::value);

	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A *const>::value);
}

TEST(is_integral, const_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<const bool *const>::value);
	EXPECT_FALSE(ft::is_integral<const char *const>::value);
	EXPECT_FALSE(ft::is_integral<const wchar_t *const>::value);
	EXPECT_FALSE(ft::is_integral<const short *const>::value);
	EXPECT_FALSE(ft::is_integral<const int *const>::value);
	EXPECT_FALSE(ft::is_integral<const long *const>::value);

	EXPECT_FALSE(ft::is_integral<const signed char *const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned char *const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned short *const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned int *const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned long *const>::value);

	EXPECT_FALSE(ft::is_integral<const float *const>::value);
	EXPECT_FALSE(ft::is_integral<const double *const>::value);

	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A *const>::value);
}

TEST(is_integral, const_volatile_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile bool *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile wchar_t *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile short *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile int *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile long *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile signed char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned short *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned int *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned long *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile float *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile double *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A *const>::value);
}

TEST(is_integral, const_volatile_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile const bool *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const wchar_t *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const short *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const int *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const long *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const signed char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned char *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned short *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned int *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned long *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const float *const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double *const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A *const>::value);
}

TEST(is_integral, volatile_ptr)
{
	EXPECT_FALSE(ft::is_integral<bool *volatile>::value);
	EXPECT_FALSE(ft::is_integral<char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<wchar_t *volatile>::value);
	EXPECT_FALSE(ft::is_integral<short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<signed char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<unsigned char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<unsigned short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<unsigned int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<unsigned long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<float *volatile>::value);
	EXPECT_FALSE(ft::is_integral<double *volatile>::value);

	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A *volatile>::value);
}

TEST(is_integral, volatile_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<const bool *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const wchar_t *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<const signed char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<const float *volatile>::value);
	EXPECT_FALSE(ft::is_integral<const double *volatile>::value);

	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A *volatile>::value);
}

TEST(is_integral, volatile_volatile_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile bool *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile wchar_t *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile signed char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile float *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile double *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A *volatile>::value);
}

TEST(is_integral, volatile_volatile_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile const bool *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const wchar_t *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile const signed char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned char *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned short *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned int *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned long *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile const float *volatile>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double *volatile>::value);

	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A *volatile>::value);
}

TEST(is_integral, volatile_q_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<bool *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<wchar_t *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<signed char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<unsigned long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<float *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<double *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<IsIntegralTest::A *volatile const>::value);
}

TEST(is_integral, volatile_const_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<const bool *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const wchar_t *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<const signed char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const unsigned long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<const float *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<const double *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<const IsIntegralTest::A *volatile const>::value);
}

TEST(is_integral, volatile_const_volatile_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile bool *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile wchar_t *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile signed char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile unsigned long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile float *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile double *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile IsIntegralTest::A *volatile const>::value);
}

TEST(is_integral, volatile_const_volatile_const_ptr)
{
	EXPECT_FALSE(ft::is_integral<volatile const bool *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const wchar_t *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const signed char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned char *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned short *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned int *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const unsigned long *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const float *volatile const>::value);
	EXPECT_FALSE(ft::is_integral<volatile const double *volatile const>::value);

	EXPECT_FALSE(ft::is_integral<volatile const IsIntegralTest::A *volatile const>::value);
}
