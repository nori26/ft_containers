#include "gtest.h"

#include <limits>
#include <list>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"
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
typedef std::istream_iterator<size_t>                     InputIter;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST_F(vector, insert_ret_type)
{
	std::list<int> l;
	Vector         v1;
	Vector         v2;

	EXPECT_EQ(typeid(void), typeid(v1.insert(v1.begin(), v2.begin(), v2.end())));
	EXPECT_EQ(typeid(void), typeid(v1.insert(v1.begin(), InputIter(), InputIter())));
	EXPECT_EQ(typeid(void), typeid(v1.insert(v1.begin(), l.begin(), l.begin())));
	EXPECT_EQ(typeid(Vector::iterator), typeid(v1.insert(v1.begin(), 1)));
}

TEST_F(vector, insert_size_t)
{
	ft::vector<size_t> v;
	size_t             ary[] = {3, 3, 3, 1, 2};
	size_t             i     = 3;
	// v.insert(v.end(), &ary, &ary + 1);
	v.insert(v.end(), i, i);
	v.insert(v.end(), 1U, 1U);
	v.insert(v.end(), 1, 2);
	for (size_t i = 0; i < ARRAY_SIZE(ary); i++) {
		EXPECT_EQ(v[i], ary[i]);
	}
}

TEST_F(vector, insert_best_viable)
{
	ft::vector<size_t> v;
	Vector             v2;

	v.insert(v.end(), 10, 1);
	EXPECT_EQ(v.size(), 10U);

	v2.insert(v2.end(), 1, 1);
	v2.insert(v2.end(), 1U, 1U);
	v2.insert(v2.end(), 1, 1U);
	v2.insert(v2.end(), 1U, 1);
	EXPECT_EQ(v2.size(), 4U);
}
// // TODO input itr, except, copy conut

TEST_F(vector, insert_empty)
{
	Vector v1;
	Vector v2;
	size_t a[] = {0, 1, 2, 3};

	v1.insert(v1.begin(), a, a + ARRAY_SIZE(a));
	v2.insert(v2.end(), a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v1[i], i);
		EXPECT_EQ(v2[i], i);
	}
}

TEST_F(vector, insert_forward)
{
	size_t a[] = {2, 3};
	size_t b[] = {0, 1};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between)
{
	size_t a[] = {0, 3};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between2)
{
	size_t a[] = {0, 3, 4};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between3)
{
	size_t a[] = {0, 3, 4, 5};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between4)
{
	size_t a[] = {0, 4};
	size_t b[] = {1, 2, 3};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_backward)
{
	size_t a[] = {0, 1};
	size_t b[] = {2, 3};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.end(), b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_forward_reserved)
{
	size_t a[] = {2, 3};
	size_t b[] = {0, 1};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_forward_reserved2)
{
	size_t a[] = {1, 2, 3};
	size_t b[] = {0};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_forward_reserved3)
{
	size_t a[] = {3};
	size_t b[] = {0, 1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between_reserved)
{
	size_t a[] = {0, 3};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between_reserved2)
{
	size_t a[] = {0, 3, 4};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between_reserved3)
{
	size_t a[] = {0, 3, 4, 5};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_between_reserved4)
{
	size_t a[] = {0, 4};
	size_t b[] = {1, 2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_backward_reserved)
{
	size_t a[] = {0, 1};
	size_t b[] = {2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.end(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_cap)
{
	Vector v;
	size_t a[] = {0, 1, 2, 3};

	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v.size(), 5U);
	EXPECT_EQ(v.capacity(), 5U);
	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 6U);
	EXPECT_EQ(v.capacity(), 10U);
}

TEST_F(vector, insert_n_empty)
{
	Vector v1;
	Vector v2;

	v1.insert(v1.begin(), 5, ftc::Data(1));
	v2.insert(v2.end(), 5, ftc::Data(1));
	EXPECT_EQ(v1.capacity(), 5U);
	EXPECT_EQ(v2.capacity(), 5U);
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(v1[i], 1);
		EXPECT_EQ(v2[i], 1);
	}
}

TEST_F(vector, insert_n_empty2)
{
	Vector v;

	v.insert(v.begin(), 0, ftc::Data(1));
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	v.insert(v.end(), 0, ftc::Data(1));
	EXPECT_EQ(v.data(), (ftc::Data *)0);
}

TEST_F(vector, insert_n_max)
{
	Vector            v;
	Vector::size_type max = std::numeric_limits<Vector::size_type>::max();

	v.insert(v.begin(), 1, ftc::Data(1));
	EXPECT_THROW(v.insert(v.begin(), max, ftc::Data(1)), std::length_error);
}

TEST_F(vector, insert_n_forward)
{
	size_t    a[]   = {2, 3};
	ftc::Data b     = 1;
	size_t    n     = 2;
	ftc::Data res[] = {1, 1, 2, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_forward2)
{
	Vector    v;
	ftc::Data left    = 0;
	ftc::Data mid     = 1;
	ftc::Data right   = 2;
	size_t    n_left  = 5;
	size_t    n_mid   = 5;
	size_t    n_right = 5;

	ftc::Data *p = v.data();
	v.insert(v.begin(), n_right, right);
	v.insert(v.begin(), n_mid, mid);
	v.insert(v.begin(), n_left, left);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), n_left + n_mid + n_right);
	for (size_t i = 0; i < n_left; i++) {
		EXPECT_EQ(v[i], left);
	}
	for (size_t i = 0; i < n_mid; i++) {
		EXPECT_EQ(v[n_left + i], mid);
	}
	for (size_t i = 0; i < n_right; i++) {
		EXPECT_EQ(v[n_left + n_mid + i], right);
	}
}

