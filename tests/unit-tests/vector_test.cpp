#include "gtest.h"

#include <limits>

#include "data.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data> Vector;

TEST(vector, example)
{
	EXPECT_TRUE(true);
}

// If size() is ​0​, data() may or may not return a null pointer.
TEST(vector, default_constructor)
{
	Vector v = Vector();
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
}

TEST(vector, copy_constructor)
{
	{
		Vector v;

		v.reserve(1000);
		for (size_t i = 0; i < 1000; i++) {
			v.resize(i);
			Vector v2 = Vector(v);
			ASSERT_EQ(v2.size(), i);
			ASSERT_EQ(v2.capacity(), i);
		}
	}
	{
		Vector v1;
		v1.push_back(1);

		Vector v2 = v1;
		v1[0]     = 0;
		EXPECT_NE(v1[0], v2[0]);
	}
}

TEST(vector, push_back)
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

TEST(vector, resize)
{
	Vector v;

	std::cout << "[ resize 0 -> 0]" << std::endl;
	v.resize(0);
	std::cout << "[ end ]" << std::endl;
	// v.push_back(1);
	// v.push_back(1);
	// std::cout << "[ resize 2 -> 0]" << std::endl;
	// v.resize(0);
	// std::cout << "[ end ]" << std::endl;
	// std::cout << "[ resize 0 -> 2]" << std::endl;
	// v.resize(2);
	// std::cout << "[ end ]" << std::endl;
}

TEST(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
}

TEST(vector, reserve)
{
	{
		Vector v = Vector();
		size_t i = 0;
		for (; i < 10; i++) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), i);
			EXPECT_EQ(v.size(), 0U);
			EXPECT_TRUE(v.empty());
			if (i == 0) {
				EXPECT_EQ(v.data(), (ftc::Data *)0);
			} else {
				EXPECT_NE(v.data(), (ftc::Data *)0);
			}
		}
		size_t cap = i;
		for (;; i--) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), cap);
			EXPECT_EQ(v.size(), 0U);
			EXPECT_TRUE(v.empty());
			EXPECT_NE(v.data(), (ftc::Data *)0);
			if (i == 0) {
				break;
			}
		}
	}
	{
		Vector v = Vector();
		v.push_back(1);
		size_t i = v.capacity();
		for (; i < 10; i++) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), i);
			EXPECT_EQ(v.size(), 1U);
			EXPECT_FALSE(v.empty());
			EXPECT_EQ(v[0], ftc::Data(1));
		}
		size_t cap = i;
		for (;; i--) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), cap);
			EXPECT_EQ(v.size(), 1U);
			EXPECT_FALSE(v.empty());
			EXPECT_EQ(v[0], ftc::Data(1));
			if (i == 0) {
				break;
			}
		}
	}
	{
		Vector v = Vector();
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		size_t size = v.size();
		size_t i    = v.capacity();
		for (; i < 10; i++) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), i);
			EXPECT_EQ(v.size(), size);
			EXPECT_FALSE(v.empty());
			EXPECT_EQ(v[0], ftc::Data(1));
		}
		size_t cap = i;
		for (;; i--) {
			v.reserve(i);
			EXPECT_EQ(v.capacity(), cap);
			EXPECT_EQ(v.size(), size);
			EXPECT_FALSE(v.empty());
			EXPECT_EQ(v[0], ftc::Data(1));
			if (i == 0) {
				break;
			}
		}
	}
	{
		Vector v = Vector();
		// EXPECT_THROW(v.reserve(v.max_size()), std::bad_alloc);
		EXPECT_THROW(v.reserve(v.max_size() + 1U), std::length_error);
	}
}

TEST(vector, max_size)
{
	typedef std::allocator<ftc::Data>::difference_type difference_type;

	Vector                    v;
	std::allocator<ftc::Data> a;
	const Vector::size_type   alloc_max      = a.max_size();
	const Vector::size_type   difference_max = std::numeric_limits<difference_type>::max();
	EXPECT_EQ(std::min<Vector::size_type>(alloc_max, difference_max), v.max_size());
}

TEST(vector, operator_eq)
{
	Vector v;
	Vector v2;

	v.reserve(1000);
	for (size_t i = 0; i < 1000; i++) {
		v.resize(i);
		v2 = v;
		ASSERT_EQ(v2.size(), i);
		ASSERT_EQ(v2.capacity(), i);
	}
}
