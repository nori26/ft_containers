#include "gtest.h"

#include <limits>

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

TEST(vector, insert_size_t)
{
	ft::vector<size_t> v;
	// size_t ary[1] = {0};
	size_t i = 3;
	// v.insert(v.end(), &ary, &ary + 1);
	v.insert(v.end(), i, i);
}

// TEST(vector, insert_cap2)
// {
// 	ft::vector<size_t> v;
// 	// size_t             a[] = {0, 1, 2, 3};

// 	v.insert(v.end(), 10, 1);
// 	std::cout << v.size() << std::endl;
// 	// v.insert(v.end(), a + 3, a);
// }
// // TODO input itr, except, copy conut

TEST(vector, insert_empty)
{
	Vector v1;
	Vector v2;
	size_t a[] = {0, 1, 2, 3};

	v1.insert(v1.begin(), a, a + ARRAY_SIZE(a));
	v2.insert(v2.end(), a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v1.capacity(), ARRAY_SIZE(a));
	EXPECT_EQ(v2.capacity(), ARRAY_SIZE(a));
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v1[i], i);
		EXPECT_EQ(v2[i], i);
	}
}

TEST(vector, insert_forward)
{
	size_t a[] = {2, 3};
	size_t b[] = {0, 1};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between)
{
	size_t a[] = {0, 3};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between2)
{
	size_t a[] = {0, 3, 4};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between3)
{
	size_t a[] = {0, 3, 4, 5};
	size_t b[] = {1, 2};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between4)
{
	size_t a[] = {0, 4};
	size_t b[] = {1, 2, 3};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_backward)
{
	size_t a[] = {0, 1};
	size_t b[] = {2, 3};
	Vector v;

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.end(), b, b + ARRAY_SIZE(b));

	EXPECT_NE(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_forward_reserved)
{
	size_t a[] = {2, 3};
	size_t b[] = {0, 1};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_forward_reserved2)
{
	size_t a[] = {1, 2, 3};
	size_t b[] = {0};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_forward_reserved3)
{
	size_t a[] = {3};
	size_t b[] = {0, 1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between_reserved)
{
	size_t a[] = {0, 3};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between_reserved2)
{
	size_t a[] = {0, 3, 4};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between_reserved3)
{
	size_t a[] = {0, 3, 4, 5};
	size_t b[] = {1, 2};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_between_reserved4)
{
	size_t a[] = {0, 4};
	size_t b[] = {1, 2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_backward_reserved)
{
	size_t a[] = {0, 1};
	size_t b[] = {2, 3};
	Vector v;
	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

	ftc::Data *p = v.data();
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	v.insert(v.end(), b, b + ARRAY_SIZE(b));

	EXPECT_EQ(v.data(), p);
	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
		EXPECT_EQ(v[i], i);
	}
}

TEST(vector, insert_cap)
{
	Vector v;
	size_t a[] = {0, 1, 2, 3};

	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 1U);
	EXPECT_EQ(v.capacity(), 1U);
	v.insert(v.end(), a, a + ARRAY_SIZE(a));
	EXPECT_EQ(v.size(), 5U);
	EXPECT_EQ(v.capacity(), 5U);
	v.insert(v.end(), a, a + 1);
	EXPECT_EQ(v.size(), 6U);
	EXPECT_EQ(v.capacity(), 10U);
}

TEST(vector, insert_n_empty)
{
	Vector v1;
	Vector v2;

	v1.insert(v1.begin(), 5, ftc::Data(1));
	v2.insert(v2.end(), 5, ftc::Data(1));
	EXPECT_EQ(v1.capacity(), 5U);
	EXPECT_EQ(v2.capacity(), 5U);
	for (size_t i = 0; i < 5; i++) {
		EXPECT_EQ(v1[i], 1);
		EXPECT_EQ(v2[i], 1);
	}
}

TEST(vector, insert_n_empty2)
{
	Vector v;

	v.insert(v.begin(), 0, ftc::Data(1));
	EXPECT_EQ(v.data(), (ftc::Data *)0);
	v.insert(v.end(), 0, ftc::Data(1));
	EXPECT_EQ(v.data(), (ftc::Data *)0);
}

TEST(vector, insert_n_max)
{
	Vector            v;
	Vector::size_type max = std::numeric_limits<Vector::size_type>::max();

	v.insert(v.begin(), 1, ftc::Data(1));
	EXPECT_THROW(v.insert(v.begin(), max, ftc::Data(1)), std::length_error);
}

// TEST(vector, insert_n_forward)
// {
// 	size_t             a[] = {2, 3};
// 	size_t             b[] = {0, 1};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between)
// {
// 	size_t             a[] = {0, 3};
// 	size_t             b[] = {1, 2};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between2)
// {
// 	size_t             a[] = {0, 3, 4};
// 	size_t             b[] = {1, 2};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between3)
// {
// 	size_t             a[] = {0, 3, 4, 5};
// 	size_t             b[] = {1, 2};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between4)
// {
// 	size_t             a[] = {0, 4};
// 	size_t             b[] = {1, 2, 3};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_backward)
// {
// 	size_t             a[] = {0, 1};
// 	size_t             b[] = {2, 3};
// 	Vector v;

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.end(), b, b + ARRAY_SIZE(b));

// 	EXPECT_NE(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_forward_reserved)
// {
// 	size_t             a[] = {2, 3};
// 	size_t             b[] = {0, 1};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_forward_reserved2)
// {
// 	size_t             a[] = {1, 2, 3};
// 	size_t             b[] = {0};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_forward_reserved3)
// {
// 	size_t             a[] = {3};
// 	size_t             b[] = {0, 1, 2};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin(), b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between_reserved)
// {
// 	size_t             a[] = {0, 3};
// 	size_t             b[] = {1, 2};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between_reserved2)
// {
// 	size_t             a[] = {0, 3, 4};
// 	size_t             b[] = {1, 2};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between_reserved3)
// {
// 	size_t             a[] = {0, 3, 4, 5};
// 	size_t             b[] = {1, 2};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_between_reserved4)
// {
// 	size_t             a[] = {0, 4};
// 	size_t             b[] = {1, 2, 3};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.begin() + 1, b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_backward_reserved)
// {
// 	size_t             a[] = {0, 1};
// 	size_t             b[] = {2, 3};
// 	Vector v;
// 	v.reserve(ARRAY_SIZE(a) + ARRAY_SIZE(b));

// 	ftc::Data *p = v.data();
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	v.insert(v.end(), b, b + ARRAY_SIZE(b));

// 	EXPECT_EQ(v.data(), p);
// 	for (size_t i = 0; i < ARRAY_SIZE(a) + ARRAY_SIZE(b); i++) {
// 		EXPECT_EQ(v[i], i);
// 	}
// }

// TEST(vector, insert_n_cap)
// {
// 	Vector v;
// 	size_t             a[] = {0, 1, 2, 3};

// 	v.insert(v.end(), a, a + 1);
// 	EXPECT_EQ(v.size(), 1U);
// 	EXPECT_EQ(v.capacity(), 1U);
// 	v.insert(v.end(), a, a + ARRAY_SIZE(a));
// 	EXPECT_EQ(v.size(), 5U);
// 	EXPECT_EQ(v.capacity(), 5U);
// 	v.insert(v.end(), a, a + 1);
// 	EXPECT_EQ(v.size(), 6U);
// 	EXPECT_EQ(v.capacity(), 10U);
// }
