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

typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator2<ValueType> > Map;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, operator_assignment_type)
{
	{
		Map  m1;
		Map  m2;
		Map &ref = (m1 = m2);

		EXPECT_EQ(typeid(Map), typeid(m1 = m2));
		EXPECT_EQ(&ref, &m1);
	}
	{
		Map       m1;
		const Map m2;
		Map      &ref = (m1 = m2);

		EXPECT_EQ(typeid(Map), typeid(m1 = m2));
		EXPECT_EQ(&ref, &m1);
	}
}

TEST(map, operator_assignment_self_empty)
{
	Map  m;
	Map &m2 = m;

	m = m2;
	EXPECT_EQ(m.size(), 0U);
	EXPECT_EQ(m.begin(), m.end());
}

TEST(map, operator_assignment_self)
{
	Map m;

	for (int i = 0; i < 10; i++) {
		m[i] = i;
	}
	Map &r = m;

	Map::size_type size = m.size();
	Map::iterator  it   = m.begin();
	m                   = r;
	EXPECT_EQ(m.size(), size);
	EXPECT_EQ(m.begin(), it);
	int i = 0;
	for (Map::iterator it = m.begin(); it != m.end(); ++it) {
		ASSERT_EQ(*it, ValueType(i, i));
		i++;
	}
}

TEST(map, operator_assignment_empty)
{
	{
		Map m;
		Map m2;

		m2 = m;
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(m2.size(), 0U);
		EXPECT_EQ(m.begin(), m.end());
		EXPECT_EQ(m2.begin(), m2.end());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());

		m.insert(ValueType(1, 1));
		m.insert(ValueType(3, 2));
		m2.insert(ValueType(2, 1));
		m2.insert(ValueType(4, 2));
		EXPECT_EQ(m[1], 1);
		EXPECT_EQ(m[3], 2);
		EXPECT_EQ(m2[2], 1);
		EXPECT_EQ(m2[4], 2);
	}
	{
		const Map m;
		Map       m2;

		m2 = m;
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(m2.size(), 0U);
		EXPECT_EQ(m.begin(), m.end());
		EXPECT_EQ(m2.begin(), m2.end());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());
		m2.insert(ValueType(2, 1));
		m2.insert(ValueType(4, 2));
		EXPECT_EQ(m2[2], 1);
		EXPECT_EQ(m2[4], 2);
	}
}

TEST(map, operator_assignment_empty2)
{
	const ValueType a1[] = {ft::make_pair(1, 1), ft::make_pair(2, 1), ft::make_pair(3, 1)};
	{
		Map m(a1, a1 + ARRAY_SIZE(a1));
		Map m2;

		m2 = m;
		EXPECT_EQ(m.size(), ARRAY_SIZE(a1));
		EXPECT_EQ(m2.size(), ARRAY_SIZE(a1));
		EXPECT_NE(m.begin(), m2.begin());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());
		size_t i = 0;
		for (Map::iterator it = m.begin(), it2 = m2.begin(); it != m.end(); ++it, ++it2) {
			EXPECT_EQ(*it, a1[i]);
			EXPECT_EQ(*it2, a1[i]);
			i++;
		}
	}
	{
		const Map m(a1, a1 + ARRAY_SIZE(a1));
		Map       m2;

		m2 = m;
		EXPECT_EQ(m.size(), ARRAY_SIZE(a1));
		EXPECT_EQ(m2.size(), ARRAY_SIZE(a1));
		EXPECT_NE(m.begin(), m2.begin());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());
		size_t i = 0;
		for (Map::const_iterator it = m.begin(), it2 = m2.begin(); it != m.end(); ++it, ++it2) {
			EXPECT_EQ(*it, a1[i]);
			EXPECT_EQ(*it2, a1[i]);
			i++;
		}
	}
}

