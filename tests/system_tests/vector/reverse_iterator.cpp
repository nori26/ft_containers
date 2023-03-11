#include "gtest.h"

#include <limits>
#include <memory>
#include <typeinfo>
#include <utility>

#include "allocator.hpp"
#include "data.hpp"
#include "type_utils.hpp"
#include "vector_fixture.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > Vector;
typedef Vector::reverse_iterator                          RevIter;
typedef Vector::const_reverse_iterator                    ConstRevIter;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

using namespace std::rel_ops;

TEST_F(vector, reverse_iterator_types)
{
	EXPECT_EQ(typeid(RevIter::difference_type), typeid(std::ptrdiff_t));
	EXPECT_EQ(typeid(RevIter::value_type), typeid(ftc::Data));
	EXPECT_EQ(typeid(RevIter::pointer), typeid(ftc::Data *));
	EXPECT_EQ(typeid(RevIter::reference), typeid(ftc::Data &));
	EXPECT_EQ(typeid(RevIter::iterator_category), typeid(std::random_access_iterator_tag));

	EXPECT_FALSE(ftc::is_reference<RevIter::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<RevIter::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<RevIter::reference>::value);
	EXPECT_FALSE(ftc::is_reference<RevIter::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<RevIter::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<RevIter::value_type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_pointer<RevIter::pointer>::type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_reference<RevIter::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<RevIter::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<RevIter::iterator_category>::value);
}

TEST_F(vector, reverse_iterator_types_const)
{
	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(ConstRevIter::difference_type));
	EXPECT_EQ(typeid(const ftc::Data), typeid(ConstRevIter::value_type));
	EXPECT_EQ(typeid(const ftc::Data *), typeid(ConstRevIter::pointer));
	EXPECT_EQ(typeid(ftc::Data &), typeid(ConstRevIter::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(ConstRevIter::iterator_category));

	EXPECT_FALSE(ftc::is_reference<ConstRevIter::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<ConstRevIter::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<ConstRevIter::reference>::value);
	EXPECT_FALSE(ftc::is_reference<ConstRevIter::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<ConstRevIter::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<ConstRevIter::value_type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_pointer<ConstRevIter::pointer>::type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_reference<ConstRevIter::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<ConstRevIter::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<ConstRevIter::iterator_category>::value);
}

