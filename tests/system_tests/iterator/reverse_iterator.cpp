#include "gtest.h"

#include <typeinfo>
#include <vector>

#include "allocator.hpp"
#include "data.hpp"
#include "type_utils.hpp"

#ifdef FT_TEST
  #include "iterator.hpp"
#else
  #include <iterator>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

typedef std::vector<ftc::Data, ftc::Allocator<ftc::Data> > Vector;
typedef ft::reverse_iterator<Vector::iterator>             RevIter;
typedef ft::reverse_iterator<Vector::const_iterator>       ConstRevIter;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

using namespace std::rel_ops;

// TODO input bidirectional output...

TEST(reverse_iterator, types)
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

TEST(reverse_iterator, types_const)
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

TEST(reverse_iterator, constructor)
{
	Vector        v(1, 1);
	RevIter       it(v.end());
	RevIter       it2;
	RevIter       it3;
	const RevIter it4 = RevIter(v.end());
	const RevIter it5 = it2;

	(void)it4;
	(void)it5;
	EXPECT_EQ(it, RevIter(v.end()));
	EXPECT_EQ(it2, it3);

	ConstRevIter       cit(RevIter(v.end()));
	ConstRevIter       cit2;
	ConstRevIter       cit3;
	const ConstRevIter cit4 = RevIter(v.end());
	const ConstRevIter cit5 = it2;

	(void)cit4;
	(void)cit5;
	EXPECT_EQ(cit, RevIter(v.end()));
	EXPECT_EQ(cit2, cit3);
}

TEST(reverse_iterator, op_assign)
{
	Vector        v(1, 1);
	RevIter       it;
	RevIter       it2;
	const RevIter it3 = RevIter(v.end());

	it                       = RevIter(v.end());
	(it2 = RevIter(v.end())) = RevIter(v.begin());
	EXPECT_EQ(it, RevIter(v.end()));
	EXPECT_EQ(it2, RevIter(v.begin()));
	it2 = it3;
	EXPECT_EQ(it2, it3);

	const Vector       cv = v;
	ConstRevIter       cit;
	ConstRevIter       cit2;
	const ConstRevIter cit3 = ConstRevIter(cv.end());

	cit                             = ConstRevIter(cv.end());
	(cit2 = ConstRevIter(cv.end())) = ConstRevIter(cv.begin());
	EXPECT_EQ(cit, ConstRevIter(cv.end()));
	EXPECT_EQ(cit2, ConstRevIter(cv.begin()));
	cit2 = cit3;
	EXPECT_EQ(cit2, cit3);
}

TEST(reverse_iterator, op_assign_plus)
{
	Vector  v(1, 1);
	RevIter it  = RevIter(v.end());
	RevIter it2 = RevIter(v.end());

	it += 1;
	(it2 += 1) += 1;
	EXPECT_EQ(it, RevIter(v.begin()));
	EXPECT_EQ(it2, RevIter(v.begin()) + 1);

	it += -1;
	(it2 += -1) += -1;
	EXPECT_EQ(it, RevIter(v.end()));
	EXPECT_EQ(it2, RevIter(v.end()));

	const Vector cv   = v;
	ConstRevIter cit  = ConstRevIter(cv.end());
	ConstRevIter cit2 = ConstRevIter(cv.end());

	cit += 1;
	(cit2 += 1) += 1;
	EXPECT_EQ(cit, ConstRevIter(cv.begin()));
	EXPECT_EQ(cit2, ConstRevIter(cv.begin()) + 1);

	cit += -1;
	(cit2 += -1) += -1;
	EXPECT_EQ(cit, ConstRevIter(cv.end()));
	EXPECT_EQ(cit2, ConstRevIter(cv.end()));
}

TEST(reverse_iterator, op_assign_minus)
{
	Vector  v(1, 1);
	RevIter it  = RevIter(v.begin());
	RevIter it2 = RevIter(v.begin());

	it -= 1;
	(it2 -= 1) -= 1;
	EXPECT_EQ(it, RevIter(v.end()));
	EXPECT_EQ(it2, RevIter(v.end()) - 1);

	it -= -1;
	(it2 -= -1) -= -1;
	EXPECT_EQ(it, RevIter(v.begin()));
	EXPECT_EQ(it2, RevIter(v.begin()));

	const Vector cv   = v;
	ConstRevIter cit  = ConstRevIter(cv.begin());
	ConstRevIter cit2 = ConstRevIter(cv.begin());

	cit -= 1;
	(cit2 -= 1) -= 1;
	EXPECT_EQ(cit, ConstRevIter(cv.end()));
	EXPECT_EQ(cit2, ConstRevIter(cv.end()) - 1);

	cit -= -1;
	(cit2 -= -1) -= -1;
	EXPECT_EQ(cit, ConstRevIter(cv.begin()));
	EXPECT_EQ(cit2, ConstRevIter(cv.begin()));
}

