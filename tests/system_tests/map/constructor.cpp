#include "gtest.h"

#include <climits>
#include <functional>
#include <list>
#include <sstream>
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

typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator<ValueType> > Map;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))
TEST(map, default_constructor)
{
	Map m;

	EXPECT_TRUE(m.empty());
	EXPECT_EQ(m.size(), 0U);
}

TEST(map, constructor_cmp)
{
	const MapCmp<ftc::Data>         c;
	const ftc::Allocator<ftc::Data> a;
	Map                             v = Map(c);

	EXPECT_TRUE(v.empty());
	v.insert(ft::make_pair(0, 1));
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.key_comp().id, c.id);
}

TEST(map, constructor_alloc)
{
	const MapCmp<ftc::Data>         c;
	const ftc::Allocator<ftc::Data> a;
	Map                             v = Map(c, a);

	EXPECT_TRUE(v.empty());
	v.insert(ft::make_pair(0, 1));
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
	EXPECT_EQ(v.key_comp().id, c.id);
}

TEST(map, copy_constructor_empty)
{
	Map v;
	Map v2 = v;

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v.get_allocator().get_id(), v2.get_allocator().get_id());
	EXPECT_EQ(v2.key_comp().id, v.key_comp().id);
}

TEST(map, copy_constructor2)
{
	Map v1;
	v1.insert(ft::make_pair(0, 1));

	Map v2 = v1;
	v1[0]  = 0;
	EXPECT_NE(v1[0], v2[0]);
	EXPECT_EQ(v1.get_allocator().get_id(), v2.get_allocator().get_id());
	EXPECT_EQ(v2.key_comp().id, v1.key_comp().id);
}

TEST(map, copy_constructor3)
{
	ValueType a1[] = {ft::make_pair(1, 1), ft::make_pair(2, 1), ft::make_pair(3, 1)};
	Map       v1(a1, a1 + ARRAY_SIZE(a1));

	Map           v2(v1);
	Map::iterator it = v1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it, a1[i]);
		++it;
	}
	it = v2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it, a1[i]);
		++it;
	}
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.get_allocator().get_id(), v2.get_allocator().get_id());
	EXPECT_EQ(v2.key_comp().id, v1.key_comp().id);
}

TEST(map, range_constructor_empty)
{
	Map v;
	Map v2(v.begin(), v.end());

	EXPECT_EQ(v2.size(), 0U);
}

TEST(map, range_constructor_empty2)
{
	const MapCmp<ftc::Data> c;
	std::vector<ValueType>  v;
	Map                     v2(v.begin(), v.end(), c);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.key_comp().id, c.id);
}

TEST(map, range_constructor_empty3)
{
	const MapCmp<ftc::Data>         c;
	const ftc::Allocator<ftc::Data> a;
	std::vector<ValueType>          v;
	Map                             v2(v.begin(), v.end(), c, a);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
	EXPECT_EQ(v2.key_comp().id, c.id);
}

TEST(map, range_constructor)
{
	ValueType a1[] = {ft::make_pair(1, 1), ft::make_pair(2, 1), ft::make_pair(3, 1)};
	Map       v1(a1, a1 + ARRAY_SIZE(a1));

	Map::iterator it = v1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it, a1[i]);
		++it;
	}
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
}

TEST(map, range_constructor_bidirectional_iter_empty)
{
	std::list<ValueType> v;
	Map                  v2(v.begin(), v.end());

	EXPECT_EQ(v2.size(), 0U);
}

TEST(map, range_constructor_bidirectional_iter_empty2)
{
	const ftc::Allocator<ftc::Data> a;
	const MapCmp<ftc::Data>         c;
	std::list<ValueType>            v;
	Map                             v2(v.begin(), v.end(), c, a);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
	EXPECT_EQ(v2.key_comp().id, c.id);
}

TEST(map, range_constructor_bidirectional_iter4)
{
	ValueType            a1[] = {ft::make_pair(1, 1), ft::make_pair(2, 1), ft::make_pair(3, 1)};
	std::list<ValueType> v1(a1, a1 + ARRAY_SIZE(a1));

	Map v2(v1.begin(), v1.end());
	Map::iterator it = v2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(*it, a1[i]);
		++it;
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
}
