#include "gtest.h"

#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "cmp.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "algorithm.hpp"
#else
  #include <algorithm>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(lexicographical_compare, empty)
{
	std::vector<int> v1;
	std::vector<int> v2;

	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<int>));
}

TEST(lexicographical_compare, empty_empty_self)
{
	std::vector<int> v1;

	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v1.begin(), v1.end()));
	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v1.begin(), v1.end(), cmp<int>));
}

TEST(lexicographical_compare, basic_self)
{
	ftc::Data a[] = {1, 2, 3};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), a + 1, a + ARRAY_SIZE(a)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, basic_same)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a) - 1, b + 1, b + ARRAY_SIZE(b)));
	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b + 1, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b) - 1));
	EXPECT_FALSE(ft::lexicographical_compare(a + 1, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
}

TEST(lexicographical_compare, basic_diff)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 4};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(b, b + ARRAY_SIZE(b), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, diff_itr)
{
	int           a[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), s1.begin(), s1.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, set_same)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, set_diff)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 4};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()));
}

TEST(lexicographical_compare, string_same)
{
	std::string s1 = "123";
	std::string s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, string_diff)
{
	std::string s1 = "123";
	std::string s2 = "124";

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()));
}

TEST(lexicographical_compare, basic_same_cmp)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a) - 1, b + 1, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b + 1, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b) - 1, cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a + 1, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
}

TEST(lexicographical_compare, basic_diff_cmp)
{
	ftc::Data a[] = {1, 2, 3};
	ftc::Data b[] = {1, 2, 4};

	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(b, b + ARRAY_SIZE(b), a, a + ARRAY_SIZE(a), cmp<ftc::Data>)
	);
}

TEST(lexicographical_compare, diff_itr_cmp)
{
	int           a[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), s1.begin(), s1.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), a, a + ARRAY_SIZE(a), cmp<int>));
}

TEST(lexicographical_compare, set_same_cmp)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 3};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end(), cmp<int>)
	);
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>)
	);

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end(), cmp<int>)
	);
}

TEST(lexicographical_compare, set_diff_cmp)
{
	int           a[] = {1, 2, 3};
	int           b[] = {1, 2, 4};
	std::set<int> s1(a, a + ARRAY_SIZE(a));
	std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end(), cmp<int>));
}

TEST(lexicographical_compare, string_same_cmp)
{
	std::string s1 = "123";
	std::string s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end(), cmp<char>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>)
	);

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end(), cmp<char>)
	);
}

TEST(lexicographical_compare, string_diff_cmp)
{
	std::string s1 = "123";
	std::string s2 = "124";

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end(), cmp<char>)
	);
}

TEST(lexicographical_compare, comma)
{
	std::vector<CommaTest> v1(10);
	std::vector<CommaTest> v2(10);

	EXPECT_NO_THROW(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_NO_THROW(
		ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<CommaTest>)
	);
	EXPECT_TRUE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_TRUE(
		ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<CommaTest>)
	);
}

TEST(lexicographical_compare, empty_const)
{
	const std::vector<int> v1;
	const std::vector<int> v2;

	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<int>));
}

TEST(lexicographical_compare, empty_empty_self_const)
{
	const std::vector<int> v1;

	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v1.begin(), v1.end()));
	EXPECT_FALSE(ft::lexicographical_compare(v1.begin(), v1.end(), v1.begin(), v1.end(), cmp<int>));
}

TEST(lexicographical_compare, basic_self_const)
{
	const ftc::Data a[] = {1, 2, 3};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), a + 1, a + ARRAY_SIZE(a)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, basic_same_const)
{
	const ftc::Data a[] = {1, 2, 3};
	const ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a) - 1, b + 1, b + ARRAY_SIZE(b)));
	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b + 1, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b) - 1));
	EXPECT_FALSE(ft::lexicographical_compare(a + 1, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
}

TEST(lexicographical_compare, basic_diff_const)
{
	const ftc::Data a[] = {1, 2, 3};
	const ftc::Data b[] = {1, 2, 4};

	EXPECT_TRUE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b)));
	EXPECT_FALSE(ft::lexicographical_compare(b, b + ARRAY_SIZE(b), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, diff_itr_const)
{
	const int           a[] = {1, 2, 3};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), s1.begin(), s1.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), a, a + ARRAY_SIZE(a)));
}

