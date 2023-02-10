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

TEST_F(vector, operator_eq_empty)
{
	Vector v;
	Vector v2;

	v2 = v;
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, operator_eq_empty2)
{
	ftc::Data a[] = {1, 2, 3};
	Vector    v;
	Vector    v2;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v2 = v;
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v.capacity(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, operator_eq_empty3)
{
	ftc::Data a[] = {1, 2, 3};
	Vector    v;
	Vector    v2;

	ftc::initv(v2, a, a + ARRAY_SIZE(a));
	v2 = v;
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, operator_eq_meta)
{
	Vector v;
	Vector v2;
	size_t cap = 129;

	v.reserve(cap);
	v2.reserve(cap + 1);
	for (size_t i = 0; i <= cap; i++) {
		v.resize(i);
		v2 = v;
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), cap + 1);
		ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	}
}

TEST_F(vector, operator_eq_meta2)
{
	Vector v;
	Vector v2;
	size_t cap = 129;

	v.reserve(cap);
	for (size_t i = 1; i <= cap; i++) {
		v.resize(i);
		v2.reserve(i - 1);
		v2 = v;
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	}
}

TEST_F(vector, operator_eq_meta3)
{
	Vector v;
	Vector v2;

	v.resize(10);
	v2.resize(5);
	v2 = v;
	EXPECT_EQ(v.size(), 10U);
	EXPECT_EQ(v.capacity(), 10U);
	EXPECT_EQ(v2.size(), 10U);
	EXPECT_EQ(v2.capacity(), 10U);
	ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, operator_eq_meta4)
{
	Vector v;
	Vector v2;

	v.resize(1000);
	v2.reserve(1000);
	v2.resize(5);
	v2 = v;
	EXPECT_EQ(v2.size(), 1000U);
	EXPECT_EQ(v2.capacity(), 1000U);
	ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, operator_eq_ret)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data a3[]  = {7, 8, 9};
	ftc::Data res[] = {7, 8, 9};
	Vector    v1;
	Vector    v2;
	Vector    v3;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	ftc::initv(v3, a3, a3 + ARRAY_SIZE(a3));
	v1 = v2 = v3;
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v1[i], res[i]);
		ASSERT_EQ(v2[i], res[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(v3[i], a3[i]);
	}
}

TEST_F(vector, operator_eq_ret2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data a3[]  = {7, 8, 9};
	ftc::Data res[] = {7, 8, 9};
	Vector    v1;
	Vector    v2;
	Vector    v3;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	ftc::initv(v3, a3, a3 + ARRAY_SIZE(a3));
	(v1 = v2) = v3;
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v1[i], res[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		ASSERT_EQ(v2[i], a2[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(v3[i], a3[i]);
	}
}

TEST_F(vector, operator_eq_ret_reserved1)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data a3[]  = {7, 8, 9, 10};
	ftc::Data res[] = {7, 8, 9, 10};
	Vector    v1;
	Vector    v2;
	Vector    v3;

	v1.reserve(ARRAY_SIZE(a1) + 1);
	v1.reserve(ARRAY_SIZE(a2) + 1);
	ftc::initv_no_reserve(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv_no_reserve(v2, a2, a2 + ARRAY_SIZE(a2));
	ftc::initv(v3, a3, a3 + ARRAY_SIZE(a3));
	v1 = v2 = v3;
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v1[i], res[i]);
		ASSERT_EQ(v2[i], res[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(v3[i], a3[i]);
	}
}

TEST_F(vector, operator_eq_ret_reserved2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data a3[]  = {7, 8, 9, 10};
	ftc::Data res[] = {7, 8, 9, 10};
	Vector    v1;
	Vector    v2;
	Vector    v3;

	v1.reserve(ARRAY_SIZE(a1) + 1);
	v1.reserve(ARRAY_SIZE(a2) + 1);
	ftc::initv_no_reserve(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv_no_reserve(v2, a2, a2 + ARRAY_SIZE(a2));
	ftc::initv(v3, a3, a3 + ARRAY_SIZE(a3));
	(v1 = v2) = v3;
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v1[i], res[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		ASSERT_EQ(v2[i], a2[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a3); i++) {
		ASSERT_EQ(v3[i], a3[i]);
	}
}

TEST_F(vector, operator_eq_val)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, operator_eq_val2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a2) - ARRAY_SIZE(a1)));
}

TEST_F(vector, operator_eq_val3)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, operator_eq_val_reserved)
{
	ftc::Data a1[]  = {1, 2, 3, 4};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data res[] = {1, 2, 3, 4};
	Vector    v1;
	Vector    v2;

	v2.reserve(ARRAY_SIZE(a1));
	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv_no_reserve(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, operator_eq_append)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3, 9};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	v2.push_back(9);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(res));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(res));
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end() - 1, v2.end()));
}

TEST_F(vector, operator_eq_append2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3, 9, 10};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2 = v1;
	v2.push_back(9);
	v2.push_back(10);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(res));
}
