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

// TODO const
TEST(map, lower_bound)
{
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.lower_bound(-1), m.begin());
	EXPECT_EQ(m.lower_bound(0), m.begin());
	EXPECT_EQ(m.lower_bound(1), m.begin());
	EXPECT_EQ(m.lower_bound(4), m.end());
	EXPECT_EQ(m.lower_bound(5), m.end());
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
	Map m;

	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.upper_bound(-1), m.begin());
	EXPECT_EQ(m.upper_bound(0), m.begin());
	EXPECT_EQ(m.upper_bound(1), m.end());
	EXPECT_EQ(m.upper_bound(4), m.end());
	EXPECT_EQ(m.upper_bound(5), m.end());
}

TEST(map, upper_bound2)
{
	Map m;

	for (int i = 1; i < 4; i++) {
		m.insert(ft::make_pair(i, i));
	}
	Map::iterator it = m.begin();
	for (int i = 1; i < 4; ++i) {
		EXPECT_EQ(m.upper_bound(i), ++it);
	}
	EXPECT_EQ(m.upper_bound(-1), m.begin());
	EXPECT_EQ(m.upper_bound(0), m.begin());
	EXPECT_EQ(m.upper_bound(4), m.end());
	EXPECT_EQ(m.upper_bound(5), m.end());
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
