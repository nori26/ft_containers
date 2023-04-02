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
typedef ft::map<ftc::Data, ftc::Data> Map;
typedef ft::pair<Map::iterator, bool> Pair;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, size)
{
	Map m;

	EXPECT_EQ(m.size(), 0U);
	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.size(), 1U);
	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.size(), 1U);
	m.insert(ft::make_pair(2, 1));
	EXPECT_EQ(m.size(), 2U);
}

// TODO range construct
TEST(map, size_const)
{
	const Map m;

	EXPECT_EQ(m.size(), 0U);
}

TEST(map, empty)
{
	Map m;

	EXPECT_TRUE(m.empty());
	m.insert(ft::make_pair(1, 1));
	EXPECT_FALSE(m.empty());
	m.insert(ft::make_pair(1, 1));
	EXPECT_FALSE(m.empty());
	m.insert(ft::make_pair(2, 1));
	EXPECT_FALSE(m.empty());
	m.erase(1);
	EXPECT_FALSE(m.empty());
	m.erase(0);
	EXPECT_FALSE(m.empty());
	m.erase(2);
	EXPECT_TRUE(m.empty());
}

// TODO range construct
TEST(map, empty_const)
{
	const Map m;

	EXPECT_TRUE(m.empty());
}

// nodeのallocatorがないと判定できないので、メソッドの存在だけ確認
TEST(map, max_size)
{
	Map m;

	EXPECT_LT(m.max_size(), m.get_allocator().max_size());
}

TEST(map, max_size_const)
{
	const Map m;

	EXPECT_LT(m.max_size(), m.get_allocator().max_size());
}
