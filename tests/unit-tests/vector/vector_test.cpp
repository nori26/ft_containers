#include "gtest.h"

#include <limits>
#include <memory>

#include "allocator.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "vector.hpp"
#else
  #include <vector>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::vector<ftc::Data>                             Vector;
typedef ft::vector<ftc::Data, ftc::Allocator<ftc::Data> > VectorAl;

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

TEST(vector, constructor_alloc)
{
	Vector v = Vector(std::allocator<ftc::Data>());

	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	EXPECT_TRUE(v.empty());
	v.push_back(1);
	EXPECT_EQ(v[0], 1);
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

TEST(vector, push_back_except)
{
	Vector v;
	// VectorAl v;
	size_t cap = 1;

	// ftc::PrintOn _;
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

TEST(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
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
