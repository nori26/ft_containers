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

TEST(map, types)
{
	typedef ft::pair<const ftc::Data, int>                                             ValueType2;
	typedef ft::map<ftc::Data, int, std::less<ftc::Data>, ftc::Allocator<ValueType2> > Map2;

	EXPECT_EQ(typeid(Map2::allocator_type), typeid(ftc::Allocator<ValueType2>));
	EXPECT_EQ(typeid(Map2::pointer), typeid(ValueType2 *));
	EXPECT_EQ(typeid(Map2::const_pointer), typeid(const ValueType2 *));
	EXPECT_EQ(typeid(Map2::value_type), typeid(ValueType2));
	EXPECT_EQ(typeid(Map2::key_type), typeid(ftc::Data));
	EXPECT_EQ(typeid(Map2::reference), typeid(ValueType2 &));             // あんま意味ない
	EXPECT_EQ(typeid(Map2::const_reference), typeid(const ValueType2 &)); // あんま意味ない
	EXPECT_EQ(typeid(Map2::size_type), typeid(std::size_t));
	EXPECT_EQ(typeid(Map2::difference_type), typeid(std::ptrdiff_t));
	EXPECT_EQ(typeid(Map2::key_compare), typeid(std::less<ftc::Data>));
}

TEST(map, get_allocator_types)
{
	Map m;

	const ftc::Allocator<ValueType> &a1 = m.get_allocator();
	const ftc::Allocator<ValueType> &a2 = m.get_allocator();

	EXPECT_NE(&a1, &a2);
	EXPECT_EQ(typeid(ftc::Allocator<ValueType>), typeid(m.get_allocator()));
}

TEST(map, get_allocator_types_const)
{
	const Map m;

	const ftc::Allocator<ValueType> &a1 = m.get_allocator();
	const ftc::Allocator<ValueType> &a2 = m.get_allocator();

	EXPECT_NE(&a1, &a2);
	EXPECT_EQ(typeid(ftc::Allocator<ValueType>), typeid(m.get_allocator()));
}

TEST(map, get_allocator)
{
	ftc::Allocator<ValueType> a;
	Map                       m(std::less<ftc::Data>(), a);

	EXPECT_EQ(m.get_allocator().get_id(), a.get_id());
}

TEST(map, get_allocator_const)
{
	ftc::Allocator<ValueType> a;
	const Map                 m(std::less<ftc::Data>(), a);

	EXPECT_EQ(m.get_allocator().get_id(), a.get_id());
}

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
