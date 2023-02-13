#include "gtest.h"

#include <limits>
#include <memory>

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

TEST_F(vector, get_allocator)
{
	ftc::Allocator<ftc::Data> a;
	const Vector              v(a);

	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
}

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

TEST_F(vector, push_back_except)
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

TEST_F(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
}
