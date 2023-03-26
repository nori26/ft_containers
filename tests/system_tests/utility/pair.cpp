#include "gtest.h"

#include <string>
#include <typeinfo>
#include <utility>

#ifdef FT_TEST
  #include "utility.hpp"
#else
namespace ft = std;
#endif

using namespace std::rel_ops;

TEST(pair, basic)
{
	ft::pair<int, int> a;
}

TEST(pair, copy)
{
	ft::pair<int, int> p = ft::pair<char, char>();
	(void)p;
}

TEST(pair, operator_eq)
{
	{
		ft::pair<int, int>       p;
		const ft::pair<int, int> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<int, int>       p  = ft::pair<int, int>(1, 2);
		const ft::pair<int, int> cp = ft::pair<int, int>(1, 2);

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<int, int>       p;
		ft::pair<int, int>       p2 = ft::pair<int, int>(1, 0);
		ft::pair<int, int>       p3 = ft::pair<int, int>(0, 1);
		ft::pair<int, int>       p4 = ft::pair<int, int>(2, 2);
		const ft::pair<int, int> cp;
		const ft::pair<int, int> cp2 = p2;
		const ft::pair<int, int> cp3 = p3;
		const ft::pair<int, int> cp4 = p4;

		EXPECT_FALSE(p == p2);
		EXPECT_FALSE(p == p3);
		EXPECT_FALSE(p == p4);
		EXPECT_FALSE(p2 == p3);
		EXPECT_FALSE(p2 == p4);
		EXPECT_FALSE(p3 == p4);

		EXPECT_FALSE(cp == cp2);
		EXPECT_FALSE(cp == cp3);
		EXPECT_FALSE(cp == cp4);
		EXPECT_FALSE(cp2 == cp3);
		EXPECT_FALSE(cp2 == cp4);
		EXPECT_FALSE(cp3 == cp4);

		EXPECT_FALSE(cp == p2);
		EXPECT_FALSE(cp == p3);
		EXPECT_FALSE(cp == p4);
		EXPECT_FALSE(cp2 == p3);
		EXPECT_FALSE(cp2 == p4);
		EXPECT_FALSE(cp3 == p4);

		EXPECT_FALSE(p == cp2);
		EXPECT_FALSE(p == cp3);
		EXPECT_FALSE(p == cp4);
		EXPECT_FALSE(p2 == cp3);
		EXPECT_FALSE(p2 == cp4);
		EXPECT_FALSE(p3 == cp4);
	}
	{
		ft::pair<int, std::string>       p;
		const ft::pair<int, std::string> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<int, std::string>       p  = ft::pair<int, std::string>(1, "2");
		const ft::pair<int, std::string> cp = ft::pair<int, std::string>(1, "2");

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<int, std::string>       p;
		ft::pair<int, std::string>       p2 = ft::pair<int, std::string>(1, "0");
		ft::pair<int, std::string>       p3 = ft::pair<int, std::string>(0, "1");
		ft::pair<int, std::string>       p4 = ft::pair<int, std::string>(2, "2");
		const ft::pair<int, std::string> cp;
		const ft::pair<int, std::string> cp2 = p2;
		const ft::pair<int, std::string> cp3 = p3;
		const ft::pair<int, std::string> cp4 = p4;

		EXPECT_FALSE(p == p2);
		EXPECT_FALSE(p == p3);
		EXPECT_FALSE(p == p4);
		EXPECT_FALSE(p2 == p3);
		EXPECT_FALSE(p2 == p4);
		EXPECT_FALSE(p3 == p4);

		EXPECT_FALSE(cp == cp2);
		EXPECT_FALSE(cp == cp3);
		EXPECT_FALSE(cp == cp4);
		EXPECT_FALSE(cp2 == cp3);
		EXPECT_FALSE(cp2 == cp4);
		EXPECT_FALSE(cp3 == cp4);

		EXPECT_FALSE(cp == p2);
		EXPECT_FALSE(cp == p3);
		EXPECT_FALSE(cp == p4);
		EXPECT_FALSE(cp2 == p3);
		EXPECT_FALSE(cp2 == p4);
		EXPECT_FALSE(cp3 == p4);

		EXPECT_FALSE(p == cp2);
		EXPECT_FALSE(p == cp3);
		EXPECT_FALSE(p == cp4);
		EXPECT_FALSE(p2 == cp3);
		EXPECT_FALSE(p2 == cp4);
		EXPECT_FALSE(p3 == cp4);
	}
	{
		ft::pair<std::string, int>       p;
		const ft::pair<std::string, int> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<std::string, int>       p  = ft::pair<std::string, int>("1", 2);
		const ft::pair<std::string, int> cp = ft::pair<std::string, int>("1", 2);

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<std::string, int>       p;
		ft::pair<std::string, int>       p2 = ft::pair<std::string, int>("1", 0);
		ft::pair<std::string, int>       p3 = ft::pair<std::string, int>("0", 1);
		ft::pair<std::string, int>       p4 = ft::pair<std::string, int>("2", 2);
		const ft::pair<std::string, int> cp;
		const ft::pair<std::string, int> cp2 = p2;
		const ft::pair<std::string, int> cp3 = p3;
		const ft::pair<std::string, int> cp4 = p4;

		EXPECT_FALSE(p == p2);
		EXPECT_FALSE(p == p3);
		EXPECT_FALSE(p == p4);
		EXPECT_FALSE(p2 == p3);
		EXPECT_FALSE(p2 == p4);
		EXPECT_FALSE(p3 == p4);

		EXPECT_FALSE(cp == cp2);
		EXPECT_FALSE(cp == cp3);
		EXPECT_FALSE(cp == cp4);
		EXPECT_FALSE(cp2 == cp3);
		EXPECT_FALSE(cp2 == cp4);
		EXPECT_FALSE(cp3 == cp4);

		EXPECT_FALSE(cp == p2);
		EXPECT_FALSE(cp == p3);
		EXPECT_FALSE(cp == p4);
		EXPECT_FALSE(cp2 == p3);
		EXPECT_FALSE(cp2 == p4);
		EXPECT_FALSE(cp3 == p4);

		EXPECT_FALSE(p == cp2);
		EXPECT_FALSE(p == cp3);
		EXPECT_FALSE(p == cp4);
		EXPECT_FALSE(p2 == cp3);
		EXPECT_FALSE(p2 == cp4);
		EXPECT_FALSE(p3 == cp4);
	}
}

