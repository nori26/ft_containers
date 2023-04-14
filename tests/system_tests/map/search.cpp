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

TEST(map, find)
{
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.find(0), m.end());
	EXPECT_EQ(m.find(1), m.begin());
	EXPECT_EQ(m.find(2), m.end());

	const Map cm = m;

	EXPECT_EQ(cm.find(0), cm.end());
	EXPECT_EQ(cm.find(1), cm.begin());
	EXPECT_EQ(cm.find(2), cm.end());
}

TEST(map, find2)
{
	Map m;

	for (int i = 1; i < 4; i++) {
		m.insert(ft::make_pair(i, i));
	}
	Map::iterator it = m.begin();
	for (int i = 1; i < 4; ++i, ++it) {
		EXPECT_EQ(m.find(i), it);
	}
	EXPECT_EQ(m.find(-1), m.end());
	EXPECT_EQ(m.find(0), m.end());
	EXPECT_EQ(m.find(4), m.end());
	EXPECT_EQ(m.find(5), m.end());

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 4; ++i, ++cit) {
		EXPECT_EQ(cm.find(i), cit);
	}
	EXPECT_EQ(cm.find(-1), cm.end());
	EXPECT_EQ(cm.find(0), cm.end());
	EXPECT_EQ(cm.find(4), cm.end());
	EXPECT_EQ(cm.find(5), cm.end());
}

TEST(map, find3)
{
	Map m;

	for (int i = 1; i < 20; i++) {
		m.insert(ft::make_pair(i, i));
	}
	m.erase(10);
	Map::iterator it = m.begin();
	for (int i = 1; i <= 9; ++i, ++it) {
		EXPECT_EQ(m.find(i), it);
	}
	EXPECT_EQ(m.find(10), m.end());
	for (int i = 11; i < 20; ++i, ++it) {
		EXPECT_EQ(m.find(i), it);
	}
	EXPECT_EQ(m.find(-1), m.end());
	EXPECT_EQ(m.find(0), m.end());
	EXPECT_EQ(m.find(19), --m.end());
	EXPECT_EQ(m.find(20), m.end());
	EXPECT_EQ(m.find(21), m.end());

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 10; ++i, ++cit) {
		EXPECT_EQ(cm.find(i), cit);
	}
	EXPECT_EQ(cm.find(10), cm.end());
	for (int i = 11; i < 20; ++i, ++cit) {
		EXPECT_EQ(cm.find(i), cit);
	}
	EXPECT_EQ(cm.find(-1), cm.end());
	EXPECT_EQ(cm.find(0), cm.end());
	EXPECT_EQ(cm.find(19), --cm.end());
	EXPECT_EQ(cm.find(20), cm.end());
	EXPECT_EQ(cm.find(21), cm.end());
}

TEST(map, find4)
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
				ASSERT_EQ(m.find(i), it);
				++it;
			} else {
				ASSERT_EQ(m.find(i), m.end());
			}
		}
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			if (!(i % 2)) {
				ASSERT_EQ(m.find(i), it);
				++it;
			} else {
				ASSERT_EQ(m.find(i), m.end());
			}
		}
	}
}

TEST(map, find_empty)
{
	Map m;

	EXPECT_EQ(m.find(0), m.end());
	EXPECT_EQ(m.find(-1), m.end());
	EXPECT_EQ(m.find(INT_MIN), m.end());
}

TEST(map, find_empty_const)
{
	const Map m;

	EXPECT_EQ(m.find(0), m.end());
	EXPECT_EQ(m.find(-1), m.end());
	EXPECT_EQ(m.find(INT_MIN), m.end());
}

TEST(map, equal_range_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().equal_range(1)), typeid(ft::pair<Map::iterator, Map::iterator>));
	EXPECT_EQ(typeid(m.equal_range(1)), typeid(ft::pair<Map::const_iterator, Map::const_iterator>));
}

TEST(map, equal_range)
{
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
	EXPECT_EQ(m.equal_range(1), ft::make_pair(m.begin(), m.end()));
	EXPECT_EQ(m.equal_range(2), ft::make_pair(m.end(), m.end()));

	const Map cm = m;

	EXPECT_EQ(cm.equal_range(0), ft::make_pair(cm.begin(), cm.begin()));
	EXPECT_EQ(cm.equal_range(1), ft::make_pair(cm.begin(), cm.end()));
	EXPECT_EQ(cm.equal_range(2), ft::make_pair(cm.end(), cm.end()));
}

