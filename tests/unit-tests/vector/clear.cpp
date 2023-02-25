#include "gtest.h"

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

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST_F(vector, clear_ret_type)
{
	Vector v;

	EXPECT_EQ(typeid(void), typeid(v.clear()));
}

TEST_F(vector, clear_empty)
{
	Vector v;

	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear1)
{
	size_t a[1] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear2)
{
	size_t a[2] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear3)
{
	size_t a[3] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear4)
{
	size_t a[4] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear5)
{
	size_t a[5] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear6)
{
	size_t a[6] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear7)
{
	size_t a[7] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear8)
{
	size_t a[1000] = {};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, clear_append1)
{
	size_t a[1] = {};
	size_t b[1] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append2)
{
	size_t a[2] = {};
	size_t b[2] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append3)
{
	size_t a[3] = {};
	size_t b[3] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append4)
{
	size_t a[4] = {};
	size_t b[4] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append5)
{
	size_t a[5] = {};
	size_t b[5] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append6)
{
	size_t a[6] = {};
	size_t b[6] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append7)
{
	size_t a[7] = {};
	size_t b[7] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}

TEST_F(vector, clear_append8)
{
	size_t a[1000] = {};
	size_t b[1000] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.clear();
	v.insert(v.end(), b, b + ARRAY_SIZE(b));
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(b));
	for (size_t i = 0; i < ARRAY_SIZE(b); i++) {
		ASSERT_EQ(v[i], b[i]);
	}
}
