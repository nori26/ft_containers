#include "gtest.h"

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"

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

// If size() is ​0​, data() may or may not return a null pointer.
TEST(vector, default_constructor)
{
	Vector v = Vector();
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
}

TEST(vector, constructor_alloc)
{
	Vector v = Vector(ftc::Allocator<ftc::Data>());

	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
	v.push_back(1);
	EXPECT_EQ(v[0], 1);
}

TEST(vector, copy_constructor)
{
	{
		Vector v;

		v.reserve(128);
		for (size_t i = 0; i < 128; i++) {
			v.resize(i);
			Vector v2 = Vector(v);
			ASSERT_EQ(v2.size(), i);
			ASSERT_EQ(v2.capacity(), i);
		}
	}
	{
		Vector v1;
		v1.push_back(1);

		Vector v2 = v1;
		v1[0]     = 0;
		EXPECT_NE(v1[0], v2[0]);
	}
}
