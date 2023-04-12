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

typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator<ValueType> > Map;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, elem_access_types)
{
	Map m0;

	m0.insert(ft::make_pair(0, 0));
	{
		Map m = m0;

		EXPECT_EQ(typeid(ftc::Data &), typeid(m[0]));
		EXPECT_EQ(typeid(ftc::Data &), typeid(m.at(0)));

		ftc::Data &ref1 = m[0];
		ftc::Data &ref2 = m.at(0);
		EXPECT_EQ(&ref1, &m[0]);
		EXPECT_EQ(&ref2, &m.at(0));
	}
	{
		const Map m = m0;

		EXPECT_EQ(typeid(const ftc::Data &), typeid(m.at(0))); // あんま意味ない

		const ftc::Data &ref2 = m.at(0);
		EXPECT_EQ(&ref2, &m.at(0));
	}
}

TEST(map, at_empty)
{
	{
		Map m;

		EXPECT_THROW(m.at(0), std::out_of_range);
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.begin(), m.end());
	}
	{
		const Map m;

		EXPECT_THROW(m.at(0), std::out_of_range);
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.begin(), m.end());
	}
}

TEST(map, at)
{
	std::vector<int> vk;
	std::vector<int> vv;
	int              size = 128;
	for (int i = 0; i < size; i++) {
		vk.push_back(i);
		vv.push_back(i);
	}
	for (int i = 0; i < 10; i++) {
		std::random_shuffle(vk.begin(), vk.end());
		std::random_shuffle(vv.begin(), vv.end());
		std::vector<ValueType> v;
		v.reserve(size);
		for (int i = 0; i < size; i++) {
			v.push_back(ValueType(vk[i], vv[i]));
		}
		{
			Map m(v.begin(), v.end());

			for (std::vector<ValueType>::iterator it = v.begin(); it != v.end(); ++it) {
				EXPECT_EQ(m.at(it->first), it->second);
			}
			EXPECT_THROW(m.at(size), std::out_of_range);
			EXPECT_EQ(m.size(), v.size());
			EXPECT_EQ(m.begin()->first, 0);
			for (std::vector<ValueType>::iterator it = v.begin(); it != v.end(); ++it) {
				m.at(it->first) = it->first;
			}
			for (std::vector<ValueType>::iterator it = v.begin(); it != v.end(); ++it) {
				EXPECT_EQ(m.at(it->first), it->first);
			}
			EXPECT_EQ(m.size(), v.size());
			EXPECT_EQ(m.begin()->first, 0);
		}
		{
			const Map m(v.begin(), v.end());

			for (std::vector<ValueType>::iterator it = v.begin(); it != v.end(); ++it) {
				EXPECT_EQ(m.at(it->first), it->second);
			}
			EXPECT_THROW(m.at(size), std::out_of_range);
			EXPECT_EQ(m.size(), v.size());
			EXPECT_EQ(m.begin()->first, 0);
		}
	}
}
