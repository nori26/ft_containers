#include "gtest.h"

#include <string>
#include <typeinfo>
#include <utility>

#include "Elem.hpp"

#ifdef FT_TEST
  #include "utility.hpp"
#else
namespace ft = std;
#endif

namespace ftc = ft_containers;

using namespace std::rel_ops;

TEST(pair, type)
{
	EXPECT_EQ(typeid(ft::pair<int, char *>::first_type), typeid(int));
	EXPECT_EQ(typeid(ft::pair<int, char *>::second_type), typeid(char *));
}

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
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(2, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

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
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(1, "0");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(2, "2");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

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
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_TRUE(p == p);
		EXPECT_TRUE(cp == cp);
		EXPECT_TRUE(p == cp);
		EXPECT_TRUE(cp == p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("1", 0);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("2", 2);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

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
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(2, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

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
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(1, "0");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(2, "2");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

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
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_FALSE(p != p);
		EXPECT_FALSE(cp != cp);
		EXPECT_FALSE(p != cp);
		EXPECT_FALSE(cp != p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("1", 0);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("2", 2);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

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

TEST(pair, operator_less)
{
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p < p2);
		EXPECT_TRUE(p < p3);
		EXPECT_TRUE(p < p4);
		EXPECT_TRUE(p2 < p3);
		EXPECT_TRUE(p2 < p4);
		EXPECT_TRUE(p3 < p4);

		EXPECT_TRUE(cp < cp2);
		EXPECT_TRUE(cp < cp3);
		EXPECT_TRUE(cp < cp4);
		EXPECT_TRUE(cp2 < cp3);
		EXPECT_TRUE(cp2 < cp4);
		EXPECT_TRUE(cp3 < cp4);

		EXPECT_TRUE(cp < p2);
		EXPECT_TRUE(cp < p3);
		EXPECT_TRUE(cp < p4);
		EXPECT_TRUE(cp2 < p3);
		EXPECT_TRUE(cp2 < p4);
		EXPECT_TRUE(cp3 < p4);

		EXPECT_TRUE(p < cp2);
		EXPECT_TRUE(p < cp3);
		EXPECT_TRUE(p < cp4);
		EXPECT_TRUE(p2 < cp3);
		EXPECT_TRUE(p2 < cp4);
		EXPECT_TRUE(p3 < cp4);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_TRUE(p < p2);
		EXPECT_TRUE(p < p3);
		EXPECT_TRUE(p < p4);
		EXPECT_TRUE(p2 < p3);
		EXPECT_TRUE(p2 < p4);
		EXPECT_TRUE(p3 < p4);

		EXPECT_TRUE(cp < cp2);
		EXPECT_TRUE(cp < cp3);
		EXPECT_TRUE(cp < cp4);
		EXPECT_TRUE(cp2 < cp3);
		EXPECT_TRUE(cp2 < cp4);
		EXPECT_TRUE(cp3 < cp4);

		EXPECT_TRUE(cp < p2);
		EXPECT_TRUE(cp < p3);
		EXPECT_TRUE(cp < p4);
		EXPECT_TRUE(cp2 < p3);
		EXPECT_TRUE(cp2 < p4);
		EXPECT_TRUE(cp3 < p4);

		EXPECT_TRUE(p < cp2);
		EXPECT_TRUE(p < cp3);
		EXPECT_TRUE(p < cp4);
		EXPECT_TRUE(p2 < cp3);
		EXPECT_TRUE(p2 < cp4);
		EXPECT_TRUE(p3 < cp4);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_FALSE(p < p);
		EXPECT_FALSE(cp < cp);
		EXPECT_FALSE(p < cp);
		EXPECT_FALSE(cp < p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p < p2);
		EXPECT_TRUE(p < p3);
		EXPECT_TRUE(p < p4);
		EXPECT_TRUE(p2 < p3);
		EXPECT_TRUE(p2 < p4);
		EXPECT_TRUE(p3 < p4);

		EXPECT_TRUE(cp < cp2);
		EXPECT_TRUE(cp < cp3);
		EXPECT_TRUE(cp < cp4);
		EXPECT_TRUE(cp2 < cp3);
		EXPECT_TRUE(cp2 < cp4);
		EXPECT_TRUE(cp3 < cp4);

		EXPECT_TRUE(cp < p2);
		EXPECT_TRUE(cp < p3);
		EXPECT_TRUE(cp < p4);
		EXPECT_TRUE(cp2 < p3);
		EXPECT_TRUE(cp2 < p4);
		EXPECT_TRUE(cp3 < p4);

		EXPECT_TRUE(p < cp2);
		EXPECT_TRUE(p < cp3);
		EXPECT_TRUE(p < cp4);
		EXPECT_TRUE(p2 < cp3);
		EXPECT_TRUE(p2 < cp4);
		EXPECT_TRUE(p3 < cp4);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p2 < p);
		EXPECT_FALSE(p3 < p);
		EXPECT_FALSE(p4 < p);
		EXPECT_FALSE(p3 < p2);
		EXPECT_FALSE(p4 < p2);
		EXPECT_FALSE(p4 < p3);

		EXPECT_FALSE(cp2 < cp);
		EXPECT_FALSE(cp3 < cp);
		EXPECT_FALSE(cp4 < cp);
		EXPECT_FALSE(cp3 < cp2);
		EXPECT_FALSE(cp4 < cp2);
		EXPECT_FALSE(cp4 < cp3);

		EXPECT_FALSE(p2 < cp);
		EXPECT_FALSE(p3 < cp);
		EXPECT_FALSE(p4 < cp);
		EXPECT_FALSE(p3 < cp2);
		EXPECT_FALSE(p4 < cp2);
		EXPECT_FALSE(p4 < cp3);

		EXPECT_FALSE(cp2 < p);
		EXPECT_FALSE(cp3 < p);
		EXPECT_FALSE(cp4 < p);
		EXPECT_FALSE(cp3 < p2);
		EXPECT_FALSE(cp4 < p2);
		EXPECT_FALSE(cp4 < p3);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_FALSE(p2 < p);
		EXPECT_FALSE(p3 < p);
		EXPECT_FALSE(p4 < p);
		EXPECT_FALSE(p3 < p2);
		EXPECT_FALSE(p4 < p2);
		EXPECT_FALSE(p4 < p3);

		EXPECT_FALSE(cp2 < cp);
		EXPECT_FALSE(cp3 < cp);
		EXPECT_FALSE(cp4 < cp);
		EXPECT_FALSE(cp3 < cp2);
		EXPECT_FALSE(cp4 < cp2);
		EXPECT_FALSE(cp4 < cp3);

		EXPECT_FALSE(p2 < cp);
		EXPECT_FALSE(p3 < cp);
		EXPECT_FALSE(p4 < cp);
		EXPECT_FALSE(p3 < cp2);
		EXPECT_FALSE(p4 < cp2);
		EXPECT_FALSE(p4 < cp3);

		EXPECT_FALSE(cp2 < p);
		EXPECT_FALSE(cp3 < p);
		EXPECT_FALSE(cp4 < p);
		EXPECT_FALSE(cp3 < p2);
		EXPECT_FALSE(cp4 < p2);
		EXPECT_FALSE(cp4 < p3);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p2 < p);
		EXPECT_FALSE(p3 < p);
		EXPECT_FALSE(p4 < p);
		EXPECT_FALSE(p3 < p2);
		EXPECT_FALSE(p4 < p2);
		EXPECT_FALSE(p4 < p3);

		EXPECT_FALSE(cp2 < cp);
		EXPECT_FALSE(cp3 < cp);
		EXPECT_FALSE(cp4 < cp);
		EXPECT_FALSE(cp3 < cp2);
		EXPECT_FALSE(cp4 < cp2);
		EXPECT_FALSE(cp4 < cp3);

		EXPECT_FALSE(p2 < cp);
		EXPECT_FALSE(p3 < cp);
		EXPECT_FALSE(p4 < cp);
		EXPECT_FALSE(p3 < cp2);
		EXPECT_FALSE(p4 < cp2);
		EXPECT_FALSE(p4 < cp3);

		EXPECT_FALSE(cp2 < p);
		EXPECT_FALSE(cp3 < p);
		EXPECT_FALSE(cp4 < p);
		EXPECT_FALSE(cp3 < p2);
		EXPECT_FALSE(cp4 < p2);
		EXPECT_FALSE(cp4 < p3);
	}
}

