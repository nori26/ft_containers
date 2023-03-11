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
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > Vector;
typedef ftc::Allocator<ftc::Data>::ExceptionOn            AllocExceptionOn;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

using namespace std::rel_ops;

TEST_F(vector, iterator_types)
{
	typedef Vector::iterator Iterator;

	EXPECT_EQ(typeid(Iterator::difference_type), typeid(std::ptrdiff_t));
	EXPECT_EQ(typeid(Iterator::value_type), typeid(ftc::Data));
	EXPECT_EQ(typeid(Iterator::pointer), typeid(ftc::Data *));
	EXPECT_EQ(typeid(Iterator::reference), typeid(ftc::Data &));
	EXPECT_EQ(typeid(Iterator::iterator_category), typeid(std::random_access_iterator_tag));

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

TEST_F(vector, iterator_types_const)
{
	typedef Vector::const_iterator Iterator;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Iterator::difference_type));
	EXPECT_EQ(typeid(const ftc::Data), typeid(Iterator::value_type));
	EXPECT_EQ(typeid(const ftc::Data *), typeid(Iterator::pointer));
	EXPECT_EQ(typeid(ftc::Data &), typeid(Iterator::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(Iterator::iterator_category));

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

TEST_F(vector, iterator_types2)
{
	Vector v;

	EXPECT_EQ(typeid(Vector::iterator), typeid(v.begin()));
	EXPECT_EQ(typeid(Vector::iterator), typeid(v.end()));

	const Vector::iterator &b1 = v.begin();
	const Vector::iterator &b2 = v.begin();
	const Vector::iterator &e1 = v.end();
	const Vector::iterator &e2 = v.end();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST_F(vector, iterator_types_const2)
{
	const Vector v;

	EXPECT_EQ(typeid(Vector::const_iterator), typeid(v.begin()));
	EXPECT_EQ(typeid(Vector::const_iterator), typeid(v.end()));

	const Vector::const_iterator &b1 = v.begin();
	const Vector::const_iterator &b2 = v.begin();
	const Vector::const_iterator &e1 = v.end();
	const Vector::const_iterator &e2 = v.end();

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&e1, &e2);
}

TEST_F(vector, iterator_constructor)
{
	Vector                 v(1, 1);
	Vector::iterator       it(v.begin());
	Vector::iterator       it2;
	Vector::iterator       it3;
	const Vector::iterator it4 = v.begin();
	const Vector::iterator it5 = it2;

	(void)it4;
	(void)it5;
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(it2, it3);

	Vector::const_iterator       cit(v.begin());
	Vector::const_iterator       cit2;
	Vector::const_iterator       cit3;
	const Vector::const_iterator cit4 = v.begin();
	const Vector::const_iterator cit5 = it2;

	(void)cit4;
	(void)cit5;
	EXPECT_EQ(cit, v.begin());
	EXPECT_EQ(cit2, cit3);
}

TEST_F(vector, iterator_op_assign)
{
	Vector                 v(1, 1);
	Vector::iterator       it;
	Vector::iterator       it2;
	const Vector::iterator it3 = v.begin();

	it                = v.begin();
	(it2 = v.begin()) = v.end();
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(it2, v.end());
	it2 = it3;
	EXPECT_EQ(it2, it3);

	const Vector                 cv = v;
	Vector::const_iterator       cit;
	Vector::const_iterator       cit2;
	const Vector::const_iterator cit3 = cv.begin();

	cit                 = cv.begin();
	(cit2 = cv.begin()) = cv.end();
	EXPECT_EQ(cit, cv.begin());
	EXPECT_EQ(cit2, cv.end());
	cit2 = cit3;
	EXPECT_EQ(cit2, cit3);
}

TEST_F(vector, iterator_op_assign_plus)
{
	Vector           v(1, 1);
	Vector::iterator it  = v.begin();
	Vector::iterator it2 = v.begin();

	it += 1;
	(it2 += 1) += 1;
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(it2, v.end() + 1);

	it += -1;
	(it2 += -1) += -1;
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(it2, v.begin());

	const Vector           cv   = v;
	Vector::const_iterator cit  = cv.begin();
	Vector::const_iterator cit2 = cv.begin();

	cit += 1;
	(cit2 += 1) += 1;
	EXPECT_EQ(cit, cv.end());
	EXPECT_EQ(cit2, cv.end() + 1);

	cit += -1;
	(cit2 += -1) += -1;
	EXPECT_EQ(cit, cv.begin());
	EXPECT_EQ(cit2, cv.begin());
}

TEST_F(vector, iterator_op_assign_minus)
{
	Vector           v(1, 1);
	Vector::iterator it  = v.end();
	Vector::iterator it2 = v.end();

	it -= 1;
	(it2 -= 1) -= 1;
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(it2, v.begin() - 1);

	it -= -1;
	(it2 -= -1) -= -1;
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(it2, v.end());

	const Vector           cv   = v;
	Vector::const_iterator cit  = cv.end();
	Vector::const_iterator cit2 = cv.end();

	cit -= 1;
	(cit2 -= 1) -= 1;
	EXPECT_EQ(cit, cv.begin());
	EXPECT_EQ(cit2, cv.begin() - 1);

	cit -= -1;
	(cit2 -= -1) -= -1;
	EXPECT_EQ(cit, cv.end());
	EXPECT_EQ(cit2, cv.end());
}

TEST_F(vector, iterator_empty)
{
	Vector       v;
	const Vector cv;

	EXPECT_TRUE(v.begin() == v.end());
	EXPECT_TRUE(v.begin() >= v.end());
	EXPECT_TRUE(v.begin() <= v.end());
	EXPECT_FALSE(v.begin() != v.end());
	EXPECT_FALSE(v.begin() < v.end());
	EXPECT_FALSE(v.begin() > v.end());
	EXPECT_EQ(v.begin() - v.end(), 0);
	EXPECT_EQ(v.begin() - 0, v.begin());
	EXPECT_EQ(v.begin() + 0, v.begin());
	EXPECT_EQ(++v.begin(), v.begin() + 1);
	EXPECT_EQ(v.begin()++, v.begin());
	EXPECT_EQ(--v.begin(), v.begin() - 1);
	EXPECT_EQ(v.begin()--, v.begin());

	EXPECT_TRUE(cv.begin() == cv.end());
	EXPECT_TRUE(cv.begin() >= cv.end());
	EXPECT_TRUE(cv.begin() <= cv.end());
	EXPECT_FALSE(cv.begin() != cv.end());
	EXPECT_FALSE(cv.begin() < cv.end());
	EXPECT_FALSE(cv.begin() > cv.end());
	EXPECT_EQ(cv.begin() - cv.end(), 0);
	EXPECT_EQ(cv.begin() - 0, cv.begin());
	EXPECT_EQ(cv.begin() + 0, cv.begin());
	EXPECT_EQ(++cv.begin(), cv.begin() + 1);
	EXPECT_EQ(cv.begin()++, cv.begin());
	EXPECT_EQ(--cv.begin(), cv.begin() - 1);
	EXPECT_EQ(cv.begin()--, cv.begin());
}

TEST_F(vector, iterator_op_indirection)
{
	Vector                 v(1, 1);
	Vector::iterator       b  = v.begin();
	Vector::const_iterator cb = v.begin();

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

TEST_F(vector, iterator_op_indirection_const)
{
	Vector                       v(1, 1);
	const Vector::iterator       b  = v.begin();
	const Vector::const_iterator cb = v.begin();

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

TEST_F(vector, iterator_op_subscript)
{
	ftc::Data                    a[] = {1, 2, 3};
	Vector                       v(a, a + ARRAY_SIZE(a));
	const Vector::iterator       b  = v.begin() + 1;
	const Vector::const_iterator cb = v.begin() + 1;

	EXPECT_EQ(typeid(b[0]), typeid(ftc::Data));
	EXPECT_EQ(typeid(cb[0]), typeid(const ftc::Data));

	const ftc::Data &d1  = b[0];
	const ftc::Data &d2  = b[0];
	const ftc::Data &cd1 = cb[0];
	const ftc::Data &cd2 = cb[0];

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(b[-1], 1);
	EXPECT_EQ(cb[-1], 1);
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(cb[0], 2);
	EXPECT_EQ(b[1], 3);
	EXPECT_EQ(cb[1], 3);
	b[0] = 4;
	EXPECT_EQ(b[0], 4);
}

TEST_F(vector, iterator_op_subscript_const)
{
	ftc::Data              a[] = {1, 2, 3};
	Vector                 v(a, a + ARRAY_SIZE(a));
	Vector::iterator       b  = v.begin() + 1;
	Vector::const_iterator cb = v.begin() + 1;

	EXPECT_EQ(typeid(b[0]), typeid(ftc::Data));
	EXPECT_EQ(typeid(cb[0]), typeid(const ftc::Data));

	const ftc::Data &d1  = b[0];
	const ftc::Data &d2  = b[0];
	const ftc::Data &cd1 = cb[0];
	const ftc::Data &cd2 = cb[0];

	EXPECT_EQ(&d1, &d2);
	EXPECT_EQ(&cd1, &cd2);

	EXPECT_EQ(b[-1], 1);
	EXPECT_EQ(cb[-1], 1);
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(cb[0], 2);
	EXPECT_EQ(b[1], 3);
	EXPECT_EQ(cb[1], 3);
	b[0] = 4;
	EXPECT_EQ(b[0], 4);
}

TEST_F(vector, iterator_op_allow)
{
	Vector                 v(1, 1);
	Vector::iterator       b  = v.begin();
	Vector::const_iterator cb = v.begin();

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST_F(vector, iterator_op_allow_const)
{
	Vector                       v(1, 1);
	const Vector::iterator       b  = v.begin();
	const Vector::const_iterator cb = v.begin();

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST_F(vector, iterator_op_inc)
{
	Vector           v(1, 1);
	Vector::iterator b = v.begin();

	const Vector::iterator &pre1  = ++b;
	const Vector::iterator &pre2  = ++b;
	const Vector::iterator &post1 = b++;
	const Vector::iterator &post2 = b++;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(v.begin()++, v.begin());
	EXPECT_EQ(++v.begin(), v.end());
}

TEST_F(vector, iterator_op_dec)
{
	Vector           v(1, 1);
	Vector::iterator b = v.begin();

	const Vector::iterator &pre1  = --b;
	const Vector::iterator &pre2  = --b;
	const Vector::iterator &post1 = b--;
	const Vector::iterator &post2 = b--;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(v.end()--, v.end());
	EXPECT_EQ(--v.end(), v.begin());
}

TEST_F(vector, iterator_op_plus)
{
	Vector                       v(1, 1);
	const Vector                &cv = v;
	const Vector::iterator       b  = v.begin();
	const Vector::const_iterator cb = cv.begin();

	EXPECT_EQ(typeid(Vector::iterator), typeid(b + 1));
	EXPECT_EQ(typeid(Vector::iterator), typeid(1 + b));
	EXPECT_EQ(typeid(Vector::const_iterator), typeid(cb + 1));
	EXPECT_EQ(typeid(Vector::const_iterator), typeid(1 + cb));

	const Vector::iterator       &b1  = b + 1;
	const Vector::iterator       &b2  = b + 1;
	const Vector::iterator       &b3  = 1 + b;
	const Vector::iterator       &b4  = 1 + b;
	const Vector::const_iterator &cb1 = cb + 1;
	const Vector::const_iterator &cb2 = cb + 1;
	const Vector::const_iterator &cb3 = 1 + cb;
	const Vector::const_iterator &cb4 = 1 + cb;

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&b3, &b4);
	EXPECT_NE(&cb1, &cb2);
	EXPECT_NE(&cb3, &cb4);

	EXPECT_EQ(b + 1, v.end());
	EXPECT_EQ(1 + b, v.end());
	EXPECT_EQ(cb + 1, cv.end());
	EXPECT_EQ(1 + cb, cv.end());

	EXPECT_EQ(v.end() + -1, v.begin());
	EXPECT_EQ(-1 + v.end(), v.begin());
	EXPECT_EQ(cv.end() + -1, cv.begin());
	EXPECT_EQ(-1 + cv.end(), cv.begin());
}

TEST_F(vector, iterator_op_minus)
{
	Vector                       v(1, 1);
	const Vector                &cv = v;
	const Vector::iterator       b  = v.end();
	const Vector::const_iterator cb = cv.end();

	EXPECT_EQ(typeid(Vector::iterator), typeid(b - 1));
	EXPECT_EQ(typeid(Vector::const_iterator), typeid(cb - 1));
	EXPECT_EQ(typeid(Vector::iterator::difference_type), typeid(b - b));
	EXPECT_EQ(typeid(Vector::iterator::difference_type), typeid(cb - cb));
	EXPECT_EQ(typeid(Vector::iterator::difference_type), typeid(b - cb));
	EXPECT_EQ(typeid(Vector::iterator::difference_type), typeid(cb - b));

	const Vector::iterator                  &b1  = b - 1;
	const Vector::iterator                  &b2  = b - 1;
	const Vector::const_iterator            &cb1 = cb - 1;
	const Vector::const_iterator            &cb2 = cb - 1;
	const Vector::iterator::difference_type &d1  = b - b;
	const Vector::iterator::difference_type &d2  = b - b;
	const Vector::iterator::difference_type &d3  = cb - cb;
	const Vector::iterator::difference_type &d4  = cb - cb;
	const Vector::iterator::difference_type &d5  = b - cb;
	const Vector::iterator::difference_type &d6  = b - cb;
	const Vector::iterator::difference_type &d7  = cb - b;
	const Vector::iterator::difference_type &d8  = cb - b;

	EXPECT_NE(&b1, &b2);
	EXPECT_NE(&cb1, &cb2);
	EXPECT_NE(&d1, &d2);
	EXPECT_NE(&d3, &d4);
	EXPECT_NE(&d5, &d6);
	EXPECT_NE(&d7, &d8);

	EXPECT_EQ(b - 1, v.begin());
	EXPECT_EQ(cb - 1, cv.begin());
	EXPECT_EQ(b - b, 0);
	EXPECT_EQ(cb - cb, 0);
	EXPECT_EQ(b - cb, 0);
	EXPECT_EQ(cb - b, 0);

	EXPECT_EQ(v.begin() - -1, v.end());
	EXPECT_EQ(cv.begin() - -1, cv.end());
}

TEST_F(vector, iterator_op_eq)
{
	Vector                 v(1, 1);
	const Vector::iterator b = v.begin();
	const Vector::iterator e = v.end();

	EXPECT_TRUE(b == b);
	EXPECT_TRUE(b == v.begin());
	EXPECT_TRUE(v.begin() == b);
	EXPECT_FALSE(b == e);
	EXPECT_FALSE(b == v.end());
	EXPECT_FALSE(v.end() == b);

	const Vector                &cv = v;
	const Vector::const_iterator cb = cv.begin();
	const Vector::const_iterator ce = cv.end();

	EXPECT_TRUE(cb == cb);
	EXPECT_TRUE(cb == cv.begin());
	EXPECT_TRUE(cv.begin() == cb);

	EXPECT_FALSE(cb == ce);
	EXPECT_FALSE(cb == cv.end());
	EXPECT_FALSE(cv.end() == cb);

	EXPECT_TRUE(cb == b);
	EXPECT_TRUE(b == cb);
	EXPECT_TRUE(cb == v.begin());
	EXPECT_TRUE(v.begin() == cb);

	EXPECT_FALSE(cb == e);
	EXPECT_FALSE(e == cb);
	EXPECT_FALSE(cb == v.end());
	EXPECT_FALSE(v.end() == cb);

	EXPECT_EQ(typeid(bool), typeid(v.begin() == v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() == cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() == cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() == v.end()));
}

TEST_F(vector, iterator_op_ne)
{
	Vector                 v(1, 1);
	const Vector::iterator b = v.begin();
	const Vector::iterator e = v.end();

	EXPECT_FALSE(b != b);
	EXPECT_FALSE(b != v.begin());
	EXPECT_FALSE(v.begin() != b);
	EXPECT_TRUE(b != e);
	EXPECT_TRUE(b != v.end());
	EXPECT_TRUE(v.end() != b);

	const Vector                &cv = v;
	const Vector::const_iterator cb = cv.begin();
	const Vector::const_iterator ce = cv.end();

	EXPECT_FALSE(cb != cb);
	EXPECT_FALSE(cb != cv.begin());
	EXPECT_FALSE(cv.begin() != cb);

	EXPECT_TRUE(cb != ce);
	EXPECT_TRUE(cb != cv.end());
	EXPECT_TRUE(cv.end() != cb);

	EXPECT_FALSE(cb != b);
	EXPECT_FALSE(b != cb);
	EXPECT_FALSE(cb != v.begin());
	EXPECT_FALSE(v.begin() != cb);

	EXPECT_TRUE(cb != e);
	EXPECT_TRUE(e != cb);
	EXPECT_TRUE(cb != v.end());
	EXPECT_TRUE(v.end() != cb);

	EXPECT_EQ(typeid(bool), typeid(v.begin() != v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() != cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() != cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() != v.end()));
}

TEST_F(vector, iterator_op_less)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.begin() < v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() < cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() < cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() < v.end()));

	EXPECT_TRUE(v.begin() < v.end());
	EXPECT_TRUE(cv.begin() < cv.end());
	EXPECT_TRUE(v.begin() < cv.end());
	EXPECT_TRUE(cv.begin() < v.end());

	EXPECT_FALSE(v.end() < v.begin());
	EXPECT_FALSE(cv.end() < cv.begin());
	EXPECT_FALSE(v.end() < cv.begin());
	EXPECT_FALSE(cv.end() < v.begin());

	EXPECT_FALSE(v.end() < v.end());
	EXPECT_FALSE(cv.end() < cv.end());
	EXPECT_FALSE(v.end() < cv.end());
	EXPECT_FALSE(cv.end() < v.end());
}

TEST_F(vector, iterator_op_less_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.begin() <= v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() <= cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() <= cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() <= v.end()));

	EXPECT_TRUE(v.begin() <= v.end());
	EXPECT_TRUE(cv.begin() <= cv.end());
	EXPECT_TRUE(v.begin() <= cv.end());
	EXPECT_TRUE(cv.begin() <= v.end());

	EXPECT_FALSE(v.end() <= v.begin());
	EXPECT_FALSE(cv.end() <= cv.begin());
	EXPECT_FALSE(v.end() <= cv.begin());
	EXPECT_FALSE(cv.end() <= v.begin());

	EXPECT_TRUE(v.end() <= v.end());
	EXPECT_TRUE(cv.end() <= cv.end());
	EXPECT_TRUE(v.end() <= cv.end());
	EXPECT_TRUE(cv.end() <= v.end());
}