TEST(reverse_iterator, empty)
{
	Vector       v;
	const Vector cv;

	EXPECT_TRUE(RevIter(v.end()) == RevIter(v.begin()));
	EXPECT_TRUE(RevIter(v.end()) >= RevIter(v.begin()));
	EXPECT_TRUE(RevIter(v.end()) <= RevIter(v.begin()));
	EXPECT_FALSE(RevIter(v.end()) != RevIter(v.begin()));
	EXPECT_FALSE(RevIter(v.end()) < RevIter(v.begin()));
	EXPECT_FALSE(RevIter(v.end()) > RevIter(v.begin()));
	EXPECT_EQ(RevIter(v.end()) - RevIter(v.begin()), 0);
	EXPECT_EQ(RevIter(v.end()) - 0, RevIter(v.end()));
	EXPECT_EQ(RevIter(v.end()) + 0, RevIter(v.end()));
	EXPECT_EQ(++RevIter(v.end()), RevIter(v.end()) + 1);
	EXPECT_EQ(RevIter(v.end())++, RevIter(v.end()));
	EXPECT_EQ(--RevIter(v.end()), RevIter(v.end()) - 1);
	EXPECT_EQ(RevIter(v.end())--, RevIter(v.end()));

	EXPECT_TRUE(ConstRevIter(cv.end()) == ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) >= ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) <= ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) != ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) < ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) > ConstRevIter(cv.begin()));
	EXPECT_EQ(ConstRevIter(cv.end()) - ConstRevIter(cv.begin()), 0);
	EXPECT_EQ(ConstRevIter(cv.end()) - 0, ConstRevIter(cv.end()));
	EXPECT_EQ(ConstRevIter(cv.end()) + 0, ConstRevIter(cv.end()));
	EXPECT_EQ(++ConstRevIter(cv.end()), ConstRevIter(cv.end()) + 1);
	EXPECT_EQ(ConstRevIter(cv.end())++, ConstRevIter(cv.end()));
	EXPECT_EQ(--ConstRevIter(cv.end()), ConstRevIter(cv.end()) - 1);
	EXPECT_EQ(ConstRevIter(cv.end())--, ConstRevIter(cv.end()));
}