TEST(pair, operator_less_eq)
{
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p <= p2);
		EXPECT_TRUE(p <= p3);
		EXPECT_TRUE(p <= p4);
		EXPECT_TRUE(p2 <= p3);
		EXPECT_TRUE(p2 <= p4);
		EXPECT_TRUE(p3 <= p4);

		EXPECT_TRUE(cp <= cp2);
		EXPECT_TRUE(cp <= cp3);
		EXPECT_TRUE(cp <= cp4);
		EXPECT_TRUE(cp2 <= cp3);
		EXPECT_TRUE(cp2 <= cp4);
		EXPECT_TRUE(cp3 <= cp4);

		EXPECT_TRUE(cp <= p2);
		EXPECT_TRUE(cp <= p3);
		EXPECT_TRUE(cp <= p4);
		EXPECT_TRUE(cp2 <= p3);
		EXPECT_TRUE(cp2 <= p4);
		EXPECT_TRUE(cp3 <= p4);

		EXPECT_TRUE(p <= cp2);
		EXPECT_TRUE(p <= cp3);
		EXPECT_TRUE(p <= cp4);
		EXPECT_TRUE(p2 <= cp3);
		EXPECT_TRUE(p2 <= cp4);
		EXPECT_TRUE(p3 <= cp4);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_TRUE(p <= p2);
		EXPECT_TRUE(p <= p3);
		EXPECT_TRUE(p <= p4);
		EXPECT_TRUE(p2 <= p3);
		EXPECT_TRUE(p2 <= p4);
		EXPECT_TRUE(p3 <= p4);

		EXPECT_TRUE(cp <= cp2);
		EXPECT_TRUE(cp <= cp3);
		EXPECT_TRUE(cp <= cp4);
		EXPECT_TRUE(cp2 <= cp3);
		EXPECT_TRUE(cp2 <= cp4);
		EXPECT_TRUE(cp3 <= cp4);

		EXPECT_TRUE(cp <= p2);
		EXPECT_TRUE(cp <= p3);
		EXPECT_TRUE(cp <= p4);
		EXPECT_TRUE(cp2 <= p3);
		EXPECT_TRUE(cp2 <= p4);
		EXPECT_TRUE(cp3 <= p4);

		EXPECT_TRUE(p <= cp2);
		EXPECT_TRUE(p <= cp3);
		EXPECT_TRUE(p <= cp4);
		EXPECT_TRUE(p2 <= cp3);
		EXPECT_TRUE(p2 <= cp4);
		EXPECT_TRUE(p3 <= cp4);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_TRUE(p <= p);
		EXPECT_TRUE(cp <= cp);
		EXPECT_TRUE(p <= cp);
		EXPECT_TRUE(cp <= p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p <= p2);
		EXPECT_TRUE(p <= p3);
		EXPECT_TRUE(p <= p4);
		EXPECT_TRUE(p2 <= p3);
		EXPECT_TRUE(p2 <= p4);
		EXPECT_TRUE(p3 <= p4);

		EXPECT_TRUE(cp <= cp2);
		EXPECT_TRUE(cp <= cp3);
		EXPECT_TRUE(cp <= cp4);
		EXPECT_TRUE(cp2 <= cp3);
		EXPECT_TRUE(cp2 <= cp4);
		EXPECT_TRUE(cp3 <= cp4);

		EXPECT_TRUE(cp <= p2);
		EXPECT_TRUE(cp <= p3);
		EXPECT_TRUE(cp <= p4);
		EXPECT_TRUE(cp2 <= p3);
		EXPECT_TRUE(cp2 <= p4);
		EXPECT_TRUE(cp3 <= p4);

		EXPECT_TRUE(p <= cp2);
		EXPECT_TRUE(p <= cp3);
		EXPECT_TRUE(p <= cp4);
		EXPECT_TRUE(p2 <= cp3);
		EXPECT_TRUE(p2 <= cp4);
		EXPECT_TRUE(p3 <= cp4);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p2 <= p);
		EXPECT_FALSE(p3 <= p);
		EXPECT_FALSE(p4 <= p);
		EXPECT_FALSE(p3 <= p2);
		EXPECT_FALSE(p4 <= p2);
		EXPECT_FALSE(p4 <= p3);

		EXPECT_FALSE(cp2 <= cp);
		EXPECT_FALSE(cp3 <= cp);
		EXPECT_FALSE(cp4 <= cp);
		EXPECT_FALSE(cp3 <= cp2);
		EXPECT_FALSE(cp4 <= cp2);
		EXPECT_FALSE(cp4 <= cp3);

		EXPECT_FALSE(p2 <= cp);
		EXPECT_FALSE(p3 <= cp);
		EXPECT_FALSE(p4 <= cp);
		EXPECT_FALSE(p3 <= cp2);
		EXPECT_FALSE(p4 <= cp2);
		EXPECT_FALSE(p4 <= cp3);

		EXPECT_FALSE(cp2 <= p);
		EXPECT_FALSE(cp3 <= p);
		EXPECT_FALSE(cp4 <= p);
		EXPECT_FALSE(cp3 <= p2);
		EXPECT_FALSE(cp4 <= p2);
		EXPECT_FALSE(cp4 <= p3);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_FALSE(p2 <= p);
		EXPECT_FALSE(p3 <= p);
		EXPECT_FALSE(p4 <= p);
		EXPECT_FALSE(p3 <= p2);
		EXPECT_FALSE(p4 <= p2);
		EXPECT_FALSE(p4 <= p3);

		EXPECT_FALSE(cp2 <= cp);
		EXPECT_FALSE(cp3 <= cp);
		EXPECT_FALSE(cp4 <= cp);
		EXPECT_FALSE(cp3 <= cp2);
		EXPECT_FALSE(cp4 <= cp2);
		EXPECT_FALSE(cp4 <= cp3);

		EXPECT_FALSE(p2 <= cp);
		EXPECT_FALSE(p3 <= cp);
		EXPECT_FALSE(p4 <= cp);
		EXPECT_FALSE(p3 <= cp2);
		EXPECT_FALSE(p4 <= cp2);
		EXPECT_FALSE(p4 <= cp3);

		EXPECT_FALSE(cp2 <= p);
		EXPECT_FALSE(cp3 <= p);
		EXPECT_FALSE(cp4 <= p);
		EXPECT_FALSE(cp3 <= p2);
		EXPECT_FALSE(cp4 <= p2);
		EXPECT_FALSE(cp4 <= p3);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p2 <= p);
		EXPECT_FALSE(p3 <= p);
		EXPECT_FALSE(p4 <= p);
		EXPECT_FALSE(p3 <= p2);
		EXPECT_FALSE(p4 <= p2);
		EXPECT_FALSE(p4 <= p3);

		EXPECT_FALSE(cp2 <= cp);
		EXPECT_FALSE(cp3 <= cp);
		EXPECT_FALSE(cp4 <= cp);
		EXPECT_FALSE(cp3 <= cp2);
		EXPECT_FALSE(cp4 <= cp2);
		EXPECT_FALSE(cp4 <= cp3);

		EXPECT_FALSE(p2 <= cp);
		EXPECT_FALSE(p3 <= cp);
		EXPECT_FALSE(p4 <= cp);
		EXPECT_FALSE(p3 <= cp2);
		EXPECT_FALSE(p4 <= cp2);
		EXPECT_FALSE(p4 <= cp3);

		EXPECT_FALSE(cp2 <= p);
		EXPECT_FALSE(cp3 <= p);
		EXPECT_FALSE(cp4 <= p);
		EXPECT_FALSE(cp3 <= p2);
		EXPECT_FALSE(cp4 <= p2);
		EXPECT_FALSE(cp4 <= p3);
	}
}

