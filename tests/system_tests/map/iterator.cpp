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

using namespace std::rel_ops;

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

TEST(map, iterator_constructor)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::iterator       it(m.begin());
	Map::iterator       it2;
	Map::iterator       it3;
	const Map::iterator it4 = m.begin();
	const Map::iterator it5 = it2;

	(void)it4;
	(void)it5;
	EXPECT_EQ(it, m.begin());
	EXPECT_EQ(it2, it3);

	Map::const_iterator       cit(m.begin());
	Map::const_iterator       cit2;
	Map::const_iterator       cit3;
	const Map::const_iterator cit4 = m.begin();
	const Map::const_iterator cit5 = it2;

	(void)cit4;
	(void)cit5;
	EXPECT_EQ(cit, m.begin());
	EXPECT_EQ(cit2, cit3);
}

TEST(map, iterator_op_assign)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::iterator       it;
	Map::iterator       it2;
	const Map::iterator it3 = m.begin();

	it                = m.begin();
	(it2 = m.begin()) = m.end();
	EXPECT_EQ(it, m.begin());
	EXPECT_EQ(it2, m.end());
	it2 = it3;
	EXPECT_EQ(it2, it3);

	const Map                 cm = m;
	Map::const_iterator       cit;
	Map::const_iterator       cit2;
	const Map::const_iterator cit3 = cm.begin();

	cit                 = cm.begin();
	(cit2 = cm.begin()) = cm.end();
	EXPECT_EQ(cit, cm.begin());
	EXPECT_EQ(cit2, cm.end());
	cit2 = cit3;
	EXPECT_EQ(cit2, cit3);
}

TEST(map, iterator_op_assign2)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::iterator it = m.begin();
	;

	Map::const_iterator cit = m.end();
	EXPECT_NE(it, cit);
	cit = it;
	EXPECT_EQ(it, cit);
}

TEST(map, iterator_cmp_empty)
{
	Map       m;
	const Map cm;

	EXPECT_TRUE(m.begin() == m.end());
	EXPECT_TRUE(cm.begin() == cm.end());
	EXPECT_FALSE(m.begin() == cm.end());
	EXPECT_FALSE(cm.begin() == m.end());

	EXPECT_FALSE(m.begin() != m.end());
	EXPECT_FALSE(cm.begin() != cm.end());
	EXPECT_TRUE(m.begin() != cm.end());
	EXPECT_TRUE(cm.begin() != m.end());
}

TEST(map, iterator_op_indirection)
{
	{
		Map m;
		m.insert(ValueType(1, 1));
		Map::iterator       b  = m.begin();
		Map::const_iterator cb = m.begin();

		EXPECT_EQ(typeid(*b), typeid(ValueType));
		EXPECT_EQ(typeid(*cb), typeid(const ValueType));

		const ValueType &d1  = *b;
		const ValueType &d2  = *b;
		const ValueType &cd1 = *cb;
		const ValueType &cd2 = *cb;

		EXPECT_EQ(&d1, &d2);
		EXPECT_EQ(&cd1, &cd2);

		EXPECT_EQ(*b, ValueType(1, 1));
		EXPECT_EQ(*cb, ValueType(1, 1));
		(*b).second = 2;
		EXPECT_EQ(*b, ValueType(1, 2));
	}
	{
		Map m;
		m.insert(ValueType(1, 1));
		const Map::iterator       b  = m.begin();
		const Map::const_iterator cb = m.begin();

		EXPECT_EQ(typeid(*b), typeid(ValueType));
		EXPECT_EQ(typeid(*cb), typeid(const ValueType));

		const ValueType &d1  = *b;
		const ValueType &d2  = *b;
		const ValueType &cd1 = *cb;
		const ValueType &cd2 = *cb;

		EXPECT_EQ(&d1, &d2);
		EXPECT_EQ(&cd1, &cd2);

		EXPECT_EQ(*b, ValueType(1, 1));
		EXPECT_EQ(*cb, ValueType(1, 1));
		(*b).second = 2;
		EXPECT_EQ(*b, ValueType(1, 2));
	}
}

