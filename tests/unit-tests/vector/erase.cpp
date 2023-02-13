#include "gtest.h"

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

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST_F(vector, erase_one_forward)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(ftc::Data::IsDestructed(v.data(), v.data() + 1));
}

TEST_F(vector, erase_one_forward2)
{
	size_t    a[]   = {2, 3};
	ftc::Data res[] = {3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin());
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_forward3)
{
	size_t    a[]   = {2, 3, 4};
	ftc::Data res[] = {3, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin());
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_forward4)
{
	size_t    a[129]   = {2, 3, 4, 5};
	ftc::Data res[128] = {3, 4, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin());
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_between)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_between2)
{
	size_t    a[]   = {1, 2, 3, 4};
	ftc::Data res[] = {1, 3, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_between3)
{
	size_t    a[128]   = {1, 2, 3};
	ftc::Data res[127] = {1, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_between4)
{
	size_t    a[128]   = {1, 2, 3};
	ftc::Data res[127] = {1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 2);
	EXPECT_EQ(it, v.end() - 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_one_backward)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 1);
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, erase_one_backward2)
{
	size_t    a[]   = {2, 3};
	ftc::Data res[] = {2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 1);
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_empty)
{
	Vector v;

	Vector::iterator it = v.erase(v.begin(), v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	v.erase(v.end(), v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	v.erase(v.begin(), v.begin());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
}

TEST_F(vector, erase_nop)
{
	size_t    a[]   = {1, 2, 3, 4};
	ftc::Data res[] = {1, 2, 3, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin(), v.begin());
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, erase_nop2)
{
	size_t    a[]   = {1, 2, 3, 4};
	ftc::Data res[] = {1, 2, 3, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end(), v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
}

TEST_F(vector, erase_forward)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin(), v.begin() + 1);
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, erase_forward2)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin(), v.begin() + 1);
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_forward3)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin(), v.begin() + 2);
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_forward4)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin(), v.begin() + ARRAY_SIZE(a));
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.begin() + 2);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between2)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.begin() + 2);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between3)
{
	size_t    a[]   = {1, 2, 3, 4};
	ftc::Data res[] = {1, 3, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.begin() + 2);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between4)
{
	size_t    a[]   = {1, 2, 3, 4};
	ftc::Data res[] = {1, 4};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.begin() + 3);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between5)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 3, 4, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.begin() + 2);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between6)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 1, v.end() - 1);
	EXPECT_EQ(it, v.begin() + 1);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_between7)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 2, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin() + 2, v.end() - 1);
	EXPECT_EQ(it, v.begin() + 2);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward)
{
	size_t    a[]   = {1};
	ftc::Data res[] = {};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 1, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward2)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1, 2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 1, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward3)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1, 2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 1, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward4)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {1};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 2, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward5)
{
	size_t    a[]   = {1, 2, 3};
	ftc::Data res[] = {};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 3, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_backward6)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 3, v.end());
	EXPECT_EQ(it, v.end());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_append)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 2, 3, 4, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.end() - 3, v.end());
	v.insert(it, a + 2, a + ARRAY_SIZE(a));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, erase_push_append)
{
	size_t    a[]   = {1, 2, 3, 4, 5};
	ftc::Data res[] = {1, 2, 3, 4, 5};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.erase(v.end() - 3, v.end());
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}
