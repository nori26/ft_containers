#include "gtest.h"

#include <list>
#include <typeinfo>

#include "data.hpp"

namespace ftc = ft_containers;

#ifdef FT_TEST
  #include "stack.hpp"
#else
  #include <stack>
namespace ft = std;
#endif

typedef ft::stack<ftc::Data, std::list<ftc::Data> > Stack;

typedef std::list<ftc::Data> Vector;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(stack, types_list)
{
	EXPECT_EQ(typeid(Stack::container_type), typeid(Vector));
	EXPECT_EQ(typeid(Stack::value_type), typeid(Stack::container_type::value_type));
	EXPECT_EQ(typeid(Stack::size_type), typeid(Stack::container_type::size_type));
	EXPECT_EQ(typeid(Stack::reference), typeid(Stack::container_type::reference));
	EXPECT_EQ(typeid(Stack::const_reference), typeid(Stack::container_type::const_reference));
}

TEST(stack, push_pop_size_empty_top_types_list)
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

TEST(stack, push_pop_size_empty_top_list)
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

TEST(stack, push_pop_size_empty_top2_list)
{
	ftc::Data a1[] = {1, 2, 3};
	Vector    v(a1, a1 + ARRAY_SIZE(a1));
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
		s.push(*v.begin());
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 1U);
		EXPECT_EQ(s.top(), 1);
		s.push(*++v.begin());
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 2U);
		EXPECT_EQ(s.top(), 2);
		s.push(*++++v.begin());
		EXPECT_FALSE(s.empty());
		EXPECT_EQ(s.size(), 3U);
		EXPECT_EQ(s.top(), 3);
	}
}

TEST(stack, operator_assignment_list)
{
	ftc::Data a1[] = {1, 2, 3};
	Vector    v(a1, a1 + ARRAY_SIZE(a1));
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

TEST(stack, c_list)
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

TEST(stack, operator_cmp_empty_list)
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

TEST(stack, operator_cmp_empty2_list)
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

TEST(stack, operator_less_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST(stack, operator_less2_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 < v2);
	EXPECT_FALSE(v2 < v1);
}

TEST(stack, operator_less3_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 < v2);
	EXPECT_TRUE(v2 < v1);
}

TEST(stack, operator_less_self_list)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_FALSE(v1 < v1);
}

TEST(stack, operator_grater_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST(stack, operator_grater2_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 > v2);
	EXPECT_TRUE(v2 > v1);
}

TEST(stack, operator_grater3_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 > v2);
	EXPECT_FALSE(v2 > v1);
}

TEST(stack, operator_grater_self_list)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_FALSE(v1 > v1);
}

TEST(stack, operator_less_eq_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST(stack, operator_less_eq2_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 <= v2);
	EXPECT_FALSE(v2 <= v1);
}

TEST(stack, operator_less_eq3_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 <= v2);
	EXPECT_TRUE(v2 <= v1);
}

TEST(stack, operator_less_eq_self_list)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_TRUE(v1 <= v1);
}

TEST(stack, operator_grater_eq_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST(stack, operator_grater_eq2_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2, 4};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_FALSE(v1 >= v2);
	EXPECT_TRUE(v2 >= v1);
}

TEST(stack, operator_grater_eq3_list)
{
	ftc::Data   a[] = {1, 2, 3};
	ftc::Data   b[] = {1, 2};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));
	const Stack v2(Vector(b, b + ARRAY_SIZE(b)));

	EXPECT_TRUE(v1 >= v2);
	EXPECT_FALSE(v2 >= v1);
}

TEST(stack, operator_gather_eq_self_list)
{
	ftc::Data   a[] = {1, 2, 3};
	const Stack v1(Vector(a, a + ARRAY_SIZE(a)));

	EXPECT_TRUE(v1 >= v1);
}

TEST(stack, operator_eq_empty_list)
{
	Stack v1;
	Stack v2;

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq_empty2_list)
{
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1;
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq_empty3_list)
{
	Stack v1;

	EXPECT_EQ(v1, Stack());
	EXPECT_TRUE(v1 == Stack());
	EXPECT_EQ(Stack(), v1);
	EXPECT_TRUE(Stack() == v1);
}

TEST(stack, operator_eq_list)
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

TEST(stack, operator_eq2_list)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 4};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq3_list)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_ne_empty_list)
{
	Stack v1;
	Stack v2;

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne_empty2_list)
{
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1;
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne_empty3_list)
{
	Stack v1;

	EXPECT_NE(v1, Stack(Vector(1, 1)));
	EXPECT_TRUE(v1 != Stack(Vector(1, 1)));
	EXPECT_NE(Stack(Vector(1, 1)), v1);
	EXPECT_TRUE(Stack(Vector(1, 1)) != v1);
}

TEST(stack, operator_ne_list)
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

TEST(stack, operator_ne2_list)
{
	ftc::Data a1[] = {1, 2, 3};
	ftc::Data a2[] = {1, 2, 3};
	Stack     v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	Stack     v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne3_list)
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

TEST(stack, operator_eq_empty_const_list)
{
	const Stack v1;
	const Stack v2;

	EXPECT_EQ(v1, v2);
	EXPECT_TRUE(v1 == v2);
	EXPECT_EQ(v2, v1);
	EXPECT_TRUE(v2 == v1);
}

TEST(stack, operator_eq_empty2_const_list)
{
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1;
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq_const_list)
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

TEST(stack, operator_eq2_const_list)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 4};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_eq3_const_list)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 == v2);
	EXPECT_FALSE(v2 == v1);
}

TEST(stack, operator_ne_empty_const_list)
{
	const Stack v1;
	const Stack v2;

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne_empty2_const_list)
{
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1;
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_NE(v1, v2);
	EXPECT_TRUE(v1 != v2);
	EXPECT_NE(v2, v1);
	EXPECT_TRUE(v2 != v1);
}

TEST(stack, operator_ne_const_list)
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

TEST(stack, operator_ne2_const_list)
{
	ftc::Data   a1[] = {1, 2, 3};
	ftc::Data   a2[] = {1, 2, 3};
	const Stack v1(Vector(a1, a1 + ARRAY_SIZE(a1)));
	const Stack v2(Vector(a2, a2 + ARRAY_SIZE(a2)));

	EXPECT_FALSE(v1 != v2);
	EXPECT_FALSE(v2 != v1);
}

TEST(stack, operator_ne3_const_list)
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
