#include "data.hpp"
#include "gtest.h"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;

TEST(vector, example)
{
	EXPECT_TRUE(true);
}

// If size() is ​0​, data() may or may not return a null pointer.
TEST(vector, default_constructor)
{
	ft::vector<ftc::Data> v = ft::vector<ftc::Data>();
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
}

TEST(vector, copy_constructor)
{
	{
		ftc::PrintOff         _;
		ft::vector<ftc::Data> v;

		v.reserve(1000);
		for (size_t i = 0; i < 1000; i++) {
			v.resize(i);
			ft::vector<ftc::Data> v2 = ft::vector<ftc::Data>(v);
			ASSERT_EQ(v2.size(), i);
			ASSERT_EQ(v2.capacity(), i);
		}
	}
	{
		ft::vector<ftc::Data> v1;
		v1.push_back(1);

		ft::vector<ftc::Data> v2 = v1;
		v1[0]                    = 0;
		EXPECT_NE(v1[0], v2[0]);
	}
}

TEST(vector, resize)
{
	ft::vector<ftc::Data> v;

	std::cout << "[ resize 0 -> 0]" << std::endl;
	v.resize(0);
	std::cout << "[ end ]" << std::endl;
	// v.push_back(1);
	// v.push_back(1);
	// std::cout << "[ resize 2 -> 0]" << std::endl;
	// v.resize(0);
	// std::cout << "[ end ]" << std::endl;
	// std::cout << "[ resize 0 -> 2]" << std::endl;
	// v.resize(2);
	// std::cout << "[ end ]" << std::endl;
}

TEST(vector, iterator)
{
	ft::vector<ftc::Data> v;
	EXPECT_EQ(v.begin(), v.end());
}

TEST(vector, reserve)
{
	ft::vector<ftc::Data> v = ft::vector<ftc::Data>();
	v.reserve(0);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());

	v.reserve(1);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 1U);
	EXPECT_NE(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
}

TEST(vector, operator_eq)
{
	ftc::PrintOff         _;
	ft::vector<ftc::Data> v;
	ft::vector<ftc::Data> v2;

	v.reserve(1000);
	for (size_t i = 0; i < 1000; i++) {
		v.resize(i);
		v2 = v;
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
	}
}
