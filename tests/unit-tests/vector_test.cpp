#include "gtest.h"

#ifdef STL_TEST
  #include <vector>
namespace ft = std;
#else
  #include "vector.hpp"
#endif

TEST(vector, example)
{
	EXPECT_TRUE(true);
}