TEST(pair, operator_greater)
{
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p > p2);
		EXPECT_FALSE(p > p3);
		EXPECT_FALSE(p > p4);
		EXPECT_FALSE(p2 > p3);
		EXPECT_FALSE(p2 > p4);
		EXPECT_FALSE(p3 > p4);

		EXPECT_FALSE(cp > cp2);
		EXPECT_FALSE(cp > cp3);
		EXPECT_FALSE(cp > cp4);
		EXPECT_FALSE(cp2 > cp3);
		EXPECT_FALSE(cp2 > cp4);
		EXPECT_FALSE(cp3 > cp4);

		EXPECT_FALSE(cp > p2);
		EXPECT_FALSE(cp > p3);
		EXPECT_FALSE(cp > p4);
		EXPECT_FALSE(cp2 > p3);
		EXPECT_FALSE(cp2 > p4);
		EXPECT_FALSE(cp3 > p4);

		EXPECT_FALSE(p > cp2);
		EXPECT_FALSE(p > cp3);
		EXPECT_FALSE(p > cp4);
		EXPECT_FALSE(p2 > cp3);
		EXPECT_FALSE(p2 > cp4);
		EXPECT_FALSE(p3 > cp4);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_FALSE(p > p2);
		EXPECT_FALSE(p > p3);
		EXPECT_FALSE(p > p4);
		EXPECT_FALSE(p2 > p3);
		EXPECT_FALSE(p2 > p4);
		EXPECT_FALSE(p3 > p4);

		EXPECT_FALSE(cp > cp2);
		EXPECT_FALSE(cp > cp3);
		EXPECT_FALSE(cp > cp4);
		EXPECT_FALSE(cp2 > cp3);
		EXPECT_FALSE(cp2 > cp4);
		EXPECT_FALSE(cp3 > cp4);

		EXPECT_FALSE(cp > p2);
		EXPECT_FALSE(cp > p3);
		EXPECT_FALSE(cp > p4);
		EXPECT_FALSE(cp2 > p3);
		EXPECT_FALSE(cp2 > p4);
		EXPECT_FALSE(cp3 > p4);

		EXPECT_FALSE(p > cp2);
		EXPECT_FALSE(p > cp3);
		EXPECT_FALSE(p > cp4);
		EXPECT_FALSE(p2 > cp3);
		EXPECT_FALSE(p2 > cp4);
		EXPECT_FALSE(p3 > cp4);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_FALSE(p > p);
		EXPECT_FALSE(cp > cp);
		EXPECT_FALSE(p > cp);
		EXPECT_FALSE(cp > p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p > p2);
		EXPECT_FALSE(p > p3);
		EXPECT_FALSE(p > p4);
		EXPECT_FALSE(p2 > p3);
		EXPECT_FALSE(p2 > p4);
		EXPECT_FALSE(p3 > p4);

		EXPECT_FALSE(cp > cp2);
		EXPECT_FALSE(cp > cp3);
		EXPECT_FALSE(cp > cp4);
		EXPECT_FALSE(cp2 > cp3);
		EXPECT_FALSE(cp2 > cp4);
		EXPECT_FALSE(cp3 > cp4);

		EXPECT_FALSE(cp > p2);
		EXPECT_FALSE(cp > p3);
		EXPECT_FALSE(cp > p4);
		EXPECT_FALSE(cp2 > p3);
		EXPECT_FALSE(cp2 > p4);
		EXPECT_FALSE(cp3 > p4);

		EXPECT_FALSE(p > cp2);
		EXPECT_FALSE(p > cp3);
		EXPECT_FALSE(p > cp4);
		EXPECT_FALSE(p2 > cp3);
		EXPECT_FALSE(p2 > cp4);
		EXPECT_FALSE(p3 > cp4);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p2 > p);
		EXPECT_TRUE(p3 > p);
		EXPECT_TRUE(p4 > p);
		EXPECT_TRUE(p3 > p2);
		EXPECT_TRUE(p4 > p2);
		EXPECT_TRUE(p4 > p3);

		EXPECT_TRUE(cp2 > cp);
		EXPECT_TRUE(cp3 > cp);
		EXPECT_TRUE(cp4 > cp);
		EXPECT_TRUE(cp3 > cp2);
		EXPECT_TRUE(cp4 > cp2);
		EXPECT_TRUE(cp4 > cp3);

		EXPECT_TRUE(p2 > cp);
		EXPECT_TRUE(p3 > cp);
		EXPECT_TRUE(p4 > cp);
		EXPECT_TRUE(p3 > cp2);
		EXPECT_TRUE(p4 > cp2);
		EXPECT_TRUE(p4 > cp3);

		EXPECT_TRUE(cp2 > p);
		EXPECT_TRUE(cp3 > p);
		EXPECT_TRUE(cp4 > p);
		EXPECT_TRUE(cp3 > p2);
		EXPECT_TRUE(cp4 > p2);
		EXPECT_TRUE(cp4 > p3);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_TRUE(p2 > p);
		EXPECT_TRUE(p3 > p);
		EXPECT_TRUE(p4 > p);
		EXPECT_TRUE(p3 > p2);
		EXPECT_TRUE(p4 > p2);
		EXPECT_TRUE(p4 > p3);

		EXPECT_TRUE(cp2 > cp);
		EXPECT_TRUE(cp3 > cp);
		EXPECT_TRUE(cp4 > cp);
		EXPECT_TRUE(cp3 > cp2);
		EXPECT_TRUE(cp4 > cp2);
		EXPECT_TRUE(cp4 > cp3);

		EXPECT_TRUE(p2 > cp);
		EXPECT_TRUE(p3 > cp);
		EXPECT_TRUE(p4 > cp);
		EXPECT_TRUE(p3 > cp2);
		EXPECT_TRUE(p4 > cp2);
		EXPECT_TRUE(p4 > cp3);

		EXPECT_TRUE(cp2 > p);
		EXPECT_TRUE(cp3 > p);
		EXPECT_TRUE(cp4 > p);
		EXPECT_TRUE(cp3 > p2);
		EXPECT_TRUE(cp4 > p2);
		EXPECT_TRUE(cp4 > p3);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p2 > p);
		EXPECT_TRUE(p3 > p);
		EXPECT_TRUE(p4 > p);
		EXPECT_TRUE(p3 > p2);
		EXPECT_TRUE(p4 > p2);
		EXPECT_TRUE(p4 > p3);

		EXPECT_TRUE(cp2 > cp);
		EXPECT_TRUE(cp3 > cp);
		EXPECT_TRUE(cp4 > cp);
		EXPECT_TRUE(cp3 > cp2);
		EXPECT_TRUE(cp4 > cp2);
		EXPECT_TRUE(cp4 > cp3);

		EXPECT_TRUE(p2 > cp);
		EXPECT_TRUE(p3 > cp);
		EXPECT_TRUE(p4 > cp);
		EXPECT_TRUE(p3 > cp2);
		EXPECT_TRUE(p4 > cp2);
		EXPECT_TRUE(p4 > cp3);

		EXPECT_TRUE(cp2 > p);
		EXPECT_TRUE(cp3 > p);
		EXPECT_TRUE(cp4 > p);
		EXPECT_TRUE(cp3 > p2);
		EXPECT_TRUE(cp4 > p2);
		EXPECT_TRUE(cp4 > p3);
	}
}