TEST_F(vector, reverse_iterator_types2)
{
	Vector v;

	EXPECT_EQ(typeid(RevIter), typeid(v.rbegin()));
	EXPECT_EQ(typeid(RevIter), typeid(v.rend()));

	const RevIter &b1 = v.rbegin();
	const RevIter &b2 = v.rbegin();
	const RevIter &e1 = v.rend();
	const RevIter &e2 = v.rend();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST_F(vector, reverse_iterator_types_const2)
{
	const Vector v;

	EXPECT_EQ(typeid(ConstRevIter), typeid(v.rbegin()));
	EXPECT_EQ(typeid(ConstRevIter), typeid(v.rend()));

	const ConstRevIter &b1 = v.rbegin();
	const ConstRevIter &b2 = v.rbegin();
	const ConstRevIter &e1 = v.rend();
	const ConstRevIter &e2 = v.rend();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST_F(vector, reverse_iterator_constructor)
{
	Vector        v(1, 1);
	RevIter       it(v.rbegin());
	RevIter       it2;
	RevIter       it3;
	const RevIter it4 = v.rbegin();
	const RevIter it5 = it2;

	(void)it4;
	(void)it5;
	EXPECT_EQ(it, v.rbegin());
	EXPECT_EQ(it2, it3);

	ConstRevIter       cit(v.rbegin());
	ConstRevIter       cit2;
	ConstRevIter       cit3;
	const ConstRevIter cit4 = v.rbegin();
	const ConstRevIter cit5 = it2;

	(void)cit4;
	(void)cit5;
	EXPECT_EQ(cit, v.rbegin());
	EXPECT_EQ(cit2, cit3);
}

TEST_F(vector, reverse_iterator_op_assign)
{
	Vector        v(1, 1);
	RevIter       it;
	RevIter       it2;
	const RevIter it3 = v.rbegin();

	it                 = v.rbegin();
	(it2 = v.rbegin()) = v.rend();
	EXPECT_EQ(it, v.rbegin());
	EXPECT_EQ(it2, v.rend());
	it2 = it3;
	EXPECT_EQ(it2, it3);

	const Vector       cv = v;
	ConstRevIter       cit;
	ConstRevIter       cit2;
	const ConstRevIter cit3 = cv.rbegin();

	cit                  = cv.rbegin();
	(cit2 = cv.rbegin()) = cv.rend();
	EXPECT_EQ(cit, cv.rbegin());
	EXPECT_EQ(cit2, cv.rend());
	cit2 = cit3;
	EXPECT_EQ(cit2, cit3);
}

TEST_F(vector, reverse_iterator_op_assign_plus)
{
	Vector  v(1, 1);
	RevIter it  = v.rbegin();
	RevIter it2 = v.rbegin();

	it += 1;
	(it2 += 1) += 1;
	EXPECT_EQ(it, v.rend());
	EXPECT_EQ(it2, v.rend() + 1);

	it += -1;
	(it2 += -1) += -1;
	EXPECT_EQ(it, v.rbegin());
	EXPECT_EQ(it2, v.rbegin());

	const Vector cv   = v;
	ConstRevIter cit  = cv.rbegin();
	ConstRevIter cit2 = cv.rbegin();

	cit += 1;
	(cit2 += 1) += 1;
	EXPECT_EQ(cit, cv.rend());
	EXPECT_EQ(cit2, cv.rend() + 1);

	cit += -1;
	(cit2 += -1) += -1;
	EXPECT_EQ(cit, cv.rbegin());
	EXPECT_EQ(cit2, cv.rbegin());
}

TEST_F(vector, reverse_iterator_op_assign_minus)
{
	Vector  v(1, 1);
	RevIter it  = v.rend();
	RevIter it2 = v.rend();

	it -= 1;
	(it2 -= 1) -= 1;
	EXPECT_EQ(it, v.rbegin());
	EXPECT_EQ(it2, v.rbegin() - 1);

	it -= -1;
	(it2 -= -1) -= -1;
	EXPECT_EQ(it, v.rend());
	EXPECT_EQ(it2, v.rend());

	const Vector cv   = v;
	ConstRevIter cit  = cv.rend();
	ConstRevIter cit2 = cv.rend();

	cit -= 1;
	(cit2 -= 1) -= 1;
	EXPECT_EQ(cit, cv.rbegin());
	EXPECT_EQ(cit2, cv.rbegin() - 1);

	cit -= -1;
	(cit2 -= -1) -= -1;
	EXPECT_EQ(cit, cv.rend());
	EXPECT_EQ(cit2, cv.rend());
}

TEST_F(vector, reverse_iterator_empty)
{
	Vector       v;
	const Vector cv;

	EXPECT_TRUE(v.rbegin() == v.rend());
	EXPECT_TRUE(v.rbegin() >= v.rend());
	EXPECT_TRUE(v.rbegin() <= v.rend());
	EXPECT_FALSE(v.rbegin() != v.rend());
	EXPECT_FALSE(v.rbegin() < v.rend());
	EXPECT_FALSE(v.rbegin() > v.rend());
	EXPECT_EQ(v.rbegin() - v.rend(), 0);
	EXPECT_EQ(v.rbegin() - 0, v.rbegin());
	EXPECT_EQ(v.rbegin() + 0, v.rbegin());
	EXPECT_EQ(++v.rbegin(), v.rbegin() + 1);
	EXPECT_EQ(v.rbegin()++, v.rbegin());
	EXPECT_EQ(--v.rbegin(), v.rbegin() - 1);
	EXPECT_EQ(v.rbegin()--, v.rbegin());

	EXPECT_TRUE(cv.rbegin() == cv.rend());
	EXPECT_TRUE(cv.rbegin() >= cv.rend());
	EXPECT_TRUE(cv.rbegin() <= cv.rend());
	EXPECT_FALSE(cv.rbegin() != cv.rend());
	EXPECT_FALSE(cv.rbegin() < cv.rend());
	EXPECT_FALSE(cv.rbegin() > cv.rend());
	EXPECT_EQ(cv.rbegin() - cv.rend(), 0);
	EXPECT_EQ(cv.rbegin() - 0, cv.rbegin());
	EXPECT_EQ(cv.rbegin() + 0, cv.rbegin());
	EXPECT_EQ(++cv.rbegin(), cv.rbegin() + 1);
	EXPECT_EQ(cv.rbegin()++, cv.rbegin());
	EXPECT_EQ(--cv.rbegin(), cv.rbegin() - 1);
	EXPECT_EQ(cv.rbegin()--, cv.rbegin());
}

TEST_F(vector, reverse_iterator_op_indirection)
{
	Vector       v(1, 1);
	RevIter      b  = v.rbegin();
	ConstRevIter cb = v.rbegin();

	EXPECT_EQ(typeid(*b), typeid(ftc::Data));
	EXPECT_EQ(typeid(*cb), typeid(const ftc::Data));

	const ftc::Data &d1  = *b;
	const ftc::Data &d2  = *b;
	const ftc::Data &cd1 = *cb;
	const ftc::Data &cd2 = *cb;

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(*b, 1);
	EXPECT_EQ(*cb, 1);
	*b = 2;
	EXPECT_EQ(*b, 2);
}

TEST_F(vector, reverse_iterator_op_indirection_const)
{
	Vector             v(1, 1);
	const RevIter      b  = v.rbegin();
	const ConstRevIter cb = v.rbegin();

	EXPECT_EQ(typeid(*b), typeid(ftc::Data));
	EXPECT_EQ(typeid(*cb), typeid(const ftc::Data));

	const ftc::Data &d1  = *b;
	const ftc::Data &d2  = *b;
	const ftc::Data &cd1 = *cb;
	const ftc::Data &cd2 = *cb;

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(*b, 1);
	EXPECT_EQ(*cb, 1);
	*b = 2;
	EXPECT_EQ(*b, 2);
}

TEST_F(vector, reverse_iterator_op_subscript)
{
	ftc::Data          a[] = {1, 2, 3};
	Vector             v(a, a + ARRAY_SIZE(a));
	const RevIter      b  = v.rbegin() + 1;
	const ConstRevIter cb = v.rbegin() + 1;

	EXPECT_EQ(typeid(b[0]), typeid(ftc::Data));
	EXPECT_EQ(typeid(cb[0]), typeid(const ftc::Data));

	const ftc::Data &d1  = b[0];
	const ftc::Data &d2  = b[0];
	const ftc::Data &cd1 = cb[0];
	const ftc::Data &cd2 = cb[0];

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(b[-1], 3);
	EXPECT_EQ(cb[-1], 3);
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(cb[0], 2);
	EXPECT_EQ(b[1], 1);
	EXPECT_EQ(cb[1], 1);
	b[0] = 4;
	EXPECT_EQ(b[0], 4);
}

TEST_F(vector, reverse_iterator_op_subscript_const)
{
	ftc::Data    a[] = {1, 2, 3};
	Vector       v(a, a + ARRAY_SIZE(a));
	RevIter      b  = v.rbegin() + 1;
	ConstRevIter cb = v.rbegin() + 1;

	EXPECT_EQ(typeid(b[0]), typeid(ftc::Data));
	EXPECT_EQ(typeid(cb[0]), typeid(const ftc::Data));

	const ftc::Data &d1  = b[0];
	const ftc::Data &d2  = b[0];
	const ftc::Data &cd1 = cb[0];
	const ftc::Data &cd2 = cb[0];

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(b[-1], 3);
	EXPECT_EQ(cb[-1], 3);
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(cb[0], 2);
	EXPECT_EQ(b[1], 1);
	EXPECT_EQ(cb[1], 1);
	b[0] = 4;
	EXPECT_EQ(b[0], 4);
}

TEST_F(vector, reverse_iterator_op_allow)
{
	Vector       v(1, 1);
	RevIter      b  = v.rbegin();
	ConstRevIter cb = v.rbegin();

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST_F(vector, reverse_iterator_op_allow_const)
{
	Vector             v(1, 1);
	const RevIter      b  = v.rbegin();
	const ConstRevIter cb = v.rbegin();

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST_F(vector, reverse_iterator_op_inc)
{
	Vector  v(1, 1);
	RevIter b = v.rbegin();

	const RevIter &pre1  = ++b;
	const RevIter &pre2  = ++b;
	const RevIter &post1 = b++;
	const RevIter &post2 = b++;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(v.rbegin()++, v.rbegin());
	EXPECT_EQ(++v.rbegin(), v.rend());
}

TEST_F(vector, reverse_iterator_op_dec)
{
	Vector  v(1, 1);
	RevIter b = v.rbegin();

	const RevIter &pre1  = --b;
	const RevIter &pre2  = --b;
	const RevIter &post1 = b--;
	const RevIter &post2 = b--;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(v.rend()--, v.rend());
	EXPECT_EQ(--v.rend(), v.rbegin());
}

TEST_F(vector, reverse_iterator_op_plus)
{
	Vector             v(1, 1);
	const Vector      &cv = v;
	const RevIter      b  = v.rbegin();
	const ConstRevIter cb = cv.rbegin();

	EXPECT_EQ(typeid(RevIter), typeid(b + 1));
	EXPECT_EQ(typeid(RevIter), typeid(1 + b));
	EXPECT_EQ(typeid(ConstRevIter), typeid(cb + 1));
	EXPECT_EQ(typeid(ConstRevIter), typeid(1 + cb));

	const RevIter      &b1  = b + 1;
	const RevIter      &b2  = b + 1;
	const RevIter      &b3  = 1 + b;
	const RevIter      &b4  = 1 + b;
	const ConstRevIter &cb1 = cb + 1;
	const ConstRevIter &cb2 = cb + 1;
	const ConstRevIter &cb3 = 1 + cb;
	const ConstRevIter &cb4 = 1 + cb;

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&b3, &b4);
	EXPECT_NE(&cb1, &cb2);
	EXPECT_NE(&cb3, &cb4);

	EXPECT_EQ(b + 1, v.rend());
	EXPECT_EQ(1 + b, v.rend());
	EXPECT_EQ(cb + 1, cv.rend());
	EXPECT_EQ(1 + cb, cv.rend());

	EXPECT_EQ(v.rend() + -1, v.rbegin());
	EXPECT_EQ(-1 + v.rend(), v.rbegin());
	EXPECT_EQ(cv.rend() + -1, cv.rbegin());
	EXPECT_EQ(-1 + cv.rend(), cv.rbegin());
}

TEST_F(vector, reverse_iterator_op_minus)
{
	Vector             v(1, 1);
	const Vector      &cv = v;
	const RevIter      b  = v.rend();
	const ConstRevIter cb = cv.rend();

	EXPECT_EQ(typeid(RevIter), typeid(b - 1));
	EXPECT_EQ(typeid(ConstRevIter), typeid(cb - 1));
	EXPECT_EQ(typeid(RevIter::difference_type), typeid(b - b));
	EXPECT_EQ(typeid(RevIter::difference_type), typeid(cb - cb));
	EXPECT_EQ(typeid(RevIter::difference_type), typeid(b - cb));
	EXPECT_EQ(typeid(RevIter::difference_type), typeid(cb - b));

	const RevIter                  &b1  = b - 1;
	const RevIter                  &b2  = b - 1;
	const ConstRevIter             &cb1 = cb - 1;
	const ConstRevIter             &cb2 = cb - 1;
	const RevIter::difference_type &d1  = b - b;
	const RevIter::difference_type &d2  = b - b;
	const RevIter::difference_type &d3  = cb - cb;
	const RevIter::difference_type &d4  = cb - cb;
	const RevIter::difference_type &d5  = b - cb;
	const RevIter::difference_type &d6  = b - cb;
	const RevIter::difference_type &d7  = cb - b;
	const RevIter::difference_type &d8  = cb - b;

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&cb1, &cb2);
	EXPECT_NE(&d1, &d2);
	EXPECT_NE(&d3, &d4);
	EXPECT_NE(&d5, &d6);
	EXPECT_NE(&d7, &d8);

	EXPECT_EQ(b - 1, v.rbegin());
	EXPECT_EQ(cb - 1, cv.rbegin());
	EXPECT_EQ(b - b, 0);
	EXPECT_EQ(cb - cb, 0);
	EXPECT_EQ(b - cb, 0);
	EXPECT_EQ(cb - b, 0);

	EXPECT_EQ(v.rbegin() - -1, v.rend());
	EXPECT_EQ(cv.rbegin() - -1, cv.rend());
}

TEST_F(vector, reverse_iterator_op_eq)
{
	Vector        v(1, 1);
	const RevIter b = v.rbegin();
	const RevIter e = v.rend();

	EXPECT_TRUE(b == b);
	EXPECT_TRUE(b == v.rbegin());
	EXPECT_TRUE(v.rbegin() == b);
	EXPECT_FALSE(b == e);
	EXPECT_FALSE(b == v.rend());
	EXPECT_FALSE(v.rend() == b);

	const Vector      &cv = v;
	const ConstRevIter cb = cv.rbegin();
	const ConstRevIter ce = cv.rend();

	EXPECT_TRUE(cb == cb);
	EXPECT_TRUE(cb == cv.rbegin());
	EXPECT_TRUE(cv.rbegin() == cb);

	EXPECT_FALSE(cb == ce);
	EXPECT_FALSE(cb == cv.rend());
	EXPECT_FALSE(cv.rend() == cb);

	EXPECT_TRUE(cb == b);
	EXPECT_TRUE(b == cb);
	EXPECT_TRUE(cb == v.rbegin());
	EXPECT_TRUE(v.rbegin() == cb);

	EXPECT_FALSE(cb == e);
	EXPECT_FALSE(e == cb);
	EXPECT_FALSE(cb == v.rend());
	EXPECT_FALSE(v.rend() == cb);

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() == v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() == cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() == cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() == v.rend()));
}