TEST(reverse_iterator, op_indirection)
{
	Vector       v(1, 1);
	RevIter      b  = RevIter(v.end());
	ConstRevIter cb = RevIter(v.end());

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

TEST(reverse_iterator, op_indirection_const)
{
	Vector             v(1, 1);
	const RevIter      b  = RevIter(v.end());
	const ConstRevIter cb = RevIter(v.end());

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

TEST(reverse_iterator, op_subscript)
{
	ftc::Data          a[] = {1, 2, 3};
	Vector             v(a, a + ARRAY_SIZE(a));
	const RevIter      b  = RevIter(v.end()) + 1;
	const ConstRevIter cb = RevIter(v.end()) + 1;

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

TEST(reverse_iterator, op_subscript_const)
{
	ftc::Data    a[] = {1, 2, 3};
	Vector       v(a, a + ARRAY_SIZE(a));
	RevIter      b  = RevIter(v.end()) + 1;
	ConstRevIter cb = RevIter(v.end()) + 1;

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

TEST(reverse_iterator, op_allow)
{
	Vector       v(1, 1);
	RevIter      b  = RevIter(v.end());
	ConstRevIter cb = RevIter(v.end());

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST(reverse_iterator, op_allow_const)
{
	Vector             v(1, 1);
	const RevIter      b  = RevIter(v.end());
	const ConstRevIter cb = RevIter(v.end());

	EXPECT_EQ(typeid(b->p), typeid(int *));

	EXPECT_EQ(b->p[0], 1);
	EXPECT_EQ(cb->p[0], 1);
	b->p[0] = 2;
	EXPECT_EQ(b->p[0], 2);
}

TEST(reverse_iterator, op_inc)
{
	Vector  v(1, 1);
	RevIter b = RevIter(v.end());

	const RevIter &pre1  = ++b;
	const RevIter &pre2  = ++b;
	const RevIter &post1 = b++;
	const RevIter &post2 = b++;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(RevIter(v.end())++, RevIter(v.end()));
	EXPECT_EQ(++RevIter(v.end()), RevIter(v.begin()));
}

TEST(reverse_iterator, op_dec)
{
	Vector  v(1, 1);
	RevIter b = RevIter(v.end());

	const RevIter &pre1  = --b;
	const RevIter &pre2  = --b;
	const RevIter &post1 = b--;
	const RevIter &post2 = b--;

	EXPECT_EQ(&pre1, &pre2);
	EXPECT_NE(&post1, &post2);

	EXPECT_EQ(RevIter(v.begin())--, RevIter(v.begin()));
	EXPECT_EQ(--RevIter(v.begin()), RevIter(v.end()));
}

TEST(reverse_iterator, op_plus)
{
	Vector             v(1, 1);
	const Vector      &cv = v;
	const RevIter      b  = RevIter(v.end());
	const ConstRevIter cb = ConstRevIter(cv.end());

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

	EXPECT_EQ(b + 1, RevIter(v.begin()));
	EXPECT_EQ(1 + b, RevIter(v.begin()));
	EXPECT_EQ(cb + 1, ConstRevIter(cv.begin()));
	EXPECT_EQ(1 + cb, ConstRevIter(cv.begin()));

	EXPECT_EQ(RevIter(v.begin()) + -1, RevIter(v.end()));
	EXPECT_EQ(-1 + RevIter(v.begin()), RevIter(v.end()));
	EXPECT_EQ(ConstRevIter(cv.begin()) + -1, ConstRevIter(cv.end()));
	EXPECT_EQ(-1 + ConstRevIter(cv.begin()), ConstRevIter(cv.end()));
}

TEST(reverse_iterator, op_minus)
{
	Vector             v(1, 1);
	const Vector      &cv = v;
	const RevIter      b  = RevIter(v.begin());
	const ConstRevIter cb = ConstRevIter(cv.begin());

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

	EXPECT_EQ(b - 1, RevIter(v.end()));
	EXPECT_EQ(cb - 1, ConstRevIter(cv.end()));
	EXPECT_EQ(b - b, 0);
	EXPECT_EQ(cb - cb, 0);
	EXPECT_EQ(b - cb, 0);
	EXPECT_EQ(cb - b, 0);

	EXPECT_EQ(RevIter(v.end()) - -1, RevIter(v.begin()));
	EXPECT_EQ(ConstRevIter(cv.end()) - -1, ConstRevIter(cv.begin()));
}

TEST(reverse_iterator, op_eq)
{
	Vector        v(1, 1);
	const RevIter b = RevIter(v.end());
	const RevIter e = RevIter(v.begin());

	EXPECT_TRUE(b == b);
	EXPECT_TRUE(b == RevIter(v.end()));
	EXPECT_TRUE(RevIter(v.end()) == b);
	EXPECT_FALSE(b == e);
	EXPECT_FALSE(b == RevIter(v.begin()));
	EXPECT_FALSE(RevIter(v.begin()) == b);

	const Vector      &cv = v;
	const ConstRevIter cb = ConstRevIter(cv.end());
	const ConstRevIter ce = ConstRevIter(cv.begin());

	EXPECT_TRUE(cb == cb);
	EXPECT_TRUE(cb == ConstRevIter(cv.end()));
	EXPECT_TRUE(ConstRevIter(cv.end()) == cb);

	EXPECT_FALSE(cb == ce);
	EXPECT_FALSE(cb == ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) == cb);

	EXPECT_TRUE(cb == b);
	EXPECT_TRUE(b == cb);
	EXPECT_TRUE(cb == RevIter(v.end()));
	EXPECT_TRUE(RevIter(v.end()) == cb);

	EXPECT_FALSE(cb == e);
	EXPECT_FALSE(e == cb);
	EXPECT_FALSE(cb == RevIter(v.begin()));
	EXPECT_FALSE(RevIter(v.begin()) == cb);

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) == RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) == ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) == ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) == RevIter(v.begin())));
}

TEST(reverse_iterator, op_ne)
{
	Vector        v(1, 1);
	const RevIter b = RevIter(v.end());
	const RevIter e = RevIter(v.begin());

	EXPECT_FALSE(b != b);
	EXPECT_FALSE(b != RevIter(v.end()));
	EXPECT_FALSE(RevIter(v.end()) != b);
	EXPECT_TRUE(b != e);
	EXPECT_TRUE(b != RevIter(v.begin()));
	EXPECT_TRUE(RevIter(v.begin()) != b);

	const Vector      &cv = v;
	const ConstRevIter cb = ConstRevIter(cv.end());
	const ConstRevIter ce = ConstRevIter(cv.begin());

	EXPECT_FALSE(cb != cb);
	EXPECT_FALSE(cb != ConstRevIter(cv.end()));
	EXPECT_FALSE(ConstRevIter(cv.end()) != cb);

	EXPECT_TRUE(cb != ce);
	EXPECT_TRUE(cb != ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) != cb);

	EXPECT_FALSE(cb != b);
	EXPECT_FALSE(b != cb);
	EXPECT_FALSE(cb != RevIter(v.end()));
	EXPECT_FALSE(RevIter(v.end()) != cb);

	EXPECT_TRUE(cb != e);
	EXPECT_TRUE(e != cb);
	EXPECT_TRUE(cb != RevIter(v.begin()));
	EXPECT_TRUE(RevIter(v.begin()) != cb);

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) != RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) != ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) != ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) != RevIter(v.begin())));
}