TEST_F(vector, insert_n_between)
{
	size_t    a[]   = {0, 3};
	ftc::Data b     = 1;
	size_t    n     = 2;
	ftc::Data res[] = {0, 1, 1, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between2)
{
	size_t    a[]   = {0, 2, 3};
	ftc::Data b     = 1;
	size_t    n     = 2;
	ftc::Data res[] = {0, 1, 1, 2, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between3)
{
	size_t    a[]   = {0, 2, 3, 4};
	ftc::Data b     = 1;
	size_t    n     = 2;
	ftc::Data res[] = {0, 1, 1, 2, 3, 4};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between4)
{
	size_t    a[]   = {0, 4};
	ftc::Data b     = 1;
	size_t    n     = 3;
	ftc::Data res[] = {0, 1, 1, 1, 4};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between5)
{
	Vector    v;
	ftc::Data left    = 0;
	ftc::Data mid     = 1;
	ftc::Data right   = 2;
	size_t    n_left  = 5;
	size_t    n_mid   = 5;
	size_t    n_right = 5;

	ftc::Data *p = v.data();
	v.insert(v.begin(), n_left, left);
	v.insert(v.end(), n_right, right);
	v.insert(v.begin() + n_left, n_mid, mid);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), n_left + n_mid + n_right);
	for (size_t i = 0; i < n_left; i++) {
		EXPECT_EQ(v[i], left);
	}
	for (size_t i = 0; i < n_mid; i++) {
		EXPECT_EQ(v[n_left + i], mid);
	}
	for (size_t i = 0; i < n_right; i++) {
		EXPECT_EQ(v[n_left + n_mid + i], right);
	}
}