TEST(map, equal_range2)
{
	Map m;

	for (int i = 1; i < 4; i++) {
		m.insert(ft::make_pair(i, i));
	}
	Map::iterator it = m.begin();
	for (int i = 1; i < 4; ++i) {
		Map::iterator prev = it++;
		ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
	}
	EXPECT_EQ(m.equal_range(-1), ft::make_pair(m.begin(), m.begin()));
	EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
	EXPECT_EQ(m.equal_range(4), ft::make_pair(m.end(), m.end()));
	EXPECT_EQ(m.equal_range(5), ft::make_pair(m.end(), m.end()));

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 4; ++i) {
		Map::const_iterator prev = cit++;
		ASSERT_EQ(cm.equal_range(i), ft::make_pair(prev, cit));
	}
	EXPECT_EQ(cm.equal_range(-1), ft::make_pair(cm.begin(), cm.begin()));
	EXPECT_EQ(cm.equal_range(0), ft::make_pair(cm.begin(), cm.begin()));
	EXPECT_EQ(cm.equal_range(4), ft::make_pair(cm.end(), cm.end()));
	EXPECT_EQ(cm.equal_range(5), ft::make_pair(cm.end(), cm.end()));
}

TEST(map, equal_range3)
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
			Map::iterator prev = it++;
			ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
		}
		EXPECT_EQ(m.equal_range(10), ft::make_pair(it, it));
		for (int i = 11; i < 20; ++i) {
			Map::iterator prev = it++;
			ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
		}
		EXPECT_EQ(m.equal_range(-1), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(19), ft::make_pair(--m.end(), m.end()));
		EXPECT_EQ(m.equal_range(20), ft::make_pair(m.end(), m.end()));
		EXPECT_EQ(m.equal_range(21), ft::make_pair(m.end(), m.end()));
	}
	{
		const Map m = m0;

		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 9; ++i) {
			Map::const_iterator prev = it++;
			ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
		}
		EXPECT_EQ(m.equal_range(10), ft::make_pair(it, it));
		for (int i = 11; i < 20; ++i) {
			Map::const_iterator prev = it++;
			ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
		}
		EXPECT_EQ(m.equal_range(-1), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(19), ft::make_pair(--m.end(), m.end()));
		EXPECT_EQ(m.equal_range(20), ft::make_pair(m.end(), m.end()));
		EXPECT_EQ(m.equal_range(21), ft::make_pair(m.end(), m.end()));
	}
}

TEST(map, equal_range4)
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
				Map::iterator prev = it++;
				ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
			} else {
				ASSERT_EQ(m.equal_range(i), ft::make_pair(it, it));
			}
		}
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			if (!(i % 2)) {
				Map::const_iterator prev = it++;
				ASSERT_EQ(m.equal_range(i), ft::make_pair(prev, it));
			} else {
				ASSERT_EQ(m.equal_range(i), ft::make_pair(it, it));
			}
		}
	}
}

TEST(map, equal_range_empty)
{
	Map m;

	EXPECT_EQ(m.equal_range(0), ft::make_pair(m.end(), m.end()));
	EXPECT_EQ(m.equal_range(-1), ft::make_pair(m.end(), m.end()));
	EXPECT_EQ(m.equal_range(INT_MIN), ft::make_pair(m.end(), m.end()));
}

TEST(map, equal_range_empty_const)
{
	const Map m;

	EXPECT_EQ(m.equal_range(0), ft::make_pair(m.end(), m.end()));
	EXPECT_EQ(m.equal_range(-1), ft::make_pair(m.end(), m.end()));
	EXPECT_EQ(m.equal_range(INT_MIN), ft::make_pair(m.end(), m.end()));
}

TEST(map, equal_range5)
{
	Map m0;

	for (int i = 1; i <= 100; i++) {
		m0.insert(ft::make_pair(1, i));
	}
	{
		Map m = m0;
		EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(1), ft::make_pair(m.begin(), m.end()));
		EXPECT_EQ(m.equal_range(2), ft::make_pair(m.end(), m.end()));
	}
	{
		const Map m = m0;
		EXPECT_EQ(m.equal_range(0), ft::make_pair(m.begin(), m.begin()));
		EXPECT_EQ(m.equal_range(1), ft::make_pair(m.begin(), m.end()));
		EXPECT_EQ(m.equal_range(2), ft::make_pair(m.end(), m.end()));
	}
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

