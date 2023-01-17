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

TEST(vector, default_construtor)
{
	ft::vector<int> i = ft::vector<int>();
	EXPECT_EQ(i.size(), 0U);
	EXPECT_EQ(i.capacity(), 0U);
}
