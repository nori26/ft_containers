#include "gtest.h"

#include <list>

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

// If size() is ​0​, data() may or may not return a null pointer.
TEST_F(vector, default_constructor)
{
	Vector v = Vector();
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, constructor_alloc)
{
	const ftc::Allocator<ftc::Data> a;
	Vector                          v = Vector(a);

	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
	v.push_back(1);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, copy_constructor_empty)
{
	Vector v;
	Vector v2 = v;

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, copy_constructor)
{
	Vector v;
	size_t cap = 128;

	v.reserve(cap);
	for (size_t i = 0; i < cap; i++) {
		v.resize(i);
		Vector v2 = Vector(v);
		EXPECT_NE(v.data(), v2.data());
		ASSERT_EQ(v.size(), i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		ASSERT_EQ(v.get_allocator().get_id(), v2.get_allocator().get_id());
	}
}

TEST_F(vector, copy_constructor2)
{
	Vector v1;
	v1.push_back(1);

	Vector v2 = v1;
	v1[0]     = 0;
	EXPECT_NE(v1[0], v2[0]);
	EXPECT_NE(v1.data(), v2.data());
	EXPECT_EQ(v1.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, copy_constructor3)
{
	ftc::Data a1[] = {1, 2, 3};
	Vector    v1;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	Vector v2(v1);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_NE(v1.data(), v2.data());
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, copy_constructor4)
{
	ftc::Data a1[256] = {1, 2, 3};
	Vector    v1;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	Vector v2(v1);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_NE(v1.data(), v2.data());
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.get_allocator().get_id(), v2.get_allocator().get_id());
}

TEST_F(vector, range_constructor_empty)
{
	Vector v;
	Vector v2(v.begin(), v.end());

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
}

TEST_F(vector, range_constructor_empty2)
{
	const ftc::Allocator<ftc::Data> a;
	Vector                          v;
	Vector                          v2(v.begin(), v.end(), a);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, range_constructor)
{
	Vector v;
	size_t cap = 128;

	v.reserve(cap);
	for (size_t i = 0; i < cap; i++) {
		v.resize(i);
		Vector v2(v.begin(), v.end());
		EXPECT_NE(v.data(), v2.data());
		ASSERT_EQ(v.size(), i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
	}
}

TEST_F(vector, range_constructor3)
{
	Vector                          v;
	size_t                          cap = 128;
	const ftc::Allocator<ftc::Data> a;

	v.reserve(cap);
	for (size_t i = 0; i < cap; i++) {
		v.resize(i);
		Vector v2(v.begin(), v.end(), a);
		EXPECT_NE(v.data(), v2.data());
		ASSERT_EQ(v.size(), i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
	}
}

TEST_F(vector, range_constructor4)
{
	ftc::Data a1[] = {1, 2, 3};
	Vector    v1;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	Vector v2(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_NE(v1.data(), v2.data());
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
}

TEST_F(vector, range_constructor5)
{
	ftc::Data a1[256] = {1, 2, 3};
	Vector    v1;

	ftc::initv(v1, a1, a1 + ARRAY_SIZE(a1));
	Vector v2(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v1[i], a1[i]);
	}
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_NE(v1.data(), v2.data());
	EXPECT_EQ(v1.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
}

TEST_F(vector, fill_constructor_0)
{
	ftc::Data d = 3;
	size_t    n = 0;
	Vector    v(n, d);

	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
}

TEST_F(vector, fill_constructor_0_2)
{
	const ftc::Allocator<ftc::Data> a;
	ftc::Data                       d = 3;
	size_t                          n = 0;
	Vector                          v(n, d, a);

	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, fill_constructor)
{
	ftc::Data d = 3;
	size_t    n = 0;

	for (size_t i = 0; i < n; i++) {
		Vector v2(i, d);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		for (size_t j = 0; j < i; j++) {
			ASSERT_EQ(v2[i], d);
		}
	}
}

TEST_F(vector, fill_constructor3)
{
	const ftc::Allocator<ftc::Data> a;
	ftc::Data                       d = 3;
	size_t                          n = 0;

	for (size_t i = 0; i < n; i++) {
		Vector v2(i, d, a);
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
		EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
		for (size_t j = 0; j < i; j++) {
			ASSERT_EQ(v2[i], d);
		}
	}
}

static void init_ss(std::stringstream &ss, size_t *ary, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		ss << ary[i] << " ";
	}
}

TEST_F(vector, range_constructor_input_iter_empty)
{
	Vector v2 = Vector(InputIter(), InputIter());

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
}

TEST_F(vector, range_constructor_input_iter_empty2)
{
	const ftc::Allocator<ftc::Data> a;
	Vector                          v2(InputIter(), InputIter(), a);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, range_constructor_input_iter4)
{
	size_t            a1[] = {1, 2, 3};
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	InputIter it(ss);
	Vector    v2(it, InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), 4U);
}

TEST_F(vector, range_constructor_input_iter5)
{
	size_t            a1[256] = {1, 2, 3};
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	InputIter it(ss);
	Vector    v2(it, InputIter());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
}

TEST_F(vector, range_constructor_input_iter_exception_safety)
{
	size_t            a1[256] = {1, 2, 3};
	std::stringstream ss;

	init_ss(ss, a1, ARRAY_SIZE(a1));
	InputIter        it(ss);
	ftc::ExceptionOn o;
	try {
		Vector v2(it, InputIter());
	} catch (...) {
	}
}

TEST_F(vector, range_constructor_bidirectional_iter_empty)
{
	std::list<size_t> v;
	Vector            v2(v.begin(), v.end());

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
}

TEST_F(vector, range_constructor_bidirectional_iter_empty2)
{
	const ftc::Allocator<ftc::Data> a;
	std::list<size_t>               v;
	Vector                          v2(v.begin(), v.end(), a);

	EXPECT_EQ(v2.size(), 0U);
	EXPECT_EQ(v2.capacity(), 0U);
	EXPECT_EQ(v2.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v2.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, range_constructor_bidirectional_iter4)
{
	std::size_t       a1[] = {1, 2, 3};
	std::list<size_t> v1(a1, a1 + ARRAY_SIZE(a1));

	Vector v2(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
}

TEST_F(vector, range_constructor_bidirectional_iter5)
{
	std::size_t       a1[256] = {1, 2, 3};
	std::list<size_t> v1(a1, a1 + ARRAY_SIZE(a1));

	Vector v2(v1.begin(), v1.end());
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		ASSERT_EQ(v2[i], a1[i]);
	}
	EXPECT_EQ(v2.size(), ARRAY_SIZE(a1));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a1));
}