TEST(map, count_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().count(1)), typeid(Map::size_type));
	EXPECT_EQ(typeid(m.count(1)), typeid(Map::size_type));
}

TEST(map, count)
{
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.count(0), 0U);
	EXPECT_EQ(m.count(1), 1U);
	EXPECT_EQ(m.count(2), 0U);

	const Map cm = m;

	EXPECT_EQ(cm.count(0), 0U);
	EXPECT_EQ(cm.count(1), 1U);
	EXPECT_EQ(cm.count(2), 0U);
}

TEST(map, count2)
{
	Map m;

	for (int i = 1; i < 4; i++) {
		m.insert(ft::make_pair(i, i));
	}
	Map::iterator it = m.begin();
	for (int i = 1; i < 4; ++i, ++it) {
		EXPECT_EQ(m.count(i), 1U);
	}
	EXPECT_EQ(m.count(-1), 0U);
	EXPECT_EQ(m.count(0), 0U);
	EXPECT_EQ(m.count(4), 0U);
	EXPECT_EQ(m.count(5), 0U);

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 4; ++i, ++cit) {
		EXPECT_EQ(cm.count(i), 1U);
	}
	EXPECT_EQ(cm.count(-1), 0U);
	EXPECT_EQ(cm.count(0), 0U);
	EXPECT_EQ(cm.count(4), 0U);
	EXPECT_EQ(cm.count(5), 0U);
}

TEST(map, count3)
{
	Map m;

	for (int i = 1; i < 20; i++) {
		m.insert(ft::make_pair(i, i));
	}
	m.erase(10);
	Map::iterator it = m.begin();
	for (int i = 1; i <= 9; ++i, ++it) {
		EXPECT_EQ(m.count(i), 1U);
	}
	EXPECT_EQ(m.count(10), 0U);
	for (int i = 11; i < 20; ++i, ++it) {
		EXPECT_EQ(m.count(i), 1U);
	}
	EXPECT_EQ(m.count(-1), 0U);
	EXPECT_EQ(m.count(0), 0U);
	EXPECT_EQ(m.count(19), 1U);
	EXPECT_EQ(m.count(20), 0U);
	EXPECT_EQ(m.count(21), 0U);

	const Map cm = m;

	Map::const_iterator cit = cm.begin();
	for (int i = 1; i < 10; ++i, ++cit) {
		EXPECT_EQ(cm.count(i), 1U);
	}
	EXPECT_EQ(cm.count(10), 0U);
	for (int i = 11; i < 20; ++i, ++cit) {
		EXPECT_EQ(cm.count(i), 1U);
	}
	EXPECT_EQ(cm.count(-1), 0U);
	EXPECT_EQ(cm.count(0), 0U);
	EXPECT_EQ(cm.count(19), 1U);
	EXPECT_EQ(cm.count(20), 0U);
	EXPECT_EQ(cm.count(21), 0U);
}

TEST(map, count4)
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
				ASSERT_EQ(m.count(i), 1U);
				++it;
			} else {
				ASSERT_EQ(m.count(i), 0U);
			}
		}
	}
	{
		const Map           m  = m0;
		Map::const_iterator it = m.begin();
		for (int i = 1; i <= 100; ++i) {
			if (!(i % 2)) {
				ASSERT_EQ(m.count(i), 1U);
				++it;
			} else {
				ASSERT_EQ(m.count(i), 0U);
			}
		}
	}
}

TEST(map, count5)
{
	Map m0;

	for (int i = 1; i <= 100; i++) {
		m0.insert(ft::make_pair(1, i));
	}
	{
		Map m = m0;
		EXPECT_EQ(m.count(0), 0U);
		EXPECT_EQ(m.count(1), 1U);
		EXPECT_EQ(m.count(2), 0U);
	}
	{
		const Map m = m0;
		EXPECT_EQ(m.count(0), 0U);
		EXPECT_EQ(m.count(1), 1U);
		EXPECT_EQ(m.count(2), 0U);
	}
}

TEST(map, count_empty)
{
	Map m;

	EXPECT_EQ(m.count(0), 0U);
	EXPECT_EQ(m.count(-1), 0U);
	EXPECT_EQ(m.count(INT_MIN), 0U);
}

TEST(map, count_empty_const)
{
	const Map m;

	EXPECT_EQ(m.count(0), 0U);
	EXPECT_EQ(m.count(-1), 0U);
	EXPECT_EQ(m.count(INT_MIN), 0U);
}
