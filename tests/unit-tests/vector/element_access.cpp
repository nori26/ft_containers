#include "gtest.h"

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"
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

TEST_F(vector, at_empty)
{
	Vector v;

	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	EXPECT_THROW(v.at(0), std::out_of_range);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, at)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v.at(i), a[i]);
	}
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_THROW(v.at(ARRAY_SIZE(a)), std::out_of_range);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	v.at(0) = 10;
	EXPECT_EQ(v.at(0), 10);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, at_empty_const)
{
	const Vector v;

	const ftc::Data  *p   = v.data();
	Vector::size_type cap = v.capacity();
	EXPECT_THROW(v.at(0), std::out_of_range);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