TEST(map, operator_assignment_empty3)
{
	const ValueType a1[] = {ft::make_pair(1, 1), ft::make_pair(2, 1), ft::make_pair(3, 1)};
	{
		Map m;
		Map m2(a1, a1 + ARRAY_SIZE(a1));

		m2 = m;
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(m2.size(), 0U);
		EXPECT_EQ(m2.begin(), m2.end());
		EXPECT_NE(m.begin(), m2.begin());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());

		m2.insert(a1, a1 + ARRAY_SIZE(a1));
		EXPECT_EQ(m2.size(), ARRAY_SIZE(a1));
		size_t i = 0;
		for (Map::const_iterator it = m2.begin(); it != m2.end(); ++it) {
			EXPECT_EQ(*it, a1[i]);
			i++;
		}
	}
	{
		const Map m;
		Map       m2(a1, a1 + ARRAY_SIZE(a1));

		m2 = m;
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(m2.size(), 0U);
		EXPECT_EQ(m2.begin(), m2.end());
		EXPECT_NE(m.begin(), m2.begin());
		EXPECT_NE(m.get_allocator().get_id(), m2.get_allocator().get_id());

		m2.insert(a1, a1 + ARRAY_SIZE(a1));
		EXPECT_EQ(m2.size(), ARRAY_SIZE(a1));
		size_t i = 0;
		for (Map::const_iterator it = m2.begin(); it != m2.end(); ++it) {
			EXPECT_EQ(*it, a1[i]);
			i++;
		}
	}
}

TEST(map, operator_assignment_ret)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	const ValueType a3[]  = {ValueType(7, 7), ValueType(8, 8), ValueType(9, 9)};
	const ValueType res[] = {ValueType(7, 7), ValueType(8, 8), ValueType(9, 9)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));
	Map             m3(a3, a3 + ARRAY_SIZE(a3));

	m1 = m2           = m3;
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	Map::iterator it3 = m3.begin();
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it1, res[i]);
		ASSERT_EQ(*it2, res[i]);
		++it1;
		++it2;
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(*it3, a3[i]);
		++it3;
	}
}

TEST(map, operator_assignment_ret2)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	const ValueType a3[]  = {ValueType(7, 7), ValueType(8, 8), ValueType(9, 9)};
	const ValueType res[] = {ValueType(7, 7), ValueType(8, 8), ValueType(9, 9)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));
	Map             m3(a3, a3 + ARRAY_SIZE(a3));

	(m1 = m2)         = m3;
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	Map::iterator it3 = m3.begin();
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it1, res[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		ASSERT_EQ(*it2, a2[i]);
		++it2;
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(*it3, a3[i]);
		++it3;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
	EXPECT_EQ(it3, m3.end());
}

TEST(map, operator_assignment1)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	const ValueType res[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));

	m2                = m1;
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it1, a1[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it2, res[i]);
		++it2;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
}

TEST(map, operator_assignment2)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6), ValueType(7, 7)};
	const ValueType res[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));

	m2                = m1;
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it1, a1[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it2, res[i]);
		++it2;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
}

TEST(map, operator_assignment3)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	const ValueType res[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));

	m2                = m1;
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it1, a1[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it2, res[i]);
		++it2;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
}

TEST(map, operator_assignment_append)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6), ValueType(7, 7)};
	const ValueType res[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(9, 9)};
	Map             m1(a1, a1 + ARRAY_SIZE(a1));
	Map             m2(a2, a2 + ARRAY_SIZE(a2));

	m2 = m1;
	m2.insert(ValueType(9, 9));
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it1, a1[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it2, res[i]);
		++it2;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
}

TEST(map, operator_assignment_append2)
{
	const ValueType a1[]  = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	const ValueType a2[]  = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6), ValueType(7, 7)};
	const ValueType res[] = {
		ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(9, 9), ValueType(10, 10)};
	Map m1(a1, a1 + ARRAY_SIZE(a1));
	Map m2(a2, a2 + ARRAY_SIZE(a2));

	m2 = m1;
	m2.insert(ValueType(9, 9));
	m2.insert(ValueType(10, 10));
	Map::iterator it1 = m1.begin();
	Map::iterator it2 = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it1, a1[i]);
		++it1;
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(*it2, res[i]);
		++it2;
	}
	EXPECT_EQ(it1, m1.end());
	EXPECT_EQ(it2, m2.end());
}
