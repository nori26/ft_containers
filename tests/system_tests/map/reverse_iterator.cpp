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

typedef Map::reverse_iterator       RevIter;
typedef Map::const_reverse_iterator ConstRevIter;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

using namespace std::rel_ops;

TEST(map, reverse_iterator_types)
{
	typedef Map::reverse_iterator Iterator;

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

TEST(map, reverse_iterator_types_const)
{
	typedef Map::const_reverse_iterator Iterator;

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

TEST(map, reverse_iterator_types2)
{
	Map m;

	EXPECT_EQ(typeid(Map::reverse_iterator), typeid(m.rbegin()));
	EXPECT_EQ(typeid(Map::reverse_iterator), typeid(m.rend()));

	const Map::reverse_iterator &b1 = m.rbegin();
	const Map::reverse_iterator &b2 = m.rbegin();
	const Map::reverse_iterator &e1 = m.rend();
	const Map::reverse_iterator &e2 = m.rend();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST(map, reverse_iterator_types_const2)
{
	const Map m;

	EXPECT_EQ(typeid(Map::const_reverse_iterator), typeid(m.rbegin()));
	EXPECT_EQ(typeid(Map::const_reverse_iterator), typeid(m.rend()));

	const Map::const_reverse_iterator &b1 = m.rbegin();
	const Map::const_reverse_iterator &b2 = m.rbegin();
	const Map::const_reverse_iterator &e1 = m.rend();
	const Map::const_reverse_iterator &e2 = m.rend();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST(map, reverse_iterator_constructor)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::reverse_iterator       it(m.rbegin());
	Map::reverse_iterator       it2;
	Map::reverse_iterator       it3;
	const Map::reverse_iterator it4 = m.rbegin();
	const Map::reverse_iterator it5 = it2;

	(void)it4;
	(void)it5;
	EXPECT_EQ(it, m.rbegin());
	EXPECT_EQ(it2, it3);

	Map::const_reverse_iterator       cit(m.rbegin());
	Map::const_reverse_iterator       cit2;
	Map::const_reverse_iterator       cit3;
	const Map::const_reverse_iterator cit4 = m.rbegin();
	const Map::const_reverse_iterator cit5 = it2;

	(void)cit4;
	(void)cit5;
	EXPECT_EQ(cit, m.rbegin());
	EXPECT_EQ(cit2, cit3);
}

TEST(map, reverse_iterator_op_assign)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::reverse_iterator       it;
	Map::reverse_iterator       it2;
	const Map::reverse_iterator it3 = m.rbegin();

	it                 = m.rbegin();
	(it2 = m.rbegin()) = m.rend();
	EXPECT_EQ(it, m.rbegin());
	EXPECT_EQ(it2, m.rend());
	it2 = it3;
	EXPECT_EQ(it2, it3);

	const Map                         cm = m;
	Map::const_reverse_iterator       cit;
	Map::const_reverse_iterator       cit2;
	const Map::const_reverse_iterator cit3 = cm.rbegin();

	cit                  = cm.rbegin();
	(cit2 = cm.rbegin()) = cm.rend();
	EXPECT_EQ(cit, cm.rbegin());
	EXPECT_EQ(cit2, cm.rend());
	cit2 = cit3;
	EXPECT_EQ(cit2, cit3);
}

TEST(map, reverse_iterator_op_assign2)
{
	Map m;
	m.insert(ValueType(1, 1));
	Map::reverse_iterator it = m.rbegin();
	;

	Map::const_reverse_iterator cit = m.rend();
	EXPECT_NE(it, cit);
	cit = it;
	EXPECT_EQ(it, cit);
}

TEST(map, reverse_iterator_cmp_empty)
{
	Map       m;
	const Map cm;

	EXPECT_TRUE(m.rbegin() == m.rend());
	EXPECT_TRUE(cm.rbegin() == cm.rend());
	EXPECT_FALSE(m.rbegin() == cm.rend());
	EXPECT_FALSE(cm.rbegin() == m.rend());

	EXPECT_FALSE(m.rbegin() != m.rend());
	EXPECT_FALSE(cm.rbegin() != cm.rend());
	EXPECT_TRUE(m.rbegin() != cm.rend());
	EXPECT_TRUE(cm.rbegin() != m.rend());
}

TEST(map, reverse_iterator_op_indirection)
{
	{
		Map m;
		m.insert(ValueType(1, 1));
		Map::reverse_iterator       b  = m.rbegin();
		Map::const_reverse_iterator cb = m.rbegin();

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
		const Map::reverse_iterator       b  = m.rbegin();
		const Map::const_reverse_iterator cb = m.rbegin();

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

TEST(map, reverse_iterator_op_allow)
{
	{
		Map m;
		m.insert(ValueType(1, 1));
		Map::reverse_iterator       b  = m.rbegin();
		Map::const_reverse_iterator cb = m.rbegin();

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
		const Map::reverse_iterator       b  = m.rbegin();
		const Map::const_reverse_iterator cb = m.rbegin();

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

TEST(map, reverse_iterator_op_inc)
{
	const ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	{
		Map                          m(a1, a1 + ARRAY_SIZE(a1));
		Map::reverse_iterator        b     = m.rbegin();
		const Map::reverse_iterator &pre1  = ++b;
		const Map::reverse_iterator &pre2  = ++b;
		const Map::reverse_iterator &post1 = b++;
		const Map::reverse_iterator &post2 = b++;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		ft::reverse_iterator<const ValueType *> p(a1 + ARRAY_SIZE(a1));
		for (Map::reverse_iterator it = m.rbegin(); it != m.rend(); ++it, ++p) {
			EXPECT_EQ(*it, *p);
		}
		p = ft::reverse_iterator<const ValueType *>(a1 + ARRAY_SIZE(a1));
		for (Map::reverse_iterator it = m.rbegin(); it != m.rend(); it++, p++) {
			EXPECT_EQ(*it, *p);
		}

		Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.rbegin()++, m2.rbegin());
		EXPECT_EQ(++m2.rbegin(), m2.rend());
	}
	{
		const Map                          m(a1, a1 + ARRAY_SIZE(a1));
		Map::const_reverse_iterator        b     = m.rbegin();
		const Map::const_reverse_iterator &pre1  = ++b;
		const Map::const_reverse_iterator &pre2  = ++b;
		const Map::const_reverse_iterator &post1 = b++;
		const Map::const_reverse_iterator &post2 = b++;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		ft::reverse_iterator<const ValueType *> p(a1 + ARRAY_SIZE(a1));
		for (Map::const_reverse_iterator it = m.rbegin(); it != m.rend(); ++it, ++p) {
			EXPECT_EQ(*it, *p);
		}
		p = ft::reverse_iterator<const ValueType *>(a1 + ARRAY_SIZE(a1));
		for (Map::const_reverse_iterator it = m.rbegin(); it != m.rend(); it++, p++) {
			EXPECT_EQ(*it, *p);
		}

		const Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.rbegin()++, m2.rbegin());
		EXPECT_EQ(++m2.rbegin(), m2.rend());
	}
}

TEST(map, reverse_iterator_op_dec)
{
	const ValueType a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3), ValueType(4, 4)};
	{
		Map                          m(a1, a1 + ARRAY_SIZE(a1));
		Map::reverse_iterator        b     = m.rend();
		const Map::reverse_iterator &pre1  = --b;
		const Map::reverse_iterator &pre2  = --b;
		const Map::reverse_iterator &post1 = b--;
		const Map::reverse_iterator &post2 = b--;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		ft::reverse_iterator<const ValueType *> p(a1);
		for (Map::reverse_iterator it = m.rend(); it != m.rbegin();) {
			--it;
			--p;
			EXPECT_EQ(*it, *p);
		}
		p = ft::reverse_iterator<const ValueType *>(a1);
		for (Map::reverse_iterator it = m.rend(); it != m.rbegin();) {
			it--;
			p--;
			EXPECT_EQ(*it, *p);
		}

		Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.rend()--, m2.rend());
		EXPECT_EQ(--m2.rend(), m2.rbegin());
	}
	{
		const Map                          m(a1, a1 + ARRAY_SIZE(a1));
		Map::const_reverse_iterator        b     = m.rend();
		const Map::const_reverse_iterator &pre1  = --b;
		const Map::const_reverse_iterator &pre2  = --b;
		const Map::const_reverse_iterator &post1 = b--;
		const Map::const_reverse_iterator &post2 = b--;

		EXPECT_EQ(&pre1, &pre2);
		EXPECT_NE(&post1, &post2);

		ft::reverse_iterator<const ValueType *> p(a1);
		for (Map::const_reverse_iterator it = m.rend(); it != m.rbegin();) {
			--it;
			--p;
			EXPECT_EQ(*it, *p);
		}
		p = ft::reverse_iterator<const ValueType *>(a1);
		for (Map::const_reverse_iterator it = m.rend(); it != m.rbegin();) {
			it--;
			p--;
			EXPECT_EQ(*it, *p);
		}

		const Map m2(a1, a1 + 1);
		EXPECT_EQ(m2.rend()--, m2.rend());
		EXPECT_EQ(--m2.rend(), m2.rbegin());
	}
}

TEST(map, reverse_iterator_op_eq)
{
	Map m;
	m.insert(ValueType(1, 1));
	const Map::reverse_iterator b = m.rbegin();
	const Map::reverse_iterator e = m.rend();

	EXPECT_TRUE(b == b);
	EXPECT_TRUE(b == m.rbegin());
	EXPECT_TRUE(m.rbegin() == b);
	EXPECT_FALSE(b == e);
	EXPECT_FALSE(b == m.rend());
	EXPECT_FALSE(m.rend() == b);

	const Map                        &cm = m;
	const Map::const_reverse_iterator cb = cm.rbegin();
	const Map::const_reverse_iterator ce = cm.rend();

	EXPECT_TRUE(cb == cb);
	EXPECT_TRUE(cb == cm.rbegin());
	EXPECT_TRUE(cm.rbegin() == cb);

	EXPECT_FALSE(cb == ce);
	EXPECT_FALSE(cb == cm.rend());
	EXPECT_FALSE(cm.rend() == cb);

	EXPECT_TRUE(cb == b);
	EXPECT_TRUE(b == cb);
	EXPECT_TRUE(cb == m.rbegin());
	EXPECT_TRUE(m.rbegin() == cb);

	EXPECT_FALSE(cb == e);
	EXPECT_FALSE(e == cb);
	EXPECT_FALSE(cb == m.rend());
	EXPECT_FALSE(m.rend() == cb);

	EXPECT_EQ(typeid(bool), typeid(m.rbegin() == m.rend()));
	EXPECT_EQ(typeid(bool), typeid(cm.rbegin() == cm.rend()));
	EXPECT_EQ(typeid(bool), typeid(m.rbegin() == cm.rend()));
	EXPECT_EQ(typeid(bool), typeid(cm.rbegin() == m.rend()));
}

TEST(map, reverse_iterator_op_ne)
{
	Map m;
	m.insert(ValueType(1, 1));
	const Map::reverse_iterator b = m.rbegin();
	const Map::reverse_iterator e = m.rend();

	EXPECT_FALSE(b != b);
	EXPECT_FALSE(b != m.rbegin());
	EXPECT_FALSE(m.rbegin() != b);
	EXPECT_TRUE(b != e);
	EXPECT_TRUE(b != m.rend());
	EXPECT_TRUE(m.rend() != b);

	const Map                        &cm = m;
	const Map::const_reverse_iterator cb = cm.rbegin();
	const Map::const_reverse_iterator ce = cm.rend();

	EXPECT_FALSE(cb != cb);
	EXPECT_FALSE(cb != cm.rbegin());
	EXPECT_FALSE(cm.rbegin() != cb);

	EXPECT_TRUE(cb != ce);
	EXPECT_TRUE(cb != cm.rend());
	EXPECT_TRUE(cm.rend() != cb);

	EXPECT_FALSE(cb != b);
	EXPECT_FALSE(b != cb);
	EXPECT_FALSE(cb != m.rbegin());
	EXPECT_FALSE(m.rbegin() != cb);

	EXPECT_TRUE(cb != e);
	EXPECT_TRUE(e != cb);
	EXPECT_TRUE(cb != m.rend());
	EXPECT_TRUE(m.rend() != cb);

	EXPECT_EQ(typeid(bool), typeid(m.rbegin() != m.rend()));
	EXPECT_EQ(typeid(bool), typeid(cm.rbegin() != cm.rend()));
	EXPECT_EQ(typeid(bool), typeid(m.rbegin() != cm.rend()));
	EXPECT_EQ(typeid(bool), typeid(cm.rbegin() != m.rend()));
}
