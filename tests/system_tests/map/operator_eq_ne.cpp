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

TEST(map, operator_eq_empty)
{
	Map m1;
	Map m2;

	EXPECT_EQ(m1, m2);
	EXPECT_TRUE(m1 == m2);
	EXPECT_EQ(m2, m1);
	EXPECT_TRUE(m2 == m1);
}

TEST(map, operator_eq_empty2)
{
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map       m1;
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);
	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_eq_empty3)
{
	Map m1;

	EXPECT_EQ(m1, Map());

	EXPECT_TRUE(m1 == Map());

	EXPECT_EQ(Map(), m1);

	EXPECT_TRUE(Map() == m1);
}

TEST(map, operator_eq)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_EQ(m1, m2);

	EXPECT_TRUE(m1 == m2);

	EXPECT_EQ(m2, m1);

	EXPECT_TRUE(m2 == m1);
}

TEST(map, operator_eq2)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);

	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_eq3)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);

	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_eq4)
{
	ValueType a1[] = {ValueType(1, 1)};
	ValueType a2[] = {ValueType(1, 2)};
	{
		Map m1(a1, a1 + ARRAY_SIZE(a1));
		Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_FALSE(m1 == m2);
		EXPECT_FALSE(m2 == m1);
	}
	{
		const Map m1(a1, a1 + ARRAY_SIZE(a1));
		const Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_FALSE(m1 == m2);
		EXPECT_FALSE(m2 == m1);
	}
	{
		Map       m1(a1, a1 + ARRAY_SIZE(a1));
		const Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_FALSE(m1 == m2);
		EXPECT_FALSE(m2 == m1);
	}
}

TEST(map, operator_ne_empty)
{
	Map m1;
	Map m2;

	EXPECT_FALSE(m1 != m2);

	EXPECT_FALSE(m2 != m1);
}

TEST(map, operator_ne_empty2)
{
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map       m1;
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);
	EXPECT_TRUE(m1 != m2);
	EXPECT_NE(m2, m1);
	EXPECT_TRUE(m2 != m1);
}

TEST(map, operator_ne_empty3)
{
	ValueType a1[] = {ValueType(1, 1)};
	Map m1;

	EXPECT_NE(m1, Map(a1, a1 + ARRAY_SIZE(a1)));
	EXPECT_TRUE(m1 != Map(a1, a1 + ARRAY_SIZE(a1)));
	EXPECT_NE(Map(a1, a1 + ARRAY_SIZE(a1)), m1);
	EXPECT_TRUE(Map(a1, a1 + ARRAY_SIZE(a1)) != m1);
}

TEST(map, operator_ne)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);

	EXPECT_TRUE(m1 != m2);

	EXPECT_NE(m2, m1);

	EXPECT_TRUE(m2 != m1);
}

TEST(map, operator_ne2)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 != m2);

	EXPECT_FALSE(m2 != m1);
}

TEST(map, operator_ne3)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2)};
	Map       m1(a1, a1 + ARRAY_SIZE(a1));
	Map       m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);

	EXPECT_TRUE(m1 != m2);

	EXPECT_NE(m2, m1);

	EXPECT_TRUE(m2 != m1);
}

TEST(map, operator_ne4)
{
	ValueType a1[] = {ValueType(1, 1)};
	ValueType a2[] = {ValueType(1, 2)};
	{
		Map m1(a1, a1 + ARRAY_SIZE(a1));
		Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_TRUE(m1 != m2);
		EXPECT_TRUE(m2 != m1);
	}
	{
		const Map m1(a1, a1 + ARRAY_SIZE(a1));
		const Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_TRUE(m1 != m2);
		EXPECT_TRUE(m2 != m1);
	}
	{
		Map       m1(a1, a1 + ARRAY_SIZE(a1));
		const Map m2(a2, a2 + ARRAY_SIZE(a2));

		EXPECT_TRUE(m1 != m2);
		EXPECT_TRUE(m2 != m1);
	}
}

TEST(map, operator_eq_empty_const)
{
	const Map m1;
	const Map m2;

	EXPECT_EQ(m1, m2);

	EXPECT_TRUE(m1 == m2);

	EXPECT_EQ(m2, m1);

	EXPECT_TRUE(m2 == m1);
}

TEST(map, operator_eq_empty2_const)
{
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1;
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);

	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_eq_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_EQ(m1, m2);

	EXPECT_TRUE(m1 == m2);

	EXPECT_EQ(m2, m1);

	EXPECT_TRUE(m2 == m1);
}

TEST(map, operator_eq2_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);

	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_eq3_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 == m2);

	EXPECT_FALSE(m2 == m1);
}

TEST(map, operator_ne_empty_const)
{
	const Map m1;
	const Map m2;

	EXPECT_FALSE(m1 != m2);

	EXPECT_FALSE(m2 != m1);
}

TEST(map, operator_ne_empty2_const)
{
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1;
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);

	EXPECT_TRUE(m1 != m2);

	EXPECT_NE(m2, m1);

	EXPECT_TRUE(m2 != m1);
}

TEST(map, operator_ne_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(4, 4)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);

	EXPECT_TRUE(m1 != m2);

	EXPECT_NE(m2, m1);

	EXPECT_TRUE(m2 != m1);
}

TEST(map, operator_ne2_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_FALSE(m1 != m2);

	EXPECT_FALSE(m2 != m1);
}

TEST(map, operator_ne3_const)
{
	ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType a2[] = {ValueType(1, 1), ValueType(2, 2)};
	const Map m1(a1, a1 + ARRAY_SIZE(a1));
	const Map m2(a2, a2 + ARRAY_SIZE(a2));

	EXPECT_NE(m1, m2);

	EXPECT_TRUE(m1 != m2);

	EXPECT_NE(m2, m1);

	EXPECT_TRUE(m2 != m1);
}
