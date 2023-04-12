#include "gtest.h"

#include <climits>
#include <functional>
#include <list>
#include <sstream>
#include <typeinfo>

#include "allocator.hpp"
#include "cmp.hpp"
#include "data.hpp"
#include "type_utils.hpp"

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

TEST(map, iterator_types)
{
	typedef Map::iterator Iterator;

	EXPECT_EQ(typeid(Iterator::difference_type), typeid(std::ptrdiff_t));
	EXPECT_EQ(typeid(Iterator::value_type), typeid(ValueType));
	EXPECT_EQ(typeid(Iterator::pointer), typeid(ValueType *));
	EXPECT_EQ(typeid(Iterator::reference), typeid(ValueType &));
	EXPECT_EQ(typeid(Iterator::iterator_category), typeid(std::bidirectional_iterator_tag));

	EXPECT_FALSE(ftc::is_reference<Iterator::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<Iterator::reference>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<Iterator::value_type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_pointer<Iterator::pointer>::type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_reference<Iterator::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<Iterator::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<Iterator::iterator_category>::value);
}

TEST(map, iterator_types_const)
{
	typedef Map::const_iterator Iterator;

	EXPECT_EQ(typeid(Iterator::difference_type), typeid(std::ptrdiff_t));
	EXPECT_EQ(typeid(Iterator::value_type), typeid(const ValueType));
	EXPECT_EQ(typeid(Iterator::pointer), typeid(const ValueType *));
	EXPECT_EQ(typeid(Iterator::reference), typeid(const ValueType &));
	EXPECT_EQ(typeid(Iterator::iterator_category), typeid(std::bidirectional_iterator_tag));

	EXPECT_FALSE(ftc::is_reference<Iterator::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<Iterator::reference>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<Iterator::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<Iterator::value_type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_pointer<Iterator::pointer>::type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_reference<Iterator::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<Iterator::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<Iterator::iterator_category>::value);
}

TEST(map, iterator_types2)
{
	Map m;

	EXPECT_EQ(typeid(Map::iterator), typeid(m.begin()));
	EXPECT_EQ(typeid(Map::iterator), typeid(m.end()));

	const Map::iterator &b1 = m.begin();
	const Map::iterator &b2 = m.begin();
	const Map::iterator &e1 = m.end();
	const Map::iterator &e2 = m.end();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST(map, iterator_types_const2)
{
	const Map m;

	EXPECT_EQ(typeid(Map::const_iterator), typeid(m.begin()));
	EXPECT_EQ(typeid(Map::const_iterator), typeid(m.end()));

	const Map::const_iterator &b1 = m.begin();
	const Map::const_iterator &b2 = m.begin();
	const Map::const_iterator &e1 = m.end();
	const Map::const_iterator &e2 = m.end();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

