#include "gtest.h"

#include <limits>
#include <memory>

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

TEST_F(vector, get_allocator)
{
	ftc::Allocator<ftc::Data> a;
	const Vector              v(a);

	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
}
