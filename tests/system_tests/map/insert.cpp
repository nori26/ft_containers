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
typedef ft::pair<const ftc::Data, ftc::Data> ValueType;
typedef ft::map<ftc::Data, ftc::Data, std::less<ftc::Data>, ftc::Allocator<ValueType> > Map;
// typedef ft::map<ftc::Data, int> Map;
// typedef ft::map<int, int> Map;
typedef ft::pair<Map::iterator, bool> Pair;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

class MvGen
{
  public:
	typedef std::vector<int> DataSet;

	static const size_t         kSize = 10;
	static DataSet              map_values;
	static std::vector<DataSet> map_values_set;

  private:
	static bool used[kSize];
	class Init
	{
	  public:
		Init()
		{
			map_values.resize(kSize);
			map_values_set.reserve(3630000);
			dfs(0);
		}

		static void dfs(size_t depth)
		{
			if (depth == kSize) {
				map_values_set.push_back(map_values);
				return;
			}
			for (size_t i = 0; i < kSize; i++) {
				if (used[i]) {
					continue;
				}
				map_values[depth] = i;
				used[i]           = true;
				dfs(depth + 1);
				used[i] = false;
			}
		}
	};

  public:
	MvGen()
	{
		static Init ini;
	}
};

const size_t                MvGen::kSize;
bool                        MvGen::used[MvGen::kSize] = {};
MvGen::DataSet              MvGen::map_values;
std::vector<MvGen::DataSet> MvGen::map_values_set;

TEST(map, insert)
{
	Map m;
	{
		Pair p = m.insert(ft::make_pair(1, 1));
		EXPECT_EQ(p.first, m.begin());
		EXPECT_TRUE(p.second);
		EXPECT_EQ(m.size(), 1U);
		EXPECT_EQ(*m.begin(), Map::value_type(ft::make_pair(1, 1)));
	}
	{
		Pair p = m.insert(ft::make_pair(1, 2));
		EXPECT_EQ(p.first, m.begin());
		EXPECT_FALSE(p.second);
		EXPECT_EQ(m.size(), 1U);
		EXPECT_EQ(*m.begin(), Map::value_type(ft::make_pair(1, 1)));
	}
}

// TEST(map, insert_brute_force)
// {
// 	MvGen mv;
// 	for (size_t i = 0; i < MvGen::map_values_set.size(); i++) {
// 		Map             m;
// 		MvGen::DataSet &v = MvGen::map_values_set[i];
// 		for (size_t j = 0; j < v.size(); j++) {
// 			m.insert(ft::make_pair(v[j], v[j]));
// 		}
// 		Map::iterator it = m.begin();
// 		ASSERT_EQ(m.size(), v.size());
// 		for (int j = 0; j < (int)m.size(); j++, ++it) {
// 			ASSERT_EQ(*it, Map::value_type(ft::make_pair(j, j)));
// 		}
// 		if (!(i % (MvGen::map_values_set.size() / 10))) {
// 			std::cout << i << " ok" << std::endl;
// 		}
// 	}
// }

// TEST(map, insert_2)
// {
// 	MvGen mv;
// 	Map   m;
// 	m.insert(ft::make_pair(1, 1));
// }

// TEST(map, insert_huge)
// {
// 	Map m;
// 	for (int i = 0; i < INT_MAX / 100; i++) {
// 		m.insert(ft::make_pair(i, i));
// 		if (!(i % 1000000U)) {
// 			std::cout << i << std::endl;
// 		}
// 	}
// 	for (int i = 0; i < INT_MAX / 100; i++) {
// 		m.erase(i);
// 		if (!(i % 1000000U)) {
// 			std::cout << m.size() << std::endl;
// 		}
// 	}
// }

// TEST(map, insert_const)
// {
// 	const Map   m;
// 	// m.test();
// }
