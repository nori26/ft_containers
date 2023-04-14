#include "gtest.h"

#include <algorithm>
#include <climits>
#include <typeinfo>

#include "allocator.hpp"
#include "cmp.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "map.hpp"
#else
  #include <map>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::pair<const ftc::Data, ftc::Data> ValueType;

typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator<ValueType> >  Map;
typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator2<ValueType> > Map2;
typedef ftc::Allocator<ValueType>::ExceptionOn AllocExceptionOn;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, operator_cmp_empty)
{
	const Map m1;
	const Map m2;

	EXPECT_FALSE(m1 < m2);
	EXPECT_FALSE(m2 < m1);
	EXPECT_TRUE(m1 <= m2);
	EXPECT_TRUE(m2 <= m1);

	EXPECT_FALSE(m1 > m2);
	EXPECT_FALSE(m2 > m1);
	EXPECT_TRUE(m1 >= m2);
	EXPECT_TRUE(m2 >= m1);

	EXPECT_FALSE(m1 < Map());
	EXPECT_FALSE(m2 < Map());
	EXPECT_TRUE(m1 <= Map());
	EXPECT_TRUE(m2 <= Map());

	EXPECT_FALSE(m1 > Map());
	EXPECT_FALSE(m2 > Map());
	EXPECT_TRUE(m1 >= Map());
	EXPECT_TRUE(m2 >= Map());

	EXPECT_FALSE(Map() < m2);
	EXPECT_FALSE(Map() < m1);
	EXPECT_TRUE(Map() <= m2);
	EXPECT_TRUE(Map() <= m1);

	EXPECT_FALSE(Map() > m2);
	EXPECT_FALSE(Map() > m1);
	EXPECT_TRUE(Map() >= m2);
	EXPECT_TRUE(Map() >= m1);
}

TEST(map, operator_cmp_empty2)
{
	const Map m1;

	EXPECT_FALSE(m1 < m1);
	EXPECT_FALSE(m1 < m1);
	EXPECT_TRUE(m1 <= m1);
	EXPECT_TRUE(m1 <= m1);

	EXPECT_FALSE(m1 > m1);
	EXPECT_FALSE(m1 > m1);
	EXPECT_TRUE(m1 >= m1);
	EXPECT_TRUE(m1 >= m1);
}

TEST(map, operator_less)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 < m2);
	EXPECT_FALSE(m2 < m1);
}

TEST(map, operator_less2)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 < m2);
	EXPECT_FALSE(m2 < m1);
}

TEST(map, operator_less3)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 < m2);
	EXPECT_TRUE(m2 < m1);
}

TEST(map, operator_less4)
{
	ValueType a[] = {ValueType(1, 1)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 < m2);
	EXPECT_FALSE(m2 < m1);
}

TEST(map, operator_less5)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 < m2);
	EXPECT_FALSE(m2 < m1);
}

TEST(map, operator_less_self)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(m1 < m1);
}

TEST(map, operator_grater)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 > m2);
	EXPECT_FALSE(m2 > m1);
}

TEST(map, operator_grater2)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 > m2);
	EXPECT_TRUE(m2 > m1);
}

TEST(map, operator_grater3)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 > m2);
	EXPECT_FALSE(m2 > m1);
}

TEST(map, operator_grater4)
{
	ValueType a[] = {ValueType(1, 1)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 > m2);
	EXPECT_TRUE(m2 > m1);
}

TEST(map, operator_grater5)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 > m2);
	EXPECT_TRUE(m2 > m1);
}

TEST(map, operator_grater_self)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(m1 > m1);
}

TEST(map, operator_less_eq)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 <= m2);
	EXPECT_TRUE(m2 <= m1);
}

TEST(map, operator_less_eq2)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 <= m2);
	EXPECT_FALSE(m2 <= m1);
}

TEST(map, operator_less_eq3)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 <= m2);
	EXPECT_TRUE(m2 <= m1);
}

TEST(map, operator_less_eq4)
{
	ValueType a[] = {ValueType(1, 1)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 <= m2);
	EXPECT_FALSE(m2 <= m1);
}

TEST(map, operator_less_eq5)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 <= m2);
	EXPECT_FALSE(m2 <= m1);
}

TEST(map, operator_less_eq_self)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));

	EXPECT_TRUE(m1 <= m1);
}

TEST(map, operator_grater_eq)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 >= m2);
	EXPECT_TRUE(m2 >= m1);
}

TEST(map, operator_grater_eq2)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 >= m2);
	EXPECT_TRUE(m2 >= m1);
}

TEST(map, operator_grater_eq3)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType b[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(m1 >= m2);
	EXPECT_FALSE(m2 >= m1);
}

TEST(map, operator_grater_eq4)
{
	ValueType a[] = {ValueType(1, 1)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 >= m2);
	EXPECT_TRUE(m2 >= m1);
}

TEST(map, operator_grater_eq5)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType b[] = {ValueType(1, 2)};
	const Map m1(a, a + ARRAY_SIZE(a));
	const Map m2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(m1 >= m2);
	EXPECT_TRUE(m2 >= m1);
}

TEST(map, operator_gather_eq_self)
{
	ValueType a[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a, a + ARRAY_SIZE(a));

	EXPECT_TRUE(m1 >= m1);
}
