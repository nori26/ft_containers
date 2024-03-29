#include "gtest.h"

#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
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

TEST_F(vector, resize_ret_type)
{
	Vector v;

	EXPECT_EQ(typeid(void), typeid(v.resize(1)));
	EXPECT_EQ(typeid(void), typeid(v.resize(1, 1)));
}

TEST_F(vector, resize)
{
	// ftc::PrintOn _;
	Vector v;

	v.resize(0);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	v.resize(1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.resize(2);
	EXPECT_EQ(v.size(), 2U);
	EXPECT_EQ(v.capacity(), 2U);
	v.resize(3);
	EXPECT_EQ(v.size(), 3U);
	EXPECT_EQ(v.capacity(), 4U);
	ftc::Data::ClearDestructedPool();
	v.resize(0);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 4U);
	EXPECT_TRUE(ftc::Data::IsDestructed(v.end(), v.end() + 3));
	v.resize(15);
	EXPECT_EQ(v.size(), 15U);
	EXPECT_EQ(v.capacity(), 15U);
	v.resize(17);
	EXPECT_EQ(v.size(), 17U);
	EXPECT_EQ(v.capacity(), 30U);
	v.resize(61);
	EXPECT_EQ(v.size(), 61U);
	EXPECT_EQ(v.capacity(), 61U);
	v.resize(62);
	EXPECT_EQ(v.size(), 62U);
	EXPECT_EQ(v.capacity(), 122U);
	v.resize(63);
	EXPECT_EQ(v.size(), 63U);
	EXPECT_EQ(v.capacity(), 122U);
}

TEST_F(vector, resize_over_max)
{
	Vector v;

	EXPECT_THROW(v.resize(v.max_size() + 1U), std::length_error);
	// TODO operator==
	for (size_t i = 1; i < 100; i++) {
		v.resize(i);
		v[0]       = ftc::Data(i);
		size_t cap = v.capacity();
		EXPECT_THROW(v.resize(v.max_size() + 1U), std::length_error);
		EXPECT_EQ(v[0], ftc::Data(i));
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
	}
}

// TODO value, exception
