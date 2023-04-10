#include "gtest.h"

#include <algorithm>
#include <cassert>
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

#if !defined(FT_TEST) && defined(__GLIBCXX__)
  #define FT_EXPECT_EQ(a, b) (a)
#else
  #define FT_EXPECT_EQ(a, b) EXPECT_EQ(a, b)
#endif

TEST(map, erase_types)
{
	Map m;

	m.insert(ft::make_pair(0, 1));
	EXPECT_EQ(typeid(m.erase(0)), typeid(Map::size_type));
#if !defined(FT_TEST) && defined(__GLIBCXX__)
	EXPECT_EQ(typeid(m.erase(m.end(), m.end())), typeid(void));
	EXPECT_EQ(typeid(m.erase(m.begin())), typeid(void));
#else
	EXPECT_EQ(typeid(m.erase(m.end(), m.end())), typeid(Map::iterator));
	EXPECT_EQ(typeid(m.erase(m.begin())), typeid(Map::iterator));
#endif
}

TEST(map, erase_empty)
{
	Map m;

	for (int i = 0; i < 32; i++) {
		EXPECT_EQ(m.erase(i), 0U);
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	FT_EXPECT_EQ(m.erase(m.begin(), m.end()), m.end());
	EXPECT_EQ(m.size(), 0U);
	EXPECT_TRUE(m.empty());

	FT_EXPECT_EQ(m.erase(m.begin(), m.begin()), m.end());
	EXPECT_EQ(m.size(), 0U);
	EXPECT_TRUE(m.empty());

	FT_EXPECT_EQ(m.erase(m.end(), m.end()), m.end());
	EXPECT_EQ(m.size(), 0U);
	EXPECT_TRUE(m.empty());
}

TEST(map, erase1)
{
	Map m0;

	m0.insert(ft::make_pair(0, 1));
	{
		Map m = m0;

		EXPECT_EQ(m.erase(1), 0U);
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.end(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.begin()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
}

TEST(map, erase2)
{
	Map m0;
	for (int i = 0; i < 3; i++) {
		m0.insert(ft::make_pair(i, 1));
	}
	{
		Map m = m0;

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(1), 1U);
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(2), 1U);
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
}

TEST(map, erase3)
{
	Map m0;
	for (int i = 0; i < 3; i++) {
		m0.insert(ft::make_pair(i, 1));
	}
	{
		Map m = m0;

		EXPECT_EQ(m.erase(2), 1U);
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(1), 1U);
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(--m.end()), m.end());
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(--m.end()), m.end());
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(--m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(--m.end(), m.end()), m.end());
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(--m.end(), m.end()), m.end());
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(--m.end(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
}

TEST(map, erase4)
{
	Map m0;
	for (int i = 0; i < 3; i++) {
		m0.insert(ft::make_pair(i, 1));
	}
	{
		Map m = m0;

		EXPECT_EQ(m.erase(1), 1U);
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(2), 1U);
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		EXPECT_EQ(m.erase(0), 1U);
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.find(1)), m.find(2));
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.find(2)), m.end());
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.find(0)), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.find(1), ++m.find(1)), ++m.find(1));
		EXPECT_EQ(m.find(1), m.end());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.find(2), ++m.find(2)), ++m.find(2));
		EXPECT_EQ(m.find(2), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.find(0), ++m.find(0)), ++m.find(0));
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), ++m.begin()), ++m.begin());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
}

