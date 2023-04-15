#include "gtest.h"

#include <typeinfo>

#include "data.hpp"

namespace ftc = ft_containers;

#ifdef FT_TEST
  #include "stack.hpp"
typedef ft::stack<ftc::Data> Stack;
#else
  #include <stack>
  #include <vector>
namespace ft = std;
typedef ft::stack<ftc::Data, ft::vector<ftc::Data> > Stack;
#endif

typedef ft::vector<ftc::Data> Vector;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(stack, types)
{
	EXPECT_EQ(typeid(Stack::container_type), typeid(ft::vector<ftc::Data>));
	EXPECT_EQ(typeid(Stack::value_type), typeid(Stack::container_type::value_type));
	EXPECT_EQ(typeid(Stack::size_type), typeid(Stack::container_type::size_type));
	EXPECT_EQ(typeid(Stack::reference), typeid(Stack::container_type::reference));
	EXPECT_EQ(typeid(Stack::const_reference), typeid(Stack::container_type::const_reference));
}

TEST(stack, constructor)
{
	ftc::Data a1[] = {1, 2, 3};
	Vector    v(a1, a1 + ARRAY_SIZE(a1));
	{
		Stack s(v);

		EXPECT_EQ(s.size(), v.size());
		Vector::reverse_iterator it = v.rbegin();
		while (!s.empty()) {
			EXPECT_EQ(s.top(), *it);
			s.pop();
			++it;
		}
	}
	{
		Stack s1(v);
		Stack s2(s1);

		EXPECT_EQ(s1, s2);
		EXPECT_EQ(s2.size(), s1.size());
		while (!s1.empty() || !s2.empty()) {
			EXPECT_EQ(s1.top(), s2.top());
			s1.pop();
			s2.pop();
		}
	}
	{
		const Vector &v2 = v;
		Stack         s(v2);

		EXPECT_EQ(s.size(), v2.size());
		Vector::const_reverse_iterator it = v2.rbegin();
		while (!s.empty()) {
			EXPECT_EQ(s.top(), *it);
			s.pop();
			++it;
		}
	}
	{
		const Stack s1(v);
		Stack       s2(s1);

		EXPECT_EQ(s2.size(), s1.size());
		EXPECT_EQ(s1.top(), s2.top());
		EXPECT_EQ(s1, s2);
	}
}

TEST(stack, push_pop_size_empty_top_types)
{
	{
		Stack s;

		EXPECT_EQ(typeid(s.push(1)), typeid(void));
		EXPECT_EQ(typeid(s.pop()), typeid(void));
		EXPECT_EQ(typeid(s.size()), typeid(Stack::size_type));
		EXPECT_EQ(typeid(s.empty()), typeid(bool));
		EXPECT_EQ(typeid(s.top()), typeid(ftc::Data));
	}
	{
		const Stack s;

		EXPECT_EQ(typeid(s.size()), typeid(Stack::size_type));
		EXPECT_EQ(typeid(s.empty()), typeid(bool));
		EXPECT_EQ(typeid(s.top()), typeid(ftc::Data));
	}
}

TEST(stack, push_pop_size_empty_top)
{
	Stack s;

	EXPECT_TRUE(s.empty());
	EXPECT_EQ(s.size(), 0U);
	s.push(0);
	EXPECT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 1U);
	EXPECT_EQ(s.top(), 0);
	s.push(1);
	EXPECT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 2U);
	EXPECT_EQ(s.top(), 1);
	s.push(1);
	EXPECT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 3U);
	EXPECT_EQ(s.top(), 1);
	s.pop();
	EXPECT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 2U);
	EXPECT_EQ(s.top(), 1);
	s.pop();
	EXPECT_FALSE(s.empty());
	EXPECT_EQ(s.size(), 1U);
	EXPECT_EQ(s.top(), 0);
	s.pop();
	EXPECT_TRUE(s.empty());
	EXPECT_EQ(s.size(), 0U);
}

TEST(stack, push_pop_size_empty_top2)
{
	ftc::Data             a1[] = {1, 2, 3};
	ft::vector<ftc::Data> v(a1, a1 + ARRAY_SIZE(a1));
	{
		const Stack s;

		EXPECT_TRUE(s.empty());
		EXPECT_EQ(s.size(), 0U);
	}
	{
		const Stack s(v);

		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), v.size());
		EXPECT_EQ(s.top(), 3);
	}
	{
		Stack s(v);

		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 3U);
		EXPECT_EQ(s.top(), 3);
		s.pop();
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 2U);
		EXPECT_EQ(s.top(), 2);
		s.pop();
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 1U);
		EXPECT_EQ(s.top(), 1);
		s.pop();
		EXPECT_TRUE(s.empty());
		EXPECT_EQ(s.size(), 0U);
	}
	{
		Stack s;

		EXPECT_TRUE(s.empty());
		EXPECT_EQ(s.size(), 0U);
		s.push(v[0]);
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 1U);
		EXPECT_EQ(s.top(), 1);
		s.push(v[1]);
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 2U);
		EXPECT_EQ(s.top(), 2);
		s.push(v[2]);
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 3U);
		EXPECT_EQ(s.top(), 3);
	}
}