TEST_F(vector, insert_n_backward)
{
	size_t    a[]   = {0, 1};
	ftc::Data b     = 2;
	size_t    n     = 2;
	ftc::Data res[] = {0, 1, 2, 2};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.insert(v.end(), n, b);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_forward_reserved)
{
	size_t    a[]   = {2, 3};
	ftc::Data b     = 1;
	size_t    n     = 2;
	ftc::Data res[] = {1, 1, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_forward_reserved2)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data b     = 1;
	size_t    n     = 1;
	ftc::Data res[] = {1, 1, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_forward_reserved3)
{
	size_t    a[]   = {3};
	ftc::Data b     = 1;
	size_t    n     = 3;
	ftc::Data res[] = {1, 1, 1, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between_reserved)
{
	size_t    a[]   = {1, 3};
	ftc::Data b     = 2;
	size_t    n     = 2;
	ftc::Data res[] = {1, 2, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between_reserved2)
{
	size_t    a[]   = {1, 3, 4};
	ftc::Data b     = 2;
	size_t    n     = 2;
	ftc::Data res[] = {1, 2, 2, 3, 4};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between_reserved3)
{
	size_t    a[]   = {1, 3, 4, 5};
	ftc::Data b     = 2;
	size_t    n     = 2;
	ftc::Data res[] = {1, 2, 2, 3, 4, 5};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_between_reserved4)
{
	size_t    a[]   = {1, 5};
	ftc::Data b     = 2;
	size_t    n     = 3;
	ftc::Data res[] = {1, 2, 2, 2, 5};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_backward_reserved)
{
	size_t    a[]   = {1, 2};
	ftc::Data b     = 3;
	size_t    n     = 2;
	ftc::Data res[] = {1, 2, 3, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.insert(v.end(), n, b);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_n_cap)
{
	Vector v;

	v.insert(v.end(), 1, 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.insert(v.end(), 4, 1);
	EXPECT_EQ(v.size(), 5U);
	EXPECT_EQ(v.capacity(), 5U);
	v.insert(v.end(), 1, 1);
	EXPECT_EQ(v.size(), 6U);
	EXPECT_EQ(v.capacity(), 10U);
}

TEST_F(vector, insert_one_empty)
{
	Vector v1;
	Vector v2;

	Vector::iterator it1 = v1.insert(v1.begin(), ftc::Data(1));
	Vector::iterator it2 = v2.insert(v2.end(), ftc::Data(1));
	EXPECT_EQ(it1, v1.begin());
	EXPECT_EQ(it2, v2.begin());
	EXPECT_EQ(v1.size(), 1U);
	EXPECT_EQ(v2.size(), 1U);
	EXPECT_EQ(v1.capacity(), 1U);
	EXPECT_EQ(v2.capacity(), 1U);
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v2[0], 1);
}

TEST_F(vector, insert_one_forward)
{
	size_t    a[]   = {2, 3};
	ftc::Data b     = 1;
	ftc::Data res[] = {1, 2, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin(), b);
	EXPECT_EQ(it, v.begin());
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between)
{
	size_t    a[]   = {0, 3};
	ftc::Data b     = 1;
	ftc::Data res[] = {0, 1, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between2)
{
	size_t    a[]   = {0, 2, 3};
	ftc::Data b     = 1;
	ftc::Data res[] = {0, 1, 2, 3};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between3)
{
	size_t    a[]   = {0, 2, 3, 4};
	ftc::Data b     = 1;
	ftc::Data res[] = {0, 1, 2, 3, 4};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_backward)
{
	size_t    a[]   = {0, 1};
	ftc::Data b     = 2;
	ftc::Data res[] = {0, 1, 2};
	Vector    v;

	ftc::Data *p = v.data();
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.end(), b);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_forward_reserved)
{
	size_t    a[]   = {2, 3};
	ftc::Data b     = 1;
	ftc::Data res[] = {1, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin(), b);
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_forward_reserved3)
{
	size_t    a[]   = {3};
	ftc::Data b     = 1;
	ftc::Data res[] = {1, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin(), b);
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between_reserved)
{
	size_t    a[]   = {1, 3};
	ftc::Data b     = 2;
	ftc::Data res[] = {1, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between_reserved2)
{
	size_t    a[]   = {1, 3, 4};
	ftc::Data b     = 2;
	ftc::Data res[] = {1, 2, 3, 4};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_between_reserved3)
{
	size_t    a[]   = {1, 3, 4, 5};
	ftc::Data b     = 2;
	ftc::Data res[] = {1, 2, 3, 4, 5};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.begin() + 1, b);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_backward_reserved)
{
	size_t    a[]   = {1, 2};
	ftc::Data b     = 3;
	ftc::Data res[] = {1, 2, 3};
	Vector    v;
	v.reserve(ARRAY_SIZE(res));

	ftc::Data *p = v.data();
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	Vector::iterator it = v.insert(v.end(), b);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, insert_one_cap)
{
	Vector v;

	Vector::iterator it = v.insert(v.end(), 1);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	it = v.insert(v.end(), 1);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_EQ(v.size(), 2U);
	EXPECT_EQ(v.capacity(), 2U);
	it = v.insert(v.end(), 1);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_EQ(v.size(), 3U);
	EXPECT_EQ(v.capacity(), 4U);
}

static void init_ss(std::stringstream &ss, size_t *ary, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		ss << ary[i] << " ";
	}
}

TEST_F(vector, insert_input_iter_empty)
{
	Vector            v1;
	Vector            v2;
	size_t            a[] = {0, 1, 2, 3};
	std::stringstream ss;
	std::stringstream ss2;
	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, a, ARRAY_SIZE(a));

	v1.insert(v1.begin(), InputIter(ss), InputIter());
	v2.insert(v2.end(), InputIter(ss2), InputIter());
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v1[i], i);
		EXPECT_EQ(v2[i], i);
	}
}

