#include "gtest.h"

#include <functional>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"
#include "vector_fixture.hpp"

#ifdef FT_TEST
  #include "map.hpp"
#else
  #include <map>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

struct DerivedValCmp : public ft::map<int, int>::value_compare
{
	DerivedValCmp() : ft::map<int, int>::value_compare(std::less<int>()) {}

	result_type operator()(const first_argument_type &a, const second_argument_type &b) const
	{
		return comp(a.first, b.first);
	}
};

TEST(map, value_compare_types)
{

	EXPECT_EQ(typeid(ft::map<int, long>::value_compare::first_argument_type), typeid(ft::pair<const int, long>));
	EXPECT_EQ(typeid(ft::map<int, long>::value_compare::second_argument_type), typeid(ft::pair<const int, long>));
	EXPECT_EQ(typeid(ft::map<int, long>::value_compare::result_type), typeid(bool));
}

TEST(map, value_compare_comp)
{
	DerivedValCmp                 cmp;
	std::binder1st<DerivedValCmp> f = std::bind1st(cmp, ft::make_pair(1, 1));

	EXPECT_TRUE(f(ft::make_pair(2, 2)));
}