TEST(lexicographical_compare, set_same_const)
{
	const int           a[] = {1, 2, 3};
	const int           b[] = {1, 2, 3};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));
	const std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, set_diff_const)
{
	const int           a[] = {1, 2, 3};
	const int           b[] = {1, 2, 4};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));
	const std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()));
}

TEST(lexicographical_compare, string_same_const)
{
	const std::string s1 = "123";
	const std::string s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, string_same_const2)
{
	std::string       s1 = "123";
	const std::string s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, string_same_const3)
{
	const std::string s1 = "123";
	std::string       s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end()));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end()));
}

TEST(lexicographical_compare, string_diff_const)
{
	const std::string s1 = "123";
	const std::string s2 = "124";

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()));
}

TEST(lexicographical_compare, basic_same_cmp_const)
{
	const ftc::Data a[] = {1, 2, 3};
	const ftc::Data b[] = {1, 2, 3};

	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a) - 1, b + 1, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b + 1, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b) - 1, cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(a + 1, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
}

TEST(lexicographical_compare, basic_diff_cmp_const)
{
	const ftc::Data a[] = {1, 2, 3};
	const ftc::Data b[] = {1, 2, 4};

	EXPECT_TRUE(
		ft::lexicographical_compare(a, a + ARRAY_SIZE(a), b, b + ARRAY_SIZE(b), cmp<ftc::Data>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(b, b + ARRAY_SIZE(b), a, a + ARRAY_SIZE(a), cmp<ftc::Data>)
	);
}

TEST(lexicographical_compare, diff_itr_cmp_const)
{
	const int           a[] = {1, 2, 3};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));

	EXPECT_FALSE(ft::lexicographical_compare(a, a + ARRAY_SIZE(a), s1.begin(), s1.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), a, a + ARRAY_SIZE(a), cmp<int>));
}

TEST(lexicographical_compare, set_same_cmp_const)
{
	const int           a[] = {1, 2, 3};
	const int           b[] = {1, 2, 3};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));
	const std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end(), cmp<int>)
	);
	EXPECT_FALSE(ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>)
	);

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end(), cmp<int>)
	);
}

TEST(lexicographical_compare, set_diff_cmp_const)
{
	const int           a[] = {1, 2, 3};
	const int           b[] = {1, 2, 4};
	const std::set<int> s1(a, a + ARRAY_SIZE(a));
	const std::set<int> s2(b, b + ARRAY_SIZE(b));

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<int>));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end(), cmp<int>));
}

TEST(lexicographical_compare, string_same_cmp_const)
{
	const std::string s1 = "123";
	const std::string s2 = "123";

	EXPECT_FALSE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), --s2.end(), cmp<char>)
	);
	EXPECT_FALSE(
		ft::lexicographical_compare(++s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>)
	);

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), --s1.end(), s2.begin(), s2.end(), cmp<char>)
	);
}

TEST(lexicographical_compare, string_diff_cmp_const)
{
	const std::string s1 = "123";
	const std::string s2 = "124";

	EXPECT_TRUE(ft::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp<char>));
	EXPECT_FALSE(ft::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end(), cmp<char>)
	);
}

TEST(lexicographical_compare, comma_const)
{
	const std::vector<CommaTest> v1(10);
	const std::vector<CommaTest> v2(10);

	EXPECT_NO_THROW(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_NO_THROW(
		ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<CommaTest>)
	);
	EXPECT_TRUE(ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	EXPECT_TRUE(
		ft::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end(), cmp<CommaTest>)
	);
}
