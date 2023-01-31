#include "gtest.h"

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

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(vector, insert_empty)
{
	ft::vector<size_t> v1;
	ft::vector<size_t> v2;
	size_t             a[] = {0, 1, 2, 3};

	v1.insert(v1.begin(), a, a + ARRAY_SIZE(a));
	v2.insert(v2.end(), a, a + ARRAY_SIZE(a));
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v1[i], i);
		EXPECT_EQ(v2[i], i);
	}
}

TEST(vector, insert_between)
{
	size_t             a[] = {0, 3};
	size_t             b[] = {1, 2};
	ft::vector<size_t> enough;
	ft::vector<size_t> lack;
	enough.reserve(4);

	size_t *enough_p = enough.data();
	size_t *lack_p   = lack.data();
	enough.insert(enough.end(), a, a + ARRAY_SIZE(a));
	enough.insert(enough.begin() + 1, b, b + ARRAY_SIZE(b));
	lack.insert(lack.end(), a, a + ARRAY_SIZE(a));
	lack.insert(lack.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(enough.data(), enough_p);
	EXPECT_NE(lack.data(), lack_p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(enough[i], i);
		EXPECT_EQ(lack[i], i);
	}
}

TEST(vector, insert_forward)
{
	size_t             a[] = {2, 3};
	size_t             b[] = {0, 1};
	ft::vector<size_t> enough;
	ft::vector<size_t> lack;
	enough.reserve(4);

	size_t *enough_p = enough.data();
	size_t *lack_p   = lack.data();
	enough.insert(enough.end(), a, a + ARRAY_SIZE(a));
	enough.insert(enough.begin(), b, b + ARRAY_SIZE(b));
	lack.insert(lack.end(), a, a + ARRAY_SIZE(a));
	lack.insert(lack.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(enough.data(), enough_p);
	EXPECT_NE(lack.data(), lack_p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(enough[i], i);
		EXPECT_EQ(lack[i], i);
	}
}

TEST(vector, insert_backward)
{
	size_t             a[] = {0, 1};
	size_t             b[] = {2, 3};
	ft::vector<size_t> enough;
	ft::vector<size_t> lack;
	enough.reserve(4);

	size_t *enough_p = enough.data();
	size_t *lack_p   = lack.data();
	enough.insert(enough.end(), a, a + ARRAY_SIZE(a));
	enough.insert(enough.end(), b, b + ARRAY_SIZE(b));
	lack.insert(lack.end(), a, a + ARRAY_SIZE(a));
	lack.insert(lack.end(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(enough.data(), enough_p);
	EXPECT_NE(lack.data(), lack_p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(enough[i], i);
		EXPECT_EQ(lack[i], i);
	}
}

TEST(vector, insert_size_t)
{
	ft::vector<size_t> v;
	// size_t ary[1] = {0};
	size_t i = 3;
	// v.insert(v.end(), &ary, &ary + 1);
	v.insert(v.end(), i, i);
}

// TODO input itr
// TODO input except
