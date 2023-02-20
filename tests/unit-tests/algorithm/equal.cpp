#include "gtest.h"

#include <set>
#include <string>

#include "data.hpp"
#include "cmp.hpp"

#ifdef FT_TEST
  #include "algorithm.hpp"
#else
  #include <algorithm>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(equal, basic)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(ft::equal(a, a + ARRAY_SIZE(a), b));
	EXPECT_FALSE(ft::equal(a + 1, a + ARRAY_SIZE(a), b));
}

TEST(equal, set_true)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::equal(s1.begin(), s1.end(), s2.begin()));
	EXPECT_TRUE(ft::equal(s1.begin(), s1.end(), b));
	EXPECT_TRUE(ft::equal(b, b + ARRAY_SIZE(b), s1.begin()));
}

TEST(equal, set_false)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 4};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), s2.begin()));
	EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), b));
	EXPECT_FALSE(ft::equal(b, b + ARRAY_SIZE(b), s1.begin()));
}

TEST(equal, string_true)
{
	std::string a = "{1, 2, 3}";
	std::string b = "{1, 2, 3}";

	EXPECT_TRUE(ft::equal(a.begin(), a.end(), b.begin()));
}

TEST(equal, string_false)
{
	std::string a = "{1, 2, 3}";
	std::string b = "{1, 2, 4}";

	EXPECT_FALSE(ft::equal(a.begin(), a.end(), b.begin()));
}

TEST(equal, basic_cmp)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(ft::equal(a, a + ARRAY_SIZE(a), b, cmp<ftc::Data>));
	EXPECT_FALSE(ft::equal(a + 1, a + ARRAY_SIZE(a), b, cmp<ftc::Data>));
}

TEST(equal, set_cmp_true)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::equal(s1.begin(), s1.end(), s2.begin(), cmp<int>));
	EXPECT_TRUE(ft::equal(s1.begin(), s1.end(), b, cmp<int>));
	EXPECT_TRUE(ft::equal(b, b + ARRAY_SIZE(b), s1.begin(), cmp<int>));
}

TEST(equal, set_cmp_false)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 4};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), s2.begin(), cmp<int>));
	EXPECT_FALSE(ft::equal(s1.begin(), s1.end(), b, cmp<int>));
	EXPECT_FALSE(ft::equal(b, b + ARRAY_SIZE(b), s1.begin(), cmp<int>));
}

TEST(equal, string_cmp_true)
{
	std::string a = "{1, 2, 3}";
	std::string b = "{1, 2, 3}";

	EXPECT_TRUE(ft::equal(a.begin(), a.end(), b.begin(), cmp<char>));
}

TEST(equal, string_cmp_false)
{
	std::string a = "{1, 2, 3}";
	std::string b = "{1, 2, 4}";

	EXPECT_FALSE(ft::equal(a.begin(), a.end(), b.begin(), cmp<char>));
}

TEST(equal, comma)
{
	std::vector<CommaTest> v1(10);
	std::vector<CommaTest> v2(10);

	EXPECT_NO_THROW(ft::equal(v1.begin(), v1.end(), v2.end()));
	EXPECT_NO_THROW(ft::equal(v1.begin(), v1.end(), v2.end(), cmp<CommaTest>));
	EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.end()));
	EXPECT_TRUE(ft::equal(v1.begin(), v1.end(), v2.end(), cmp<CommaTest>));
}
