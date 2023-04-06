#include "gtest.h"

#include <climits>
#include <functional>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "map.hpp"
#else
  #include <map>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::pair<const ftc::Data, ftc::Data>                                            ValueType;
typedef ft::map<ftc::Data, ftc::Data, std::less<ftc::Data>, ftc::Allocator<ValueType> > Map;

TEST(map, find_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().find(1)), typeid(Map::iterator));
	EXPECT_EQ(typeid(m.find(1)), typeid(Map::const_iterator));
}

TEST(map, lower_bound_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().lower_bound(1)), typeid(Map::iterator));
	EXPECT_EQ(typeid(m.lower_bound(1)), typeid(Map::const_iterator));
}

TEST(map, lower_bound)
{
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.lower_bound(-1), m.begin());
	EXPECT_EQ(m.lower_bound(0), m.begin());
	EXPECT_EQ(m.lower_bound(1), m.begin());
	EXPECT_EQ(m.lower_bound(4), m.end());
	EXPECT_EQ(m.lower_bound(5), m.end());

	const Map cm = m;

	EXPECT_EQ(cm.lower_bound(-1), cm.begin());
	EXPECT_EQ(cm.lower_bound(0), cm.begin());
	EXPECT_EQ(cm.lower_bound(1), cm.begin());
	EXPECT_EQ(cm.lower_bound(4), cm.end());
	EXPECT_EQ(cm.lower_bound(5), cm.end());
}

TEST(map, lower_bound2)
{
	Map m;

	for (int i = 1; i < 4; i++) {
		m.insert(ft::make_pair(i, i));
	}
	Map::iterator it = m.begin();
	for (int i = 1; i < 4; ++i, ++it) {
		EXPECT_EQ(m.lower_bound(i), it);
	}
	EXPECT_EQ(m.lower_bound(-1), m.begin());
	EXPECT_EQ(m.lower_bound(0), m.begin());
	EXPECT_EQ(m.lower_bound(4), m.end());
	EXPECT_EQ(m.lower_bound(5), m.end());

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 4; ++i, ++cit) {
		EXPECT_EQ(cm.lower_bound(i), cit);
	}
	EXPECT_EQ(cm.lower_bound(-1), cm.begin());
	EXPECT_EQ(cm.lower_bound(0), cm.begin());
	EXPECT_EQ(cm.lower_bound(4), cm.end());
	EXPECT_EQ(cm.lower_bound(5), cm.end());
}

TEST(map, lower_bound3)
{
	Map m;

	for (int i = 1; i < 20; i++) {
		m.insert(ft::make_pair(i, i));
	}
	m.erase(10);
	Map::iterator it = m.begin();
	for (int i = 1; i <= 10; ++i, ++it) {
		EXPECT_EQ(m.lower_bound(i), it);
	}
	--it;
	for (int i = 11; i < 20; ++i, ++it) {
		EXPECT_EQ(m.lower_bound(i), it);
	}
	EXPECT_EQ(m.lower_bound(-1), m.begin());
	EXPECT_EQ(m.lower_bound(0), m.begin());
	EXPECT_EQ(m.lower_bound(19), --m.end());
	EXPECT_EQ(m.lower_bound(20), m.end());
	EXPECT_EQ(m.lower_bound(21), m.end());

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i <= 10; ++i, ++cit) {
		EXPECT_EQ(cm.lower_bound(i), cit);
	}
	--cit;
	for (int i = 11; i < 20; ++i, ++cit) {
		EXPECT_EQ(cm.lower_bound(i), cit);
	}
	EXPECT_EQ(cm.lower_bound(-1), cm.begin());
	EXPECT_EQ(cm.lower_bound(0), cm.begin());
	EXPECT_EQ(cm.lower_bound(19), --cm.end());
	EXPECT_EQ(cm.lower_bound(20), cm.end());
	EXPECT_EQ(cm.lower_bound(21), cm.end());
}

TEST(map, lower_bound4)
{
	Map m0;

	for (int i = 1; i <= 100; i++) {
		if (i % 2) {
			continue;
		}
		m0.insert(ft::make_pair(i, i));
	}
	{
		Map           m  = m0;
		Map::iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			ASSERT_EQ(m.lower_bound(i), it);
			if (!(i % 2)) {
				++it;
			}
		}
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			ASSERT_EQ(m.lower_bound(i), it);
			if (!(i % 2)) {
				++it;
			}
		}
	}
}

