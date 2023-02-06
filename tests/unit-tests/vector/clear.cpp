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

TEST(vector, clear_empty)
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

TEST(vector, clear1)
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

TEST(vector, clear2)
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

TEST(vector, clear3)
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

TEST(vector, clear4)
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

TEST(vector, clear5)
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

TEST(vector, clear6)
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

TEST(vector, clear7)
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

TEST(vector, clear8)
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
