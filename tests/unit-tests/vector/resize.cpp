#include "gtest.h"

#include <limits>
#include <memory>

#include "data.hpp"
#include "allocator.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data> Vector;
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > VectorAl;

TEST(vector, resize)
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
	v.resize(0);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 4U);
	v.resize(15);
	EXPECT_EQ(v.size(), 15U);
	EXPECT_EQ(v.capacity(), 15U);
	v.resize(17);
	EXPECT_EQ(v.size(), 17U);
	EXPECT_EQ(v.capacity(), 30U);
	v.resize(61);
	EXPECT_EQ(v.size(), 61U);
	EXPECT_EQ(v.capacity(), 61U);
}

TEST(vector, resize_over_max)
{
	Vector v;

	EXPECT_THROW(v.resize(v.max_size() + 1U), std::length_error);
	// TODO operator==
	for (size_t i = 1; i < 100; i++) {
		v.resize(i);
		v[0] = ftc::Data(i);
		size_t cap = v.capacity();
		EXPECT_THROW(v.resize(v.max_size() + 1U), std::length_error);
		EXPECT_EQ(v[0], ftc::Data(i));
		EXPECT_EQ(v.size(), i);
		EXPECT_EQ(v.capacity(), cap);
	}
}