TEST(map, iterator_op_allow)
{
	{
		Map m;
		m.insert(ValueType(1, 1));
		Map::iterator       b  = m.begin();
		Map::const_iterator cb = m.begin();

		EXPECT_EQ(typeid(b.operator->()), typeid(ValueType *));
		EXPECT_EQ(typeid(cb.operator->()), typeid(const ValueType *));

		EXPECT_EQ(b->first, 1);
		EXPECT_EQ(b->second, 1);
		EXPECT_EQ(cb->first, 1);
		EXPECT_EQ(cb->second, 1);
		b->second = 2;
		EXPECT_EQ(*b, ValueType(1, 2));
	}
	{
		Map m;
		m.insert(ValueType(1, 1));
		const Map::iterator       b  = m.begin();
		const Map::const_iterator cb = m.begin();

		EXPECT_EQ(typeid(b.operator->()), typeid(ValueType *));
		EXPECT_EQ(typeid(cb.operator->()), typeid(const ValueType *));

		EXPECT_EQ(b->first, 1);
		EXPECT_EQ(b->second, 1);
		EXPECT_EQ(cb->first, 1);
		EXPECT_EQ(cb->second, 1);
		b->second = 2;
		EXPECT_EQ(*b, ValueType(1, 2));
	}
}

TEST(map, iterator_op_inc)
{
	const ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	{
		Map                  m(a1, a1 + ARRAY_SIZE(a1));
		Map::iterator        b     = m.begin();
		const Map::iterator &pre1  = ++b;
		const Map::iterator &pre2  = ++b;
		const Map::iterator &post1 = b++;
		const Map::iterator &post2 = b++;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		const ValueType *p = a1;
		for (Map::iterator it = m.begin(); it != m.end(); ++it, ++p) {
			EXPECT_EQ(*it, *p);
		}
		p = a1;
		for (Map::iterator it = m.begin(); it != m.end(); it++, p++) {
			EXPECT_EQ(*it, *p);
		}

		Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.begin()++, m2.begin());
		EXPECT_EQ(++m2.begin(), m2.end());
	}
	{
		const Map                  m(a1, a1 + ARRAY_SIZE(a1));
		Map::const_iterator        b     = m.begin();
		const Map::const_iterator &pre1  = ++b;
		const Map::const_iterator &pre2  = ++b;
		const Map::const_iterator &post1 = b++;
		const Map::const_iterator &post2 = b++;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		const ValueType *p = a1;
		for (Map::const_iterator it = m.begin(); it != m.end(); ++it, ++p) {
			EXPECT_EQ(*it, *p);
		}
		p = a1;
		for (Map::const_iterator it = m.begin(); it != m.end(); it++, p++) {
			EXPECT_EQ(*it, *p);
		}

		const Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.begin()++, m2.begin());
		EXPECT_EQ(++m2.begin(), m2.end());
	}
}

TEST(map, iterator_op_dec)
{
	const ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	{
		Map                  m(a1, a1 + ARRAY_SIZE(a1));
		Map::iterator        b     = m.end();
		const Map::iterator &pre1  = --b;
		const Map::iterator &pre2  = --b;
		const Map::iterator &post1 = b--;
		const Map::iterator &post2 = b--;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		const ValueType *p = a1 + ARRAY_SIZE(a1);
		for (Map::iterator it = m.end(); it != m.begin();) {
			--it;
			--p;
			EXPECT_EQ(*it, *p);
		}
		p = a1 + ARRAY_SIZE(a1);
		for (Map::iterator it = m.end(); it != m.begin();) {
			it--;
			p--;
			EXPECT_EQ(*it, *p);
		}

		Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.end()--, m2.end());
		EXPECT_EQ(--m2.end(), m2.begin());
	}
	{
		const Map                  m(a1, a1 + ARRAY_SIZE(a1));
		Map::const_iterator        b     = m.end();
		const Map::const_iterator &pre1  = --b;
		const Map::const_iterator &pre2  = --b;
		const Map::const_iterator &post1 = b--;
		const Map::const_iterator &post2 = b--;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		const ValueType *p = a1 + ARRAY_SIZE(a1);
		for (Map::const_iterator it = m.end(); it != m.begin();) {
			--it;
			--p;
			EXPECT_EQ(*it, *p);
		}
		p = a1 + ARRAY_SIZE(a1);
		for (Map::const_iterator it = m.end(); it != m.begin();) {
			it--;
			p--;
			EXPECT_EQ(*it, *p);
		}

		const Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.end()--, m2.end());
		EXPECT_EQ(--m2.end(), m2.begin());
	}
}

