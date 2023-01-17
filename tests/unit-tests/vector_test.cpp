#include "gtest.h"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

TEST(vector, example)
{
	EXPECT_TRUE(true);
}

// If size() is ​0​, data() may or may not return a null pointer.
TEST(vector, default_construtor)
{
	ft::vector<int> v = ft::vector<int>();
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (int *)0);
	EXPECT_TRUE(v.empty());
}

TEST(vector, reserve)
{
	ft::vector<int> v = ft::vector<int>();
	v.reserve(0);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (int *)0);
	EXPECT_TRUE(v.empty());

	v.reserve(1);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 1U);
	EXPECT_NE(v.data(), (int *)0);
	EXPECT_TRUE(v.empty());
}
