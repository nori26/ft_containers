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
typedef std::istream_iterator<size_t>                     InputIter;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

// TODO input itr
TEST_F(vector, assign_ret_type)
{
	Vector v1;
	Vector v2;

	EXPECT_EQ(typeid(void), typeid(v1.assign(v2.begin(), v2.end())));
	EXPECT_EQ(typeid(void), typeid(v1.assign(InputIter(), InputIter())));
	EXPECT_EQ(typeid(void), typeid(v1.assign(1, 1)));
}

TEST_F(vector, assign_empty)
{
	Vector v;
	Vector v2;

	v2.assign(v.begin(), v.end());
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, assign_empty2)
{
	ftc::Data a[] = {1, 2, 3};
	Vector    v;
	Vector    v2;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v2.assign(v.begin(), v.end());
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v.capacity(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, assign_empty3)
{
	ftc::Data a[] = {1, 2, 3};
	Vector    v;
	Vector    v2;

	ftc::initv(v2, a, a + ARRAY_SIZE(a));
	v2.assign(v.begin(), v.end());
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	EXPECT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, assign_meta)
{
	Vector v;
	Vector v2;
	size_t cap = 129;

	v.reserve(cap);
	v2.reserve(cap + 1);
	for (size_t i = 0; i <= cap; i++) {
		v.resize(i);
		v2.assign(v.begin(), v.end());
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), cap + 1);
		ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	}
}

TEST_F(vector, assign_meta2)
{
	Vector v;
	Vector v2;
	size_t cap = 129;

	v.reserve(cap);
	for (size_t i = 1; i <= cap; i++) {
		v.resize(i);
		v2.assign(v.begin(), v.end());
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
	}
}

TEST_F(vector, assign_meta3)
{
	Vector v;
	Vector v2;

	v.resize(10);
	v2.resize(5);
	v2.assign(v.begin(), v.end());
	EXPECT_EQ(v.size(), 10U);
	EXPECT_EQ(v.capacity(), 10U);
	EXPECT_EQ(v2.size(), 10U);
	EXPECT_EQ(v2.capacity(), 10U);
	ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, assign_meta4)
{
	Vector v;
	Vector v2;

	v.resize(1000);
	v2.reserve(1000);
	v2.resize(5);
	v2.assign(v.begin(), v.end());
	EXPECT_EQ(v2.size(), 1000U);
	EXPECT_EQ(v2.capacity(), 1000U);
	ASSERT_NE(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, assign_val)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a2) - ARRAY_SIZE(a1)));
}

TEST_F(vector, assign_val2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a2) - ARRAY_SIZE(a1)));
}

TEST_F(vector, assign_val3)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5};
	ftc::Data res[] = {1, 2, 3};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, assign_val_reserved)
{
	ftc::Data a1[]  = {1, 2, 3, 4};
	ftc::Data a2[]  = {4, 5, 6};
	ftc::Data res[] = {1, 2, 3, 4};
	Vector    v1;
	Vector    v2;

	v2.reserve(ARRAY_SIZE(a1));
	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv_no_reserve(v2, a2, a2 + ARRAY_SIZE(a2));
	// ftc::PrintOn _;
	v2.assign(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, assign_append)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3, 9};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(v1.begin(), v1.end());
	ftc::Data *p = v2.data();
	v2.push_back(9);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(res));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(res));
	EXPECT_EQ(v2.data(), p);
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end() - 1, v2.end()));
}

TEST_F(vector, assign_append2)
{
	ftc::Data a1[]  = {1, 2, 3};
	ftc::Data a2[]  = {4, 5, 6, 7};
	ftc::Data res[] = {1, 2, 3, 9, 10};
	Vector    v1;
	Vector    v2;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(v1.begin(), v1.end());
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

TEST_F(vector, assign_n_0)
{
	ftc::Data d = 3;
	size_t    n = 0;
	Vector    v;

	v.assign(n, d);
	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v.size(), n);
	EXPECT_EQ(v.capacity(), n);
}