TEST_F(vector, insert_input_iter_forward)
{
	size_t            a[] = {2, 3};
	size_t            b[] = {0, 1};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin(), InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between)
{
	size_t            a[] = {0, 3};
	size_t            b[] = {1, 2};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between2)
{
	size_t            a[] = {0, 3, 4};
	size_t            b[] = {1, 2};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between3)
{
	size_t            a[] = {0, 3, 4, 5};
	size_t            b[] = {1, 2};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between4)
{
	size_t            a[] = {0, 4};
	size_t            b[] = {1, 2, 3};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_backward)
{
	size_t            a[] = {0, 1};
	size_t            b[] = {2, 3};
	Vector            v;
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.end(), InputIter(ss2), InputIter());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_forward_reserved)
{
	size_t a[] = {2, 3};
	size_t b[] = {0, 1};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin(), InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_forward_reserved2)
{
	size_t a[] = {1, 2, 3};
	size_t b[] = {0};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin(), InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_forward_reserved3)
{
	size_t a[] = {3};
	size_t b[] = {0, 1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin(), InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between_reserved)
{
	size_t a[] = {0, 3};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between_reserved2)
{
	size_t a[] = {0, 3, 4};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between_reserved3)
{
	size_t a[] = {0, 3, 4, 5};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_between_reserved4)
{
	size_t a[] = {0, 4};
	size_t b[] = {1, 2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.begin() + 1, InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_backward_reserved)
{
	size_t a[] = {0, 1};
	size_t b[] = {2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));
	std::stringstream ss;
	std::stringstream ss2;

	init_ss(ss, a, ARRAY_SIZE(a));
	init_ss(ss2, b, ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), InputIter(ss), InputIter());
	v.insert(v.end(), InputIter(ss2), InputIter());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_input_iter_cap)
{
	// llvm or gnuの判定わからんからとりあえずapple
#if defined(FT_TEST) || defined(__APPLE__)
	Vector            v;
	size_t            a[] = {0, 1, 2, 3};
	std::stringstream ss;
	init_ss(ss, a, ARRAY_SIZE(a));

	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.insert(v.end(), InputIter(ss), InputIter());
	EXPECT_EQ(v.size(), 5U);
	EXPECT_EQ(v.capacity(), 5U);
	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 6U);
	EXPECT_EQ(v.capacity(), 10U);
#endif
}

TEST_F(vector, insert_bidirectional_iter_empty)
{
	size_t            a[] = {0, 1, 2, 3};
	std::list<size_t> v1(a, a + ARRAY_SIZE(a));
	Vector            v2;

	v2.insert(v2.end(), a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v2[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_forward)
{
	size_t            c[] = {2, 3};
	size_t            d[] = {0, 1};
	std::list<size_t> a(c, c + ARRAY_SIZE(c));
	std::list<size_t> b(d, d + ARRAY_SIZE(d));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a.begin(), a.end());
	v.insert(v.begin(), b.begin(), b.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(c) + ARRAY_SIZE(d));
	for (size_t i = 0; i < ARRAY_SIZE(c) + ARRAY_SIZE(d); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between)
{
	size_t            a[] = {0, 3};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between2)
{
	size_t            a[] = {0, 3, 4};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between3)
{
	size_t            a[] = {0, 3, 4, 5};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between4)
{
	size_t            a[] = {0, 4};
	size_t            b[] = {1, 2, 3};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_backward)
{
	size_t            a[] = {0, 1};
	size_t            b[] = {2, 3};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.end(), d.begin(), d.end());

	EXPECT_NE(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_forward_reserved)
{
	size_t            a[] = {2, 3};
	size_t            b[] = {0, 1};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin(), d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_forward_reserved2)
{
	size_t            a[] = {1, 2, 3};
	size_t            b[] = {0};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin(), d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_forward_reserved3)
{
	size_t            a[] = {3};
	size_t            b[] = {0, 1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin(), d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between_reserved)
{
	size_t            a[] = {0, 3};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between_reserved2)
{
	size_t            a[] = {0, 3, 4};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between_reserved3)
{
	size_t            a[] = {0, 3, 4, 5};
	size_t            b[] = {1, 2};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_between_reserved4)
{
	size_t            a[] = {0, 4};
	size_t            b[] = {1, 2, 3};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.begin() + 1, d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_backward_reserved)
{
	size_t            a[] = {0, 1};
	size_t            b[] = {2, 3};
	std::list<size_t> c(a, a + ARRAY_SIZE(a));
	std::list<size_t> d(b, b + ARRAY_SIZE(b));
	Vector            v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), c.begin(), c.end());
	v.insert(v.end(), d.begin(), d.end());

	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a) + ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST_F(vector, insert_bidirectional_iter_cap)
{
	Vector            v;
	size_t            a[] = {0, 1, 2, 3};
	std::list<size_t> l(a, a + ARRAY_SIZE(a));

	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.insert(v.end(), l.begin(), l.end());
	EXPECT_EQ(v.size(), 5U);
	EXPECT_EQ(v.capacity(), 5U);
	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 6U);
	EXPECT_EQ(v.capacity(), 10U);
}