TEST(reverse_iterator, op_less)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) < RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) < ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) < ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) < RevIter(v.begin())));

	EXPECT_TRUE(RevIter(v.end()) < RevIter(v.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) < ConstRevIter(cv.begin()));
	EXPECT_TRUE(RevIter(v.end()) < ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) < RevIter(v.begin()));

	EXPECT_FALSE(RevIter(v.begin()) < RevIter(v.end()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) < ConstRevIter(cv.end()));
	EXPECT_FALSE(RevIter(v.begin()) < ConstRevIter(cv.end()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) < RevIter(v.end()));

	EXPECT_FALSE(RevIter(v.begin()) < RevIter(v.begin()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) < ConstRevIter(cv.begin()));
	EXPECT_FALSE(RevIter(v.begin()) < ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) < RevIter(v.begin()));
}

TEST(reverse_iterator, op_less_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) <= RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) <= ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) <= ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) <= RevIter(v.begin())));

	EXPECT_TRUE(RevIter(v.end()) <= RevIter(v.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) <= ConstRevIter(cv.begin()));
	EXPECT_TRUE(RevIter(v.end()) <= ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.end()) <= RevIter(v.begin()));

	EXPECT_FALSE(RevIter(v.begin()) <= RevIter(v.end()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) <= ConstRevIter(cv.end()));
	EXPECT_FALSE(RevIter(v.begin()) <= ConstRevIter(cv.end()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) <= RevIter(v.end()));

	EXPECT_TRUE(RevIter(v.begin()) <= RevIter(v.begin()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) <= ConstRevIter(cv.begin()));
	EXPECT_TRUE(RevIter(v.begin()) <= ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) <= RevIter(v.begin()));
}

TEST(reverse_iterator, op_greater)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) > RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) > ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) > ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) > RevIter(v.begin())));

	EXPECT_FALSE(RevIter(v.end()) > RevIter(v.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) > ConstRevIter(cv.begin()));
	EXPECT_FALSE(RevIter(v.end()) > ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) > RevIter(v.begin()));

	EXPECT_TRUE(RevIter(v.begin()) > RevIter(v.end()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) > ConstRevIter(cv.end()));
	EXPECT_TRUE(RevIter(v.begin()) > ConstRevIter(cv.end()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) > RevIter(v.end()));

	EXPECT_FALSE(RevIter(v.begin()) > RevIter(v.begin()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) > ConstRevIter(cv.begin()));
	EXPECT_FALSE(RevIter(v.begin()) > ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.begin()) > RevIter(v.begin()));
}

TEST(reverse_iterator, op_greater_eq)
{
	Vector        v(1, 1);
	const Vector &cv = v;

	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) >= RevIter(v.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) >= ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(RevIter(v.end()) >= ConstRevIter(cv.begin())));
	EXPECT_EQ(typeid(bool), typeid(ConstRevIter(cv.end()) >= RevIter(v.begin())));

	EXPECT_FALSE(RevIter(v.end()) >= RevIter(v.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) >= ConstRevIter(cv.begin()));
	EXPECT_FALSE(RevIter(v.end()) >= ConstRevIter(cv.begin()));
	EXPECT_FALSE(ConstRevIter(cv.end()) >= RevIter(v.begin()));

	EXPECT_TRUE(RevIter(v.begin()) >= RevIter(v.end()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) >= ConstRevIter(cv.end()));
	EXPECT_TRUE(RevIter(v.begin()) >= ConstRevIter(cv.end()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) >= RevIter(v.end()));

	EXPECT_TRUE(RevIter(v.begin()) >= RevIter(v.begin()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) >= ConstRevIter(cv.begin()));
	EXPECT_TRUE(RevIter(v.begin()) >= ConstRevIter(cv.begin()));
	EXPECT_TRUE(ConstRevIter(cv.begin()) >= RevIter(v.begin()));
}

TEST(reverse_iterator, reverse_iterator1)
{
	Vector       v;
	ConstRevIter it = RevIter(v.end());
	EXPECT_TRUE(RevIter(v.end()) == it);
	it = RevIter(v.begin());
	EXPECT_TRUE(RevIter(v.begin()) == it);
}

TEST(reverse_iterator, reverse_iterator2)
{
	RevIter      it;
	ConstRevIter c_it(it);
	ConstRevIter c_it2 = it;
	c_it               = it;
	(void)c_it2;
}

TEST(reverse_iterator, reverse_iterator3)
{
	Vector       v;
	RevIter      it(v.end());
	ConstRevIter c_it(v.end());
	c_it = it;
}

TEST(reverse_iterator, reverse_iterator4)
{
	const Vector cv;
	ConstRevIter c_it(cv.end());
}
