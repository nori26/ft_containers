#include "gtest.h"

#include <limits>
#include <memory>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
#include "vector_fixture.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > Vector;
typedef ftc::Allocator<ftc::Data>::ExceptionOn            AllocExceptionOn;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST_F(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
}