TEST_F(vector, assign_n_empty)
{
	ftc::Data d = 3;
	size_t    n = 1;
	Vector    v;

	v.assign(n, d);
	EXPECT_EQ(v.size(), n);
	EXPECT_EQ(v.capacity(), n);
	for (size_t i = 0; i < n; i++) {
		ASSERT_EQ(v[i], d);
	}
}

TEST_F(vector, assign_n)
{
	ftc::Data d = 3;
	Vector    v;
	Vector    v2;
	size_t    cap = 129;

	for (size_t i = 1; i <= cap; i++) {
		v.assign(i, d);
		ASSERT_EQ(v.size(), i);
		ASSERT_EQ(v.capacity(), i);
		for (size_t j = 0; j < v.size(); j++) {
			ASSERT_EQ(v[j], d);
		}
	}
}

TEST_F(vector, assign_n2)
{
	ftc::Data a[5] = {};
	ftc::Data d    = 3;
	size_t    n    = 10;
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.assign(n, d);
	EXPECT_EQ(v.size(), 10U);
	EXPECT_EQ(v.capacity(), 10U);
	for (size_t i = 0; i < n; i++) {
		ASSERT_EQ(v[i], d);
	}
}

TEST_F(vector, assign_n3)
{
	ftc::Data a[] = {1, 1, 1};
	ftc::Data d   = 3;
	size_t    n   = 3;
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.assign(n, d);
	EXPECT_EQ(v.size(), n);
	EXPECT_EQ(v.capacity(), n);
	for (size_t i = 0; i < n; i++) {
		ASSERT_EQ(v[i], d);
	}
}

TEST_F(vector, assign_n4)
{
	ftc::Data a[] = {1, 1, 1, 1};
	ftc::Data d   = 3;
	size_t    n   = 3;
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.assign(n, d);
	EXPECT_EQ(v.size(), n);
	EXPECT_EQ(v.capacity(), ARRAY_SIZE(a));
	for (size_t i = 0; i < n; i++) {
		ASSERT_EQ(v[i], d);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - n));
}

TEST_F(vector, assign_n_reserved)
{
	ftc::Data d   = 3;
	size_t    cap = 129;
	Vector    v;

	v.reserve(cap + 1);
	for (size_t i = 0; i <= cap; i++) {
		v.assign(i, d);
		ASSERT_EQ(v.size(), i);
		ASSERT_EQ(v.capacity(), cap + 1);
		for (size_t j = 0; j < v.size(); j++) {
			ASSERT_EQ(v[j], d);
		}
	}
}

TEST_F(vector, assign_n_reserved2)
{
	ftc::Data a[] = {5, 5, 5, 5, 5};
	ftc::Data d   = 3;
	size_t    n   = 129;
	Vector    v;

	v.reserve(n);
	ftc::initv_no_reserve(v, a, a + ARRAY_SIZE(a));
	v.assign(n, d);
	EXPECT_EQ(v.size(), n);
	EXPECT_EQ(v.capacity(), n);
	for (size_t i = 0; i < n; i++) {
		ASSERT_EQ(v[i], d);
	}
}

TEST_F(vector, assign_n_append)
{
	ftc::Data a[]   = {4, 5, 6, 7};
	ftc::Data d     = 3;
	size_t    n     = 3;
	ftc::Data res[] = {3, 3, 3, 9, 10};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	v.assign(n, d);
	v.push_back(9);
	v.push_back(10);
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v[i], res[i]);
	}
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
}

static void init_ss(std::stringstream &ss, size_t *ary, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		ss << ary[i] << " ";
	}
}

TEST_F(vector, assign_input_iter_empty)
{
	Vector v2;

	v2.assign(InputIter(), InputIter());
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
}

