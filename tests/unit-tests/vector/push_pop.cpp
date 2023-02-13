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

TEST_F(vector, push_back)
{
	Vector v;
	size_t cap = 1;

	for (size_t i = 0; i < 17; i++) {
		v.push_back(i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v.size(), i + 1U);
		ASSERT_EQ(v[i], ftc::Data(i));
		ASSERT_EQ(ftc::Data(0), *v.begin());
		ASSERT_EQ(ftc::Data(i), *(v.end() - 1));
		if (v.size() == v.capacity()) {
			cap *= 2;
		}
	}
}

TEST_F(vector, push_back_exception)
{
	Vector v;
	size_t cap = 1;

	// ftc::PrintOn _;
	AllocExceptionOn _;
	for (size_t i = 0, j = 0; i < 100; i++) {
		try {
			// TODO operator==
			ftc::ExceptionOn _;
			v.push_back(i);
		} catch (std::runtime_error &e) {
			// std::cout << e.what() << std::endl;
			continue;
		}
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v.size(), j + 1U);
		ASSERT_EQ(v[j], ftc::Data(i));
		ASSERT_EQ(*(v.end() - 1), ftc::Data(i));
		if (v.size() == v.capacity()) {
			cap *= 2;
		}
		j++;
	}
}

TEST_F(vector, pop_back)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.pop_back();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a)));
}

TEST_F(vector, pop_back2)
{
	size_t    a[]   = {2, 3};
	ftc::Data res[] = {2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	v.pop_back();
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(res));
	for (size_t i = 0; i < ARRAY_SIZE(res); i++) {
		EXPECT_EQ(v[i], res[i]);
	}
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + ARRAY_SIZE(a) - ARRAY_SIZE(res)));
}

TEST_F(vector, pop_back_exception)
{
	size_t a[] = {1};
	Vector v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);
	EXPECT_NO_THROW(v.pop_back());
}

TEST_F(vector, pop_back_exception2)
{
	size_t    a[]   = {2, 3};
	ftc::Data res[] = {2};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);
	EXPECT_NO_THROW(v.pop_back());
}