TEST_F(vector, reverse_iterator_op_ne)
{
	Vector        v(1, 1);
	const RevIter b = v.rbegin();
	const RevIter e = v.rend();

	EXPECT_FALSE(b != b);
	EXPECT_FALSE(b != v.rbegin());
	EXPECT_FALSE(v.rbegin() != b);
	EXPECT_TRUE(b != e);
	EXPECT_TRUE(b != v.rend());
	EXPECT_TRUE(v.rend() != b);

	const Vector      &cv = v;
	const ConstRevIter cb = cv.rbegin();
	const ConstRevIter ce = cv.rend();

	EXPECT_FALSE(cb != cb);
	EXPECT_FALSE(cb != cv.rbegin());
	EXPECT_FALSE(cv.rbegin() != cb);

	EXPECT_TRUE(cb != ce);
	EXPECT_TRUE(cb != cv.rend());
	EXPECT_TRUE(cv.rend() != cb);

	EXPECT_FALSE(cb != b);
	EXPECT_FALSE(b != cb);
	EXPECT_FALSE(cb != v.rbegin());
	EXPECT_FALSE(v.rbegin() != cb);

	EXPECT_TRUE(cb != e);
	EXPECT_TRUE(e != cb);
	EXPECT_TRUE(cb != v.rend());
	EXPECT_TRUE(v.rend() != cb);

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() != v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() != cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() != cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() != v.rend()));
}