TEST(pair, operator_greater_eq)
{
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		const ft::pair<ftc::Elem, ftc::Elem> cp;

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p  = ft::pair<ftc::Elem, ftc::Elem>(1, 2);
		const ft::pair<ftc::Elem, ftc::Elem> cp = ft::pair<ftc::Elem, ftc::Elem>(1, 2);

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p >= p2);
		EXPECT_FALSE(p >= p3);
		EXPECT_FALSE(p >= p4);
		EXPECT_FALSE(p2 >= p3);
		EXPECT_FALSE(p2 >= p4);
		EXPECT_FALSE(p3 >= p4);

		EXPECT_FALSE(cp >= cp2);
		EXPECT_FALSE(cp >= cp3);
		EXPECT_FALSE(cp >= cp4);
		EXPECT_FALSE(cp2 >= cp3);
		EXPECT_FALSE(cp2 >= cp4);
		EXPECT_FALSE(cp3 >= cp4);

		EXPECT_FALSE(cp >= p2);
		EXPECT_FALSE(cp >= p3);
		EXPECT_FALSE(cp >= p4);
		EXPECT_FALSE(cp2 >= p3);
		EXPECT_FALSE(cp2 >= p4);
		EXPECT_FALSE(cp3 >= p4);

		EXPECT_FALSE(p >= cp2);
		EXPECT_FALSE(p >= cp3);
		EXPECT_FALSE(p >= cp4);
		EXPECT_FALSE(p2 >= cp3);
		EXPECT_FALSE(p2 >= cp4);
		EXPECT_FALSE(p3 >= cp4);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		const ft::pair<ftc::Elem, std::string> cp;

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p  = ft::pair<ftc::Elem, std::string>(1, "2");
		const ft::pair<ftc::Elem, std::string> cp = ft::pair<ftc::Elem, std::string>(1, "2");

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_FALSE(p >= p2);
		EXPECT_FALSE(p >= p3);
		EXPECT_FALSE(p >= p4);
		EXPECT_FALSE(p2 >= p3);
		EXPECT_FALSE(p2 >= p4);
		EXPECT_FALSE(p3 >= p4);

		EXPECT_FALSE(cp >= cp2);
		EXPECT_FALSE(cp >= cp3);
		EXPECT_FALSE(cp >= cp4);
		EXPECT_FALSE(cp2 >= cp3);
		EXPECT_FALSE(cp2 >= cp4);
		EXPECT_FALSE(cp3 >= cp4);

		EXPECT_FALSE(cp >= p2);
		EXPECT_FALSE(cp >= p3);
		EXPECT_FALSE(cp >= p4);
		EXPECT_FALSE(cp2 >= p3);
		EXPECT_FALSE(cp2 >= p4);
		EXPECT_FALSE(cp3 >= p4);

		EXPECT_FALSE(p >= cp2);
		EXPECT_FALSE(p >= cp3);
		EXPECT_FALSE(p >= cp4);
		EXPECT_FALSE(p2 >= cp3);
		EXPECT_FALSE(p2 >= cp4);
		EXPECT_FALSE(p3 >= cp4);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		const ft::pair<std::string, ftc::Elem> cp;

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p  = ft::pair<std::string, ftc::Elem>("1", 2);
		const ft::pair<std::string, ftc::Elem> cp = ft::pair<std::string, ftc::Elem>("1", 2);

		EXPECT_TRUE(p >= p);
		EXPECT_TRUE(cp >= cp);
		EXPECT_TRUE(p >= cp);
		EXPECT_TRUE(cp >= p);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_FALSE(p >= p2);
		EXPECT_FALSE(p >= p3);
		EXPECT_FALSE(p >= p4);
		EXPECT_FALSE(p2 >= p3);
		EXPECT_FALSE(p2 >= p4);
		EXPECT_FALSE(p3 >= p4);

		EXPECT_FALSE(cp >= cp2);
		EXPECT_FALSE(cp >= cp3);
		EXPECT_FALSE(cp >= cp4);
		EXPECT_FALSE(cp2 >= cp3);
		EXPECT_FALSE(cp2 >= cp4);
		EXPECT_FALSE(cp3 >= cp4);

		EXPECT_FALSE(cp >= p2);
		EXPECT_FALSE(cp >= p3);
		EXPECT_FALSE(cp >= p4);
		EXPECT_FALSE(cp2 >= p3);
		EXPECT_FALSE(cp2 >= p4);
		EXPECT_FALSE(cp3 >= p4);

		EXPECT_FALSE(p >= cp2);
		EXPECT_FALSE(p >= cp3);
		EXPECT_FALSE(p >= cp4);
		EXPECT_FALSE(p2 >= cp3);
		EXPECT_FALSE(p2 >= cp4);
		EXPECT_FALSE(p3 >= cp4);
	}
	{
		ft::pair<ftc::Elem, ftc::Elem>       p;
		ft::pair<ftc::Elem, ftc::Elem>       p2 = ft::pair<ftc::Elem, ftc::Elem>(0, 1);
		ft::pair<ftc::Elem, ftc::Elem>       p3 = ft::pair<ftc::Elem, ftc::Elem>(0, 2);
		ft::pair<ftc::Elem, ftc::Elem>       p4 = ft::pair<ftc::Elem, ftc::Elem>(1, 0);
		const ft::pair<ftc::Elem, ftc::Elem> cp;
		const ft::pair<ftc::Elem, ftc::Elem> cp2 = p2;
		const ft::pair<ftc::Elem, ftc::Elem> cp3 = p3;
		const ft::pair<ftc::Elem, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p2 >= p);
		EXPECT_TRUE(p3 >= p);
		EXPECT_TRUE(p4 >= p);
		EXPECT_TRUE(p3 >= p2);
		EXPECT_TRUE(p4 >= p2);
		EXPECT_TRUE(p4 >= p3);

		EXPECT_TRUE(cp2 >= cp);
		EXPECT_TRUE(cp3 >= cp);
		EXPECT_TRUE(cp4 >= cp);
		EXPECT_TRUE(cp3 >= cp2);
		EXPECT_TRUE(cp4 >= cp2);
		EXPECT_TRUE(cp4 >= cp3);

		EXPECT_TRUE(p2 >= cp);
		EXPECT_TRUE(p3 >= cp);
		EXPECT_TRUE(p4 >= cp);
		EXPECT_TRUE(p3 >= cp2);
		EXPECT_TRUE(p4 >= cp2);
		EXPECT_TRUE(p4 >= cp3);

		EXPECT_TRUE(cp2 >= p);
		EXPECT_TRUE(cp3 >= p);
		EXPECT_TRUE(cp4 >= p);
		EXPECT_TRUE(cp3 >= p2);
		EXPECT_TRUE(cp4 >= p2);
		EXPECT_TRUE(cp4 >= p3);
	}
	{
		ft::pair<ftc::Elem, std::string>       p;
		ft::pair<ftc::Elem, std::string>       p2 = ft::pair<ftc::Elem, std::string>(0, "1");
		ft::pair<ftc::Elem, std::string>       p3 = ft::pair<ftc::Elem, std::string>(0, "2");
		ft::pair<ftc::Elem, std::string>       p4 = ft::pair<ftc::Elem, std::string>(1, "0");
		const ft::pair<ftc::Elem, std::string> cp;
		const ft::pair<ftc::Elem, std::string> cp2 = p2;
		const ft::pair<ftc::Elem, std::string> cp3 = p3;
		const ft::pair<ftc::Elem, std::string> cp4 = p4;

		EXPECT_TRUE(p2 >= p);
		EXPECT_TRUE(p3 >= p);
		EXPECT_TRUE(p4 >= p);
		EXPECT_TRUE(p3 >= p2);
		EXPECT_TRUE(p4 >= p2);
		EXPECT_TRUE(p4 >= p3);

		EXPECT_TRUE(cp2 >= cp);
		EXPECT_TRUE(cp3 >= cp);
		EXPECT_TRUE(cp4 >= cp);
		EXPECT_TRUE(cp3 >= cp2);
		EXPECT_TRUE(cp4 >= cp2);
		EXPECT_TRUE(cp4 >= cp3);

		EXPECT_TRUE(p2 >= cp);
		EXPECT_TRUE(p3 >= cp);
		EXPECT_TRUE(p4 >= cp);
		EXPECT_TRUE(p3 >= cp2);
		EXPECT_TRUE(p4 >= cp2);
		EXPECT_TRUE(p4 >= cp3);

		EXPECT_TRUE(cp2 >= p);
		EXPECT_TRUE(cp3 >= p);
		EXPECT_TRUE(cp4 >= p);
		EXPECT_TRUE(cp3 >= p2);
		EXPECT_TRUE(cp4 >= p2);
		EXPECT_TRUE(cp4 >= p3);
	}
	{
		ft::pair<std::string, ftc::Elem>       p;
		ft::pair<std::string, ftc::Elem>       p2 = ft::pair<std::string, ftc::Elem>("0", 1);
		ft::pair<std::string, ftc::Elem>       p3 = ft::pair<std::string, ftc::Elem>("0", 2);
		ft::pair<std::string, ftc::Elem>       p4 = ft::pair<std::string, ftc::Elem>("1", 0);
		const ft::pair<std::string, ftc::Elem> cp;
		const ft::pair<std::string, ftc::Elem> cp2 = p2;
		const ft::pair<std::string, ftc::Elem> cp3 = p3;
		const ft::pair<std::string, ftc::Elem> cp4 = p4;

		EXPECT_TRUE(p2 >= p);
		EXPECT_TRUE(p3 >= p);
		EXPECT_TRUE(p4 >= p);
		EXPECT_TRUE(p3 >= p2);
		EXPECT_TRUE(p4 >= p2);
		EXPECT_TRUE(p4 >= p3);

		EXPECT_TRUE(cp2 >= cp);
		EXPECT_TRUE(cp3 >= cp);
		EXPECT_TRUE(cp4 >= cp);
		EXPECT_TRUE(cp3 >= cp2);
		EXPECT_TRUE(cp4 >= cp2);
		EXPECT_TRUE(cp4 >= cp3);

		EXPECT_TRUE(p2 >= cp);
		EXPECT_TRUE(p3 >= cp);
		EXPECT_TRUE(p4 >= cp);
		EXPECT_TRUE(p3 >= cp2);
		EXPECT_TRUE(p4 >= cp2);
		EXPECT_TRUE(p4 >= cp3);

		EXPECT_TRUE(cp2 >= p);
		EXPECT_TRUE(cp3 >= p);
		EXPECT_TRUE(cp4 >= p);
		EXPECT_TRUE(cp3 >= p2);
		EXPECT_TRUE(cp4 >= p2);
		EXPECT_TRUE(cp4 >= p3);
	}
}

TEST(make_pair, LWG181)
{
	ft::make_pair("abc", 3);
}