TEST_F(vector, assign_input_iter_empty2)
{
	size_t            a[] = {1, 2, 3};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a, ARRAY_SIZE(a));
	v2.assign(InputIter(ss), InputIter());
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), 4U);
}

TEST_F(vector, assign_input_iter_empty3)
{
	ftc::Data a[] = {1, 2, 3};
	Vector    v2;

	ftc::initv(v2, a, a + ARRAY_SIZE(a));
	v2.assign(InputIter(), InputIter());
	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, assign_input_iter_cap)
{
	size_t ary[65] = {};
	{
		std::stringstream ss;
		init_ss(ss, ary, ARRAY_SIZE(ary));
		ft::vector<size_t> v;
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 128U);
	}
	{
		std::stringstream ss;
		init_ss(ss, ary, ARRAY_SIZE(ary));
		ft::vector<size_t> v(4);
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 128U);
	}
	{
		std::stringstream ss;
		init_ss(ss, ary, ARRAY_SIZE(ary));
		ft::vector<size_t> v(64);
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 128U);
	}
	{
		std::stringstream ss;
		init_ss(ss, ary, ARRAY_SIZE(ary));
		ft::vector<size_t> v(65);
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 65U);
	}
	{
		std::stringstream ss;
		init_ss(ss, ary, 64);
		ft::vector<size_t> v;
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 64U);
	}
	{
		std::stringstream ss;
		init_ss(ss, ary, 64);
		ft::vector<size_t> v(65);
		v.assign(InputIter(ss), InputIter());
		EXPECT_EQ(v.capacity(), 65U);
	}
}

TEST_F(vector, assign_input_iter_val)
{
	size_t            a1[]  = {1, 2, 3};
	size_t            a2[]  = {4, 5, 6};
	size_t            res[] = {1, 2, 3};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(InputIter(ss), InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a2) - ARRAY_SIZE(a1)));
}

TEST_F(vector, assign_input_iter_val2)
{
	size_t            a1[]  = {1, 2, 3};
	size_t            a2[]  = {4, 5, 6, 7};
	size_t            res[] = {1, 2, 3};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(InputIter(ss), InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end(), v2.end() + ARRAY_SIZE(a2) - ARRAY_SIZE(a1)));
}

TEST_F(vector, assign_input_iter_val3)
{
	size_t            a1[]  = {1, 2, 3};
	size_t            a2[]  = {4, 5};
	size_t            res[] = {1, 2, 3};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(InputIter(ss), InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, assign_input_iter_val_reserved)
{
	size_t            a1[]  = {1, 2, 3, 4};
	size_t            a2[]  = {4, 5, 6};
	size_t            res[] = {1, 2, 3, 4};
	Vector            v2;
	std::stringstream ss;

	v2.reserve(ARRAY_SIZE(a1));
	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv_no_reserve(v2, a2, a2 + ARRAY_SIZE(a2));
	// ftc::PrintOn _;
	v2.assign(InputIter(ss), InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
}

TEST_F(vector, assign_input_iter_append)
{
	size_t            a1[]  = {1, 2, 3};
	size_t            a2[]  = {4, 5, 6, 7};
	size_t            res[] = {1, 2, 3, 9};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(InputIter(ss), InputIter());
	ftc::Data *p = v2.data();
	v2.push_back(9);
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(res));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(res));
	EXPECT_EQ(v2.data(), p);
	EXPECT_TRUE(ftc::Data::IsDestructed(v2.end() - 1, v2.end()));
}

TEST_F(vector, assign_input_iter_append2)
{
	size_t            a1[]  = {1, 2, 3};
	size_t            a2[]  = {4, 5, 6, 7};
	size_t            res[] = {1, 2, 3, 9, 10};
	Vector            v2;
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	ftc::initv(v2, a2, a2 + ARRAY_SIZE(a2));
	v2.assign(InputIter(ss), InputIter());
	v2.push_back(9);
	v2.push_back(10);
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		ASSERT_EQ(v2[i], res[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(res));
}