TEST(pair, operator_ne)
{
	{
		ft::pair<int, int>       p;
		const ft::pair<int, int> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<int, int>       p  = ft::pair<int, int>(1, 2);
		const ft::pair<int, int> cp = ft::pair<int, int>(1, 2);

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<int, int>       p;
		ft::pair<int, int>       p2 = ft::pair<int, int>(1, 0);
		ft::pair<int, int>       p3 = ft::pair<int, int>(0, 1);
		ft::pair<int, int>       p4 = ft::pair<int, int>(2, 2);
		const ft::pair<int, int> cp;
		const ft::pair<int, int> cp2 = p2;
		const ft::pair<int, int> cp3 = p3;
		const ft::pair<int, int> cp4 = p4;

		EXPECT_TRUE(p != p2);
		EXPECT_TRUE(p != p3);
		EXPECT_TRUE(p != p4);
		EXPECT_TRUE(p2 != p3);
		EXPECT_TRUE(p2 != p4);
		EXPECT_TRUE(p3 != p4);

		EXPECT_TRUE(cp != cp2);
		EXPECT_TRUE(cp != cp3);
		EXPECT_TRUE(cp != cp4);
		EXPECT_TRUE(cp2 != cp3);
		EXPECT_TRUE(cp2 != cp4);
		EXPECT_TRUE(cp3 != cp4);

		EXPECT_TRUE(cp != p2);
		EXPECT_TRUE(cp != p3);
		EXPECT_TRUE(cp != p4);
		EXPECT_TRUE(cp2 != p3);
		EXPECT_TRUE(cp2 != p4);
		EXPECT_TRUE(cp3 != p4);

		EXPECT_TRUE(p != cp2);
		EXPECT_TRUE(p != cp3);
		EXPECT_TRUE(p != cp4);
		EXPECT_TRUE(p2 != cp3);
		EXPECT_TRUE(p2 != cp4);
		EXPECT_TRUE(p3 != cp4);
	}
	{
		ft::pair<int, std::string>       p;
		const ft::pair<int, std::string> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<int, std::string>       p  = ft::pair<int, std::string>(1, "2");
		const ft::pair<int, std::string> cp = ft::pair<int, std::string>(1, "2");

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<int, std::string>       p;
		ft::pair<int, std::string>       p2 = ft::pair<int, std::string>(1, "0");
		ft::pair<int, std::string>       p3 = ft::pair<int, std::string>(0, "1");
		ft::pair<int, std::string>       p4 = ft::pair<int, std::string>(2, "2");
		const ft::pair<int, std::string> cp;
		const ft::pair<int, std::string> cp2 = p2;
		const ft::pair<int, std::string> cp3 = p3;
		const ft::pair<int, std::string> cp4 = p4;

		EXPECT_TRUE(p != p2);
		EXPECT_TRUE(p != p3);
		EXPECT_TRUE(p != p4);
		EXPECT_TRUE(p2 != p3);
		EXPECT_TRUE(p2 != p4);
		EXPECT_TRUE(p3 != p4);

		EXPECT_TRUE(cp != cp2);
		EXPECT_TRUE(cp != cp3);
		EXPECT_TRUE(cp != cp4);
		EXPECT_TRUE(cp2 != cp3);
		EXPECT_TRUE(cp2 != cp4);
		EXPECT_TRUE(cp3 != cp4);

		EXPECT_TRUE(cp != p2);
		EXPECT_TRUE(cp != p3);
		EXPECT_TRUE(cp != p4);
		EXPECT_TRUE(cp2 != p3);
		EXPECT_TRUE(cp2 != p4);
		EXPECT_TRUE(cp3 != p4);

		EXPECT_TRUE(p != cp2);
		EXPECT_TRUE(p != cp3);
		EXPECT_TRUE(p != cp4);
		EXPECT_TRUE(p2 != cp3);
		EXPECT_TRUE(p2 != cp4);
		EXPECT_TRUE(p3 != cp4);
	}
	{
		ft::pair<std::string, int>       p;
		const ft::pair<std::string, int> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<std::string, int>       p  = ft::pair<std::string, int>("1", 2);
		const ft::pair<std::string, int> cp = ft::pair<std::string, int>("1", 2);

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<std::string, int>       p;
		ft::pair<std::string, int>       p2 = ft::pair<std::string, int>("1", 0);
		ft::pair<std::string, int>       p3 = ft::pair<std::string, int>("0", 1);
		ft::pair<std::string, int>       p4 = ft::pair<std::string, int>("2", 2);
		const ft::pair<std::string, int> cp;
		const ft::pair<std::string, int> cp2 = p2;
		const ft::pair<std::string, int> cp3 = p3;
		const ft::pair<std::string, int> cp4 = p4;

		EXPECT_TRUE(p != p2);
		EXPECT_TRUE(p != p3);
		EXPECT_TRUE(p != p4);
		EXPECT_TRUE(p2 != p3);
		EXPECT_TRUE(p2 != p4);
		EXPECT_TRUE(p3 != p4);

		EXPECT_TRUE(cp != cp2);
		EXPECT_TRUE(cp != cp3);
		EXPECT_TRUE(cp != cp4);
		EXPECT_TRUE(cp2 != cp3);
		EXPECT_TRUE(cp2 != cp4);
		EXPECT_TRUE(cp3 != cp4);

		EXPECT_TRUE(cp != p2);
		EXPECT_TRUE(cp != p3);
		EXPECT_TRUE(cp != p4);
		EXPECT_TRUE(cp2 != p3);
		EXPECT_TRUE(cp2 != p4);
		EXPECT_TRUE(cp3 != p4);

		EXPECT_TRUE(p != cp2);
		EXPECT_TRUE(p != cp3);
		EXPECT_TRUE(p != cp4);
		EXPECT_TRUE(p2 != cp3);
		EXPECT_TRUE(p2 != cp4);
		EXPECT_TRUE(p3 != cp4);
	}
}

TEST(make_pair, LWG181)
{
	ft::make_pair("abc", 3);
}
