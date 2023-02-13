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

TEST_F(vector, size_empty)
{
	const Vector v;

	EXPECT_EQ(v.size(), 0U);
}

TEST_F(vector, size)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, capacity_empty)
{
	const Vector v;

	EXPECT_EQ(v.capacity(), 0U);
}

TEST_F(vector, capacity)
{
	ftc::Data    a[] = {0};
	const Vector v(a, a + ARRAY_SIZE(a));

	EXPECT_EQ(v.capacity(), ARRAY_SIZE(a));
}

TEST_F(vector, empty)
{
	Vector v;

	EXPECT_TRUE(v.empty());
	v.reserve(10);
	EXPECT_TRUE(v.empty());
	v.push_back(1);
	EXPECT_FALSE(v.empty());
}

TEST_F(vector, empty_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v;
	const Vector v2(a, a + ARRAY_SIZE(a));

	EXPECT_TRUE(v.empty());
	EXPECT_FALSE(v2.empty());
}

TEST_F(vector, max_size)
{
	typedef std::allocator<ftc::Data>::difference_type difference_type;

	const Vector              v;
	std::allocator<ftc::Data> a;
	const Vector::size_type   alloc_max      = a.max_size();
	const Vector::size_type   difference_max = std::numeric_limits<difference_type>::max();

	EXPECT_EQ(std::min<Vector::size_type>(alloc_max, difference_max), v.max_size());
}

TEST_F(vector, size_empty_exception)
{
	const Vector     v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.size());
}

TEST_F(vector, size_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.size());
}

TEST_F(vector, capacity_empty_exception)
{
	const Vector     v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.capacity());
}

TEST_F(vector, capacity_exception)
{
	ftc::Data        a[] = {0};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.capacity());
}

TEST_F(vector, empty_exception)
{
	Vector v;

	{
		AllocExceptionOn e(1);
		ftc::ExceptionOn e2(1);
		EXPECT_NO_THROW(v.empty());
	}
	{
		v.reserve(10);
		AllocExceptionOn e(1);
		ftc::ExceptionOn e2(1);
		EXPECT_NO_THROW(v.empty());
	}
	{
		v.push_back(1);
		AllocExceptionOn e(1);
		ftc::ExceptionOn e2(1);
		EXPECT_NO_THROW(v.empty());
	}
}

TEST_F(vector, empty_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v;
	const Vector     v2(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.empty());
	EXPECT_NO_THROW(v2.empty());
}

TEST_F(vector, max_size_exception)
{
	const Vector     v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.max_size());
}