TEST_F(vector, reverse_iterator_op_less)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() < v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() < cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() < cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() < v.rend()));

	EXPECT_TRUE(v.rbegin() < v.rend());
	EXPECT_TRUE(cv.rbegin() < cv.rend());
	EXPECT_TRUE(v.rbegin() < cv.rend());
	EXPECT_TRUE(cv.rbegin() < v.rend());

	EXPECT_FALSE(v.rend() < v.rbegin());
	EXPECT_FALSE(cv.rend() < cv.rbegin());
	EXPECT_FALSE(v.rend() < cv.rbegin());
	EXPECT_FALSE(cv.rend() < v.rbegin());

	EXPECT_FALSE(v.rend() < v.rend());
	EXPECT_FALSE(cv.rend() < cv.rend());
	EXPECT_FALSE(v.rend() < cv.rend());
	EXPECT_FALSE(cv.rend() < v.rend());
}

TEST_F(vector, reverse_iterator_op_less_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() <= v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() <= cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() <= cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() <= v.rend()));

	EXPECT_TRUE(v.rbegin() <= v.rend());
	EXPECT_TRUE(cv.rbegin() <= cv.rend());
	EXPECT_TRUE(v.rbegin() <= cv.rend());
	EXPECT_TRUE(cv.rbegin() <= v.rend());

	EXPECT_FALSE(v.rend() <= v.rbegin());
	EXPECT_FALSE(cv.rend() <= cv.rbegin());
	EXPECT_FALSE(v.rend() <= cv.rbegin());
	EXPECT_FALSE(cv.rend() <= v.rbegin());

	EXPECT_TRUE(v.rend() <= v.rend());
	EXPECT_TRUE(cv.rend() <= cv.rend());
	EXPECT_TRUE(v.rend() <= cv.rend());
	EXPECT_TRUE(cv.rend() <= v.rend());
}