TEST_F(vector, iterator_op_greater)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.begin() > v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() > cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() > cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() > v.end()));

	EXPECT_FALSE(v.begin() > v.end());
	EXPECT_FALSE(cv.begin() > cv.end());
	EXPECT_FALSE(v.begin() > cv.end());
	EXPECT_FALSE(cv.begin() > v.end());

	EXPECT_TRUE(v.end() > v.begin());
	EXPECT_TRUE(cv.end() > cv.begin());
	EXPECT_TRUE(v.end() > cv.begin());
	EXPECT_TRUE(cv.end() > v.begin());

	EXPECT_FALSE(v.end() > v.end());
	EXPECT_FALSE(cv.end() > cv.end());
	EXPECT_FALSE(v.end() > cv.end());
	EXPECT_FALSE(cv.end() > v.end());
}

TEST_F(vector, iterator_op_greater_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(v.begin() >= v.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() >= cv.end()));
	EXPECT_EQ(typeid(bool), typeid(v.begin() >= cv.end()));
	EXPECT_EQ(typeid(bool), typeid(cv.begin() >= v.end()));

	EXPECT_FALSE(v.begin() >= v.end());
	EXPECT_FALSE(cv.begin() >= cv.end());
	EXPECT_FALSE(v.begin() >= cv.end());
	EXPECT_FALSE(cv.begin() >= v.end());

	EXPECT_TRUE(v.end() >= v.begin());
	EXPECT_TRUE(cv.end() >= cv.begin());
	EXPECT_TRUE(v.end() >= cv.begin());
	EXPECT_TRUE(cv.end() >= v.begin());

	EXPECT_TRUE(v.end() >= v.end());
	EXPECT_TRUE(cv.end() >= cv.end());
	EXPECT_TRUE(v.end() >= cv.end());
	EXPECT_TRUE(cv.end() >= v.end());
}

TEST_F(vector, iterator3)
{
	Vector                 v;
	Vector::const_iterator it = v.begin();
	EXPECT_TRUE(v.begin() == it);
	it = v.end();
	EXPECT_TRUE(v.end() == it);
}

TEST_F(vector, iterator6)
{
	Vector::iterator it;
	Vector::const_iterator c_it;
	c_it = it;
}

TEST_F(vector, iterator1)
{
	// Vector       v(1, 1);
	// (void)v;
	ftc::Data a[] = {1, 2, 3};
	Vector    v1(a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v1.begin(), v1.end() - 3);
	EXPECT_EQ((v1.begin() + 1) = v1.end(), v1.end());
}
