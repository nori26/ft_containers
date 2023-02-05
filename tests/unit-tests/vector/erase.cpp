#include "gtest.h"

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data>                             Vector;
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > VectorAl;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(vector, erase_one_forward)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	Vector::iterator  it  = v.erase(v.begin());
	EXPECT_EQ(it, v.begin());
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
}

TEST(vector, erase_one_forward2)
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
}

TEST(vector, erase_one_forward3)
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
}

TEST(vector, erase_one_forward4)
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
}

TEST(vector, erase_one_between)
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
}

TEST(vector, erase_one_between2)
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
}

TEST(vector, erase_one_between3)
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
}

TEST(vector, erase_one_between4)
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
}

TEST(vector, erase_one_backward)
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
}

TEST(vector, erase_one_backward2)
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
}