TEST(stack, operator_assignment)
{
	ftc::Data             a1[] = {1, 2, 3};
	ft::vector<ftc::Data> v(a1, a1 + ARRAY_SIZE(a1));
	{
		Stack s1(v);
		Stack s2;

		EXPECT_NE(s1, s2);
		s2 = s1;
		EXPECT_EQ(s1, s2);
		while (!s1.empty() || !s2.empty()) {
			EXPECT_EQ(s1.top(), s2.top());
			s1.pop();
			s2.pop();
		}
	}
	{
		const Stack s1(v);
		Stack       s2;

		EXPECT_NE(s1, s2);
		s2 = s1;
		EXPECT_EQ(s1, s2);
	}
}

TEST(stack, c)
{
	class stack_test : public Stack
	{
	  public:
		size_t f()
		{
			return c.size();
		}
	} st;
	EXPECT_EQ(st.f(), 0U);
}

TEST(stack, operator_cmp_empty)
{
	const Stack v1;
	const Stack v2;

	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);

	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
	EXPECT_TRUE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);

	EXPECT_FALSE(v1 < Stack());
	EXPECT_FALSE(v2 < Stack());
	EXPECT_TRUE(v1 <= Stack());
	EXPECT_TRUE(v2 <= Stack());

	EXPECT_FALSE(v1 > Stack());
	EXPECT_FALSE(v2 > Stack());
	EXPECT_TRUE(v1 >= Stack());
	EXPECT_TRUE(v2 >= Stack());

	EXPECT_FALSE(Stack() < v2);
	EXPECT_FALSE(Stack() < v1);
	EXPECT_TRUE(Stack() <= v2);
	EXPECT_TRUE(Stack() <= v1);

	EXPECT_FALSE(Stack() > v2);
	EXPECT_FALSE(Stack() > v1);
	EXPECT_TRUE(Stack() >= v2);
	EXPECT_TRUE(Stack() >= v1);
}

TEST(stack, operator_cmp_empty2)
{
	const Stack v1;

	EXPECT_FALSE(v1 < v1);
	EXPECT_FALSE(v1 < v1);
	EXPECT_TRUE(v1 <= v1);
	EXPECT_TRUE(v1 <= v1);

	EXPECT_FALSE(v1 > v1);
	EXPECT_FALSE(v1 > v1);
	EXPECT_TRUE(v1 >= v1);
	EXPECT_TRUE(v1 >= v1);
}

TEST(stack, operator_less)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST(stack, operator_less2)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST(stack, operator_less3)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 < v2);
	EXPECT_TRUE(v2 < v1);
}

TEST(stack, operator_less_self)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_FALSE(v1 < v1);
}

TEST(stack, operator_grater)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST(stack, operator_grater2)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 > v2);
	EXPECT_TRUE(v2 > v1);
}

TEST(stack, operator_grater3)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST(stack, operator_grater_self)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_FALSE(v1 > v1);
}

TEST(stack, operator_less_eq)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST(stack, operator_less_eq2)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_FALSE(v2 <= v1);
}

TEST(stack, operator_less_eq3)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST(stack, operator_less_eq_self)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_TRUE(v1 <= v1);
}

TEST(stack, operator_grater_eq)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST(stack, operator_grater_eq2)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST(stack, operator_grater_eq3)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_FALSE(v2 >= v1);
}

TEST(stack, operator_gather_eq_self)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_TRUE(v1 >= v1);
}

TEST(stack, operator_eq_empty)
{
	Stack v1;
	Stack v2;

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq_empty2)
{
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1;
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq_empty3)
{
	Stack v1;

	EXPECT_EQ(v1, Stack());
	EXPECT_TRUE(v1 == Stack());
	EXPECT_EQ(Stack(), v1);
	EXPECT_TRUE(Stack() == v1);
}

TEST(stack, operator_eq)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq2)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 4};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq3)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_ne_empty)
{
	Stack v1;
	Stack v2;

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne_empty2)
{
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1;
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne_empty3)
{
	Stack v1;

	EXPECT_NE(v1, Stack(Vector(1, 1)));
	EXPECT_TRUE(v1 != Stack(Vector(1, 1)));
	EXPECT_NE(Stack(Vector(1, 1)), v1);
	EXPECT_TRUE(Stack(Vector(1, 1)) != v1);
}

TEST(stack, operator_ne)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 4};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne2)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne3)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_eq_empty_const)
{
	const Stack v1;
	const Stack v2;

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq_empty2_const)
{
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1;
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq2_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 4};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq3_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_ne_empty_const)
{
	const Stack v1;
	const Stack v2;

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne_empty2_const)
{
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1;
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 4};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne2_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne3_const)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}