TEST(map, lower_bound_empty)
{
	Map m;

	EXPECT_EQ(m.lower_bound(0), m.end());
	EXPECT_EQ(m.lower_bound(-1), m.end());
	EXPECT_EQ(m.lower_bound(INT_MIN), m.end());
}

TEST(map, lower_bound_empty_const)
{
	const Map m;

	EXPECT_EQ(m.lower_bound(0), m.end());
	EXPECT_EQ(m.lower_bound(-1), m.end());
	EXPECT_EQ(m.lower_bound(INT_MIN), m.end());
}

TEST(map, upper_bound_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().upper_bound(1)), typeid(Map::iterator));
	EXPECT_EQ(typeid(m.upper_bound(1)), typeid(Map::const_iterator));
}

TEST(map, upper_bound)
{
	Map m0;

	m0.insert(ft::make_pair(1, 1));
	{
		Map m = m0;

		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(1), m.end());
		EXPECT_EQ(m.upper_bound(4), m.end());
		EXPECT_EQ(m.upper_bound(5), m.end());
	}
	{
		const Map m = m0;

		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(1), m.end());
		EXPECT_EQ(m.upper_bound(4), m.end());
		EXPECT_EQ(m.upper_bound(5), m.end());
	}
}

TEST(map, upper_bound2)
{
	Map m0;

	for (int i = 1; i < 4; i++) {
		m0.insert(ft::make_pair(i, i));
	}
	{
		Map m = m0;

		Map::iterator it = m.begin();
		for (int i = 1; i < 4; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(4), m.end());
		EXPECT_EQ(m.upper_bound(5), m.end());
	}
	{
		const Map m = m0;

		Map::const_iterator it = m.begin();
		for (int i = 1; i < 4; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(4), m.end());
		EXPECT_EQ(m.upper_bound(5), m.end());
	}
}

TEST(map, upper_bound3)
{
	Map m0;

	for (int i = 1; i < 20; i++) {
		m0.insert(ft::make_pair(i, i));
	}
	m0.erase(10);
	{
		Map           m  = m0;
		Map::iterator it = m.begin();
		for (int i = 1; i <= 9; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(10), it);
		for (int i = 11; i < 20; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(19), m.end());
		EXPECT_EQ(m.upper_bound(20), m.end());
		EXPECT_EQ(m.upper_bound(21), m.end());
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 9; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(10), it);
		for (int i = 11; i < 20; ++i) {
			EXPECT_EQ(m.upper_bound(i), ++it);
		}
		EXPECT_EQ(m.upper_bound(-1), m.begin());
		EXPECT_EQ(m.upper_bound(0), m.begin());
		EXPECT_EQ(m.upper_bound(19), m.end());
		EXPECT_EQ(m.upper_bound(20), m.end());
		EXPECT_EQ(m.upper_bound(21), m.end());
	}
}

TEST(map, upper_bound4)
{
	Map m0;

	for (int i = 1; i <= 100; i++) {
		if (i % 2) {
			continue;
		}
		m0.insert(ft::make_pair(i, i));
	}
	{
		Map           m  = m0;
		Map::iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			if (!(i % 2)) {
				++it;
			}
			ASSERT_EQ(m.upper_bound(i), it);
		}
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			if (!(i % 2)) {
				++it;
			}
			ASSERT_EQ(m.upper_bound(i), it);
		}
	}
}

TEST(map, upper_bound_empty)
{
	Map m;

	EXPECT_EQ(m.upper_bound(0), m.end());
	EXPECT_EQ(m.upper_bound(-1), m.end());
	EXPECT_EQ(m.upper_bound(INT_MIN), m.end());
}

// TODO const
TEST(map, upper_bound_empty_const)
{
	const Map m;

	EXPECT_EQ(m.upper_bound(0), m.end());
	EXPECT_EQ(m.upper_bound(-1), m.end());
	EXPECT_EQ(m.upper_bound(INT_MIN), m.end());
}