TEST_F(vector, reverse_iterator_op_greater)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() > v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() > cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() > cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() > v.rend()));

	EXPECT_FALSE(v.rbegin() > v.rend());
	EXPECT_FALSE(cv.rbegin() > cv.rend());
	EXPECT_FALSE(v.rbegin() > cv.rend());
	EXPECT_FALSE(cv.rbegin() > v.rend());

	EXPECT_TRUE(v.rend() > v.rbegin());
	EXPECT_TRUE(cv.rend() > cv.rbegin());
	EXPECT_TRUE(v.rend() > cv.rbegin());
	EXPECT_TRUE(cv.rend() > v.rbegin());

	EXPECT_FALSE(v.rend() > v.rend());
	EXPECT_FALSE(cv.rend() > cv.rend());
	EXPECT_FALSE(v.rend() > cv.rend());
	EXPECT_FALSE(cv.rend() > v.rend());
}

TEST_F(vector, reverse_iterator_op_greater_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.rbegin() >= v.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() >= cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(v.rbegin() >= cv.rend()));
	EXPECT_EQ(typeid(bool), typeid(cv.rbegin() >= v.rend()));

	EXPECT_FALSE(v.rbegin() >= v.rend());
	EXPECT_FALSE(cv.rbegin() >= cv.rend());
	EXPECT_FALSE(v.rbegin() >= cv.rend());
	EXPECT_FALSE(cv.rbegin() >= v.rend());

	EXPECT_TRUE(v.rend() >= v.rbegin());
	EXPECT_TRUE(cv.rend() >= cv.rbegin());
	EXPECT_TRUE(v.rend() >= cv.rbegin());
	EXPECT_TRUE(cv.rend() >= v.rbegin());

	EXPECT_TRUE(v.rend() >= v.rend());
	EXPECT_TRUE(cv.rend() >= cv.rend());
	EXPECT_TRUE(v.rend() >= cv.rend());
	EXPECT_TRUE(cv.rend() >= v.rend());
}

// TODO

TEST_F(vector, reverse_iterator1)
{
	Vector       v;
	ConstRevIter it = v.rbegin();
	EXPECT_TRUE(v.rbegin() == it);
	it = v.rend();
	EXPECT_TRUE(v.rend() == it);
}

TEST_F(vector, reverse_iterator2)
{
	RevIter      it;
	ConstRevIter c_it(it);
	ConstRevIter c_it2 = it;
	c_it               = it;
	(void)c_it2;
}

TEST_F(vector, reverse_iterator3)
{
	Vector       v;
	RevIter      it(v.begin());
	ConstRevIter c_it(v.begin());
	c_it = it;
}

TEST_F(vector, reverse_iterator4)
{
	const Vector v;
	ConstRevIter c_it(v.begin());
}

TEST_F(vector, reverse_iterator5)
{
	// Vector       v(1, 1);
	// (void)v;
	ftc::Data a[] = {1, 2, 3};
	Vector    v1(a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v1.rbegin(), v1.rend() - 3);
	EXPECT_EQ((v1.rbegin() + 1) = v1.rend(), v1.rend());
}
