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

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, size_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().size()), typeid(Map::size_type));
	EXPECT_EQ(typeid(m.size()), typeid(Map::size_type));
}

TEST(map, size)
{
	Map        m;
	const Map &cm = m;

	EXPECT_EQ(m.size(), 0U);
	EXPECT_EQ(cm.size(), 0U);
	m.erase(0);
	EXPECT_EQ(m.size(), 0U);
	EXPECT_EQ(cm.size(), 0U);
	m.erase(m.begin(), m.end());
	EXPECT_EQ(m.size(), 0U);
	EXPECT_EQ(cm.size(), 0U);
	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.size(), 1U);
	EXPECT_EQ(cm.size(), 1U);
	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.size(), 1U);
	EXPECT_EQ(cm.size(), 1U);
	m.insert(ft::make_pair(2, 1));
	EXPECT_EQ(m.size(), 2U);
	EXPECT_EQ(cm.size(), 2U);
	m.erase(1);
	EXPECT_EQ(m.size(), 1U);
	EXPECT_EQ(cm.size(), 1U);
	m.erase(1);
	EXPECT_EQ(m.size(), 1U);
	EXPECT_EQ(cm.size(), 1U);
	m.insert(ft::make_pair(2, 1));
	EXPECT_EQ(m.size(), 1U);
	EXPECT_EQ(cm.size(), 1U);
	m.insert(ft::make_pair(1, 1));
	EXPECT_EQ(m.size(), 2U);
	EXPECT_EQ(cm.size(), 2U);
}

TEST(map, size2)
{
	Map base;

	for (int i = 0; i < 3; i++) {
		base.insert(ft::make_pair(i, 1));
	}
	{
		Map        m(base);
		const Map &cm = m;

		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
	}
	{
		Map        m(base.begin(), base.end());
		const Map &cm = m;

		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
	}
	{
		Map        m(base.begin(), base.end());
		const Map &cm = m;

		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
	}
	{
		Map        m;
		const Map &cm = m;

		m.insert(base.begin(), base.end());
		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
		m.erase(m.begin(), m.begin());
		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
		m.erase(m.begin(), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(cm.size(), 0U);
		m.insert(base.end(), base.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(cm.size(), 0U);
		m.insert(base.begin(), base.end());
		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
	}
	{
		Map        m;
		const Map &cm = m;

		m.insert(base.begin(), base.end());
		EXPECT_EQ(m.size(), base.size());
		EXPECT_EQ(cm.size(), base.size());
		m.clear();
		EXPECT_EQ(m.size(), 0U);
		EXPECT_EQ(cm.size(), 0U);
	}
}

TEST(map, empty_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().empty()), typeid(bool));
	EXPECT_EQ(typeid(m.empty()), typeid(bool));
}

TEST(map, empty)
{
	Map        m;
	const Map &cm = m;

	EXPECT_TRUE(m.empty());
	EXPECT_TRUE(cm.empty());
	m.insert(ft::make_pair(1, 1));
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
	m.insert(ft::make_pair(1, 1));
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
	m.insert(ft::make_pair(2, 1));
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
	m.erase(1);
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
	m.erase(0);
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
	m.erase(2);
	EXPECT_TRUE(m.empty());
	EXPECT_TRUE(cm.empty());
	m.insert(ft::make_pair(1, 1));
	EXPECT_FALSE(m.empty());
	EXPECT_FALSE(cm.empty());
}

TEST(map, max_size_types)
{
	const Map m;

	EXPECT_EQ(typeid(Map().max_size()), typeid(Map::size_type));
	EXPECT_EQ(typeid(m.max_size()), typeid(Map::size_type));
}

// nodeのallocatorがないと判定できないので、メソッドの存在だけ確認
TEST(map, max_size)
{
	{
		Map m;

		EXPECT_LT(m.max_size(), m.get_allocator().max_size());
	}
	{
		const Map m;

		EXPECT_LT(m.max_size(), m.get_allocator().max_size());
	}
}