TEST(map, iterator_op_eq)
{
	Map m;
	m.insert(ValueType(1, 1));
	const Map::iterator b = m.begin();
	const Map::iterator e = m.end();

	EXPECT_TRUE(b == b);
	EXPECT_TRUE(b == m.begin());
	EXPECT_TRUE(m.begin() == b);
	EXPECT_FALSE(b == e);
	EXPECT_FALSE(b == m.end());
	EXPECT_FALSE(m.end() == b);

	const Map                &cm = m;
	const Map::const_iterator cb = cm.begin();
	const Map::const_iterator ce = cm.end();

	EXPECT_TRUE(cb == cb);
	EXPECT_TRUE(cb == cm.begin());
	EXPECT_TRUE(cm.begin() == cb);

	EXPECT_FALSE(cb == ce);
	EXPECT_FALSE(cb == cm.end());
	EXPECT_FALSE(cm.end() == cb);

	EXPECT_TRUE(cb == b);
	EXPECT_TRUE(b == cb);
	EXPECT_TRUE(cb == m.begin());
	EXPECT_TRUE(m.begin() == cb);

	EXPECT_FALSE(cb == e);
	EXPECT_FALSE(e == cb);
	EXPECT_FALSE(cb == m.end());
	EXPECT_FALSE(m.end() == cb);

	EXPECT_EQ(typeid(bool), typeid(m.begin() == m.end()));
	EXPECT_EQ(typeid(bool), typeid(cm.begin() == cm.end()));
	EXPECT_EQ(typeid(bool), typeid(m.begin() == cm.end()));
	EXPECT_EQ(typeid(bool), typeid(cm.begin() == m.end()));
}

TEST(map, iterator_op_ne)
{
	Map m;
	m.insert(ValueType(1, 1));
	const Map::iterator b = m.begin();
	const Map::iterator e = m.end();

	EXPECT_FALSE(b != b);
	EXPECT_FALSE(b != m.begin());
	EXPECT_FALSE(m.begin() != b);
	EXPECT_TRUE(b != e);
	EXPECT_TRUE(b != m.end());
	EXPECT_TRUE(m.end() != b);

	const Map                &cm = m;
	const Map::const_iterator cb = cm.begin();
	const Map::const_iterator ce = cm.end();

	EXPECT_FALSE(cb != cb);
	EXPECT_FALSE(cb != cm.begin());
	EXPECT_FALSE(cm.begin() != cb);

	EXPECT_TRUE(cb != ce);
	EXPECT_TRUE(cb != cm.end());
	EXPECT_TRUE(cm.end() != cb);

	EXPECT_FALSE(cb != b);
	EXPECT_FALSE(b != cb);
	EXPECT_FALSE(cb != m.begin());
	EXPECT_FALSE(m.begin() != cb);

	EXPECT_TRUE(cb != e);
	EXPECT_TRUE(e != cb);
	EXPECT_TRUE(cb != m.end());
	EXPECT_TRUE(m.end() != cb);

	EXPECT_EQ(typeid(bool), typeid(m.begin() != m.end()));
	EXPECT_EQ(typeid(bool), typeid(cm.begin() != cm.end()));
	EXPECT_EQ(typeid(bool), typeid(m.begin() != cm.end()));
	EXPECT_EQ(typeid(bool), typeid(cm.begin() != m.end()));
}
