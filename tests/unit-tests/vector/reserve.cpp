#include "gtest.h"

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

TEST_F(vector, reserve_0)
{
	Vector v = Vector();
	size_t i = 0;
	for (; i < 10; i++) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), i);
		ASSERT_EQ(v.size(), 0U);
		ASSERT_TRUE(v.empty());
		if (i == 0) {
			ASSERT_EQ(v.data(), (ftc::Data *)0);
		} else {
			ASSERT_NE(v.data(), (ftc::Data *)0);
		}
	}
	size_t cap = i;
	for (;; i--) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v.size(), 0U);
		ASSERT_TRUE(v.empty());
		ASSERT_NE(v.data(), (ftc::Data *)0);
		if (i == 0) {
			break;
		}
	}
}

TEST_F(vector, reserve_1)
{
	Vector v = Vector();
	v.push_back(1);
	size_t i = v.capacity();
	for (; i < 10; i++) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), i);
		ASSERT_EQ(v.size(), 1U);
		ASSERT_FALSE(v.empty());
		ASSERT_EQ(v[0], ftc::Data(1));
	}
	size_t cap = i;
	for (;; i--) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v.size(), 1U);
		ASSERT_FALSE(v.empty());
		ASSERT_EQ(v[0], ftc::Data(1));
		if (i == 0) {
			break;
		}
	}
}

TEST_F(vector, reserve_3)
{
	Vector v = Vector();
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	size_t size = v.size();
	size_t i    = v.capacity();
	for (; i < 10; i++) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), i);
		ASSERT_EQ(v.size(), size);
		ASSERT_FALSE(v.empty());
		ASSERT_EQ(v[0], ftc::Data(1));
	}
	size_t cap = i;
	for (;; i--) {
		v.reserve(i);
		ASSERT_EQ(v.capacity(), cap);
		ASSERT_EQ(v.size(), size);
		ASSERT_FALSE(v.empty());
		ASSERT_EQ(v[0], ftc::Data(1));
		if (i == 0) {
			break;
		}
	}
}

TEST_F(vector, reserve_throw)
{
	Vector v = Vector();
	// EXPECT_THROW(v.reserve(v.max_size()), std::bad_alloc);
	EXPECT_THROW(v.reserve(v.max_size() + 1U), std::length_error);
}

TEST_F(vector, reserve_same)
{
	Vector v;

	for (size_t i = 0; i < 18; i++) {
		v.reserve(0);
		Vector::pointer p = v.data();
		v.reserve(0);
		EXPECT_EQ(v.data(), p);
	}
}
