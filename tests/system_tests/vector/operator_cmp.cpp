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

TEST_F(vector, operator_cmp_empty)
{
	const Vector v1;
	const Vector v2;

	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);

	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
	EXPECT_TRUE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);

	EXPECT_FALSE(v1 < Vector());
	EXPECT_FALSE(v2 < Vector());
	EXPECT_TRUE(v1 <= Vector());
	EXPECT_TRUE(v2 <= Vector());

	EXPECT_FALSE(v1 > Vector());
	EXPECT_FALSE(v2 > Vector());
	EXPECT_TRUE(v1 >= Vector());
	EXPECT_TRUE(v2 >= Vector());

	EXPECT_FALSE(Vector() < v2);
	EXPECT_FALSE(Vector() < v1);
	EXPECT_TRUE(Vector() <= v2);
	EXPECT_TRUE(Vector() <= v1);

	EXPECT_FALSE(Vector() > v2);
	EXPECT_FALSE(Vector() > v1);
	EXPECT_TRUE(Vector() >= v2);
	EXPECT_TRUE(Vector() >= v1);
}

TEST_F(vector, operator_cmp_empty2)
{
	const Vector v1;

	EXPECT_FALSE(v1 < v1);
	EXPECT_FALSE(v1 < v1);
	EXPECT_TRUE(v1 <= v1);
	EXPECT_TRUE(v1 <= v1);

	EXPECT_FALSE(v1 > v1);
	EXPECT_FALSE(v1 > v1);
	EXPECT_TRUE(v1 >= v1);
	EXPECT_TRUE(v1 >= v1);
}

TEST_F(vector, operator_less)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST_F(vector, operator_less2)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 4};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST_F(vector, operator_less3)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 < v2);
	EXPECT_TRUE(v2 < v1);
}

TEST_F(vector, operator_less_self)
{
	ftc::Data    a[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(v1 < v1);
}

TEST_F(vector, operator_grater)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST_F(vector, operator_grater2)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 4};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 > v2);
	EXPECT_TRUE(v2 > v1);
}

TEST_F(vector, operator_grater3)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST_F(vector, operator_grater_self)
{
	ftc::Data    a[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(v1 > v1);
}

TEST_F(vector, operator_less_eq)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST_F(vector, operator_less_eq2)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 4};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_FALSE(v2 <= v1);
}

TEST_F(vector, operator_less_eq3)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST_F(vector, operator_less_eq_self)
{
	ftc::Data    a[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));

	EXPECT_TRUE(v1 <= v1);
}

TEST_F(vector, operator_grater_eq)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST_F(vector, operator_grater_eq2)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2, 4};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST_F(vector, operator_grater_eq3)
{
	ftc::Data    a[] = {1, 2, 3};
	ftc::Data    b[] = {1, 2};
	const Vector v1(a, a + ARRAY_SIZE(a));
	const Vector v2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_FALSE(v2 >= v1);
}

TEST_F(vector, operator_gather_eq_self)
{
	ftc::Data    a[] = {1, 2, 3};
	const Vector v1(a, a + ARRAY_SIZE(a));

	EXPECT_TRUE(v1 >= v1);
}
