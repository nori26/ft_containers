#include "gtest.h"

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"
#include "vector_fixture.hpp"
#include <map>

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

// class CommaTest
// {
//   public:
// 	CommaTest() {}
// 	bool operator==(const CommaTest &c) const
// 	{
// 		(void)c;
// 		return true;
// 	}
// };

// static ft::vector<CommaTest>::iterator operator,(ft::vector<CommaTest>::iterator it1,
// ft::vector<CommaTest>::iterator it2)
// {
// 	(void)it2;
// 	throw std::runtime_error("");
// 	return it1;
// }

// TEST(vector, operator_eq_comma)
// {
// 	ft::vector<CommaTest> v1(10);
// 	ft::vector<CommaTest> v2(10);

// 	EXPECT_NO_THROW(v1 == v2);
// 	EXPECT_NO_THROW(v1 == v2);
// 	EXPECT_EQ(v1, v2);
// }

TEST_F(vector, operator_eq_empty)
{
	Vector v1;
	Vector v2;

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_EQ(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq_empty2)
{
	ftc::Data a2[] = {1, 2, 3};
	Vector    v1;
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 3};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_EQ(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_EQ(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq2)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 4};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq3)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne_empty)
{
	Vector v1;
	Vector v2;

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne_empty2)
{
	ftc::Data a2[] = {1, 2, 3};
	Vector    v1;
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 4};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne2)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 3};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne3)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2};
	Vector    v1(a1, a1 + ARRAY_SIZE(a1));
	Vector    v2(a2, a2 + ARRAY_SIZE(a2));

	size_t     size1     = v1.size();
	size_t     capacity1 = v1.capacity();
	size_t     size2     = v2.size();
	size_t     capacity2 = v2.capacity();
	ftc::Data *data1     = v1.data();
	ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq_empty_const)
{
	const Vector v1;
	const Vector v2;

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_EQ(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_EQ(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq_empty2_const)
{
	ftc::Data    a2[] = {1, 2, 3};
	const Vector v1;
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2, 3};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_EQ(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());

	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_EQ(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq2_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2, 4};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_eq3_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 == v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 == v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne_empty_const)
{
	const Vector v1;
	const Vector v2;

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne_empty2_const)
{
	ftc::Data    a2[] = {1, 2, 3};
	const Vector v1;
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2, 4};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne2_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2, 3};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_FALSE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_FALSE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}

TEST_F(vector, operator_ne3_const)
{
	ftc::Data    a1[] = {1, 2, 3};
	ftc::Data    a2[] = {1, 2};
	const Vector v1(a1, a1 + ARRAY_SIZE(a1));
	const Vector v2(a2, a2 + ARRAY_SIZE(a2));

	size_t           size1     = v1.size();
	size_t           capacity1 = v1.capacity();
	size_t           size2     = v2.size();
	size_t           capacity2 = v2.capacity();
	const ftc::Data *data1     = v1.data();
	const ftc::Data *data2     = v2.data();

	EXPECT_NE(v1, v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v1 != v2);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_NE(v2, v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());

	EXPECT_TRUE(v2 != v1);
	EXPECT_EQ(size1, v1.size());
	EXPECT_EQ(size2, v2.size());
	EXPECT_EQ(capacity1, v1.capacity());
	EXPECT_EQ(capacity2, v2.capacity());
	EXPECT_EQ(data1, v1.data());
	EXPECT_EQ(data2, v2.data());
}