TEST(map, erase5)
{
	Map m0;
	for (int i = 0; i < 3; i++) {
		m0.insert(ft::make_pair(i, 1));
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(m.begin(), --m.end()), --m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		m.insert(ft::make_pair(0, 1));
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
	{
		Map m = m0;

		FT_EXPECT_EQ(m.erase(++m.begin(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.begin());
		EXPECT_EQ(m.size(), 1U);
		EXPECT_FALSE(m.empty());

		m.insert(ft::make_pair(1, 1));
		EXPECT_EQ(m.find(1), ++m.begin());
		EXPECT_EQ(m.size(), 2U);
		EXPECT_FALSE(m.empty());

		FT_EXPECT_EQ(m.erase(m.begin(), m.end()), m.end());
		EXPECT_EQ(m.find(0), m.end());
		EXPECT_EQ(m.size(), 0U);
		EXPECT_TRUE(m.empty());
	}
}

TEST(map, erase6)
{
	Map              m0;
	std::vector<int> v;
	int              size = 128;
	for (int i = 0; i < size; i++) {
		m0.insert(ft::make_pair(i, 1));
		v.push_back(i);
	}
	for (size_t i = 0; i < 10; i++) {
		std::random_shuffle(v.begin(), v.end());
		{
			Map    m  = m0;
			size_t sz = size;
			for (int i = 0; i < size; i++) {
				ASSERT_EQ(m.erase(v[i]), 1U);
				ASSERT_EQ(m.find(v[i]), m.end());
				ASSERT_EQ(m.size(), --sz);
			}
		}
		{
			Map    m  = m0;
			size_t sz = size;
			for (int i = 0; i < size; i++) {
				FT_EXPECT_EQ(m.erase(m.find(v[i])), ++m.find(v[i]));
				ASSERT_EQ(m.find(v[i]), m.end());
				ASSERT_EQ(m.size(), --sz);
			}
		}
		{
			Map    m  = m0;
			size_t sz = size;
			for (int i = 0; i < size; i++) {
				Map::iterator it   = m.find(v[i]);
				Map::iterator next = ++Map::iterator(it);
				FT_EXPECT_EQ(m.erase(it, next), next);
				ASSERT_EQ(m.find(v[i]), m.end());
				ASSERT_EQ(m.size(), --sz);
			}
		}
	}
}

TEST(map, erase7)
{
	Map              m0;
	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> v3;
	std::vector<int> v4;
	int              size = 128;
	assert(size >= 4);
	for (int i = 0; i < size; i++) {
		m0.insert(ft::make_pair(i, 1));
	}
	int quarter = size / 4;
	for (int i = 0; (int)v1.size() < quarter; i++) {
		v1.push_back(i);
	}
	for (int i = v1.back() + 1; (int)v2.size() < quarter; i++) {
		v2.push_back(i);
	}
	for (int i = v2.back() + 1; (int)v3.size() < quarter; i++) {
		v3.push_back(i);
	}
	for (int i = v3.back() + 1; (int)v4.size() < size - quarter * 3; i++) {
		v4.push_back(i);
	}
	{
		Map    m  = m0;
		size_t sz = size;
		{
			Map::iterator first = m.find(v1.front());
			Map::iterator last  = ++m.find(v1.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v1.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v1.size(); i++) {
				ASSERT_EQ(m.find(v1[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v2.front());
			Map::iterator last  = ++m.find(v2.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v2.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v2.size(); i++) {
				ASSERT_EQ(m.find(v2[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v3.front());
			Map::iterator last  = ++m.find(v3.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v3.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v3.size(); i++) {
				ASSERT_EQ(m.find(v3[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v4.front());
			Map::iterator last  = ++m.find(v4.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v4.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v4.size(); i++) {
				ASSERT_EQ(m.find(v4[i]), m.end());
			}
		}
	}
	{
		Map    m  = m0;
		size_t sz = size;
		{
			Map::iterator first = m.find(v4.front());
			Map::iterator last  = ++m.find(v4.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v4.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v4.size(); i++) {
				ASSERT_EQ(m.find(v4[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v3.front());
			Map::iterator last  = ++m.find(v3.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v3.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v3.size(); i++) {
				ASSERT_EQ(m.find(v3[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v2.front());
			Map::iterator last  = ++m.find(v2.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v2.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v2.size(); i++) {
				ASSERT_EQ(m.find(v2[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v1.front());
			Map::iterator last  = ++m.find(v1.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v1.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v1.size(); i++) {
				ASSERT_EQ(m.find(v1[i]), m.end());
			}
		}
	}
	{
		Map    m  = m0;
		size_t sz = size;
		{
			Map::iterator first = m.find(v3.front());
			Map::iterator last  = ++m.find(v3.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v3.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v3.size(); i++) {
				ASSERT_EQ(m.find(v3[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v4.front());
			Map::iterator last  = ++m.find(v4.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v4.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v4.size(); i++) {
				ASSERT_EQ(m.find(v4[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v2.front());
			Map::iterator last  = ++m.find(v2.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v2.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v2.size(); i++) {
				ASSERT_EQ(m.find(v2[i]), m.end());
			}
		}
		{
			Map::iterator first = m.find(v1.front());
			Map::iterator last  = ++m.find(v1.back());
			FT_EXPECT_EQ(m.erase(first, last), last);
			sz -= v1.size();
			EXPECT_EQ(m.size(), sz);
			for (int i = 0; i < (int)v1.size(); i++) {
				ASSERT_EQ(m.find(v1[i]), m.end());
			}
		}
	}
}
