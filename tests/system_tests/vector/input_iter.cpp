#include "gtest.h"

#include <sstream>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
#include "init_vector.hpp"
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

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

typedef std::istream_iterator<char> InputIter;

TEST_F(vector, range_constructor_input_iterator)
{
	char               ary[] = "1234";
	std::istringstream str(ary);
	ft::vector<char>   v = ft::vector<char>(InputIter(str), InputIter());

	EXPECT_EQ(v.size(), strlen(ary));
	for (size_t i = 0; ary[i]; i++) {
		ASSERT_EQ(v.at(i), ary[i]);
	}
}

TEST_F(vector, assign_input_iterator)
{
	char               ary[] = "1234";
	std::istringstream str(ary);
	ft::vector<char>   v;

	v.assign(InputIter(str), InputIter());
	EXPECT_EQ(v.size(), strlen(ary));
	EXPECT_EQ(v.capacity(), strlen(ary));
	for (size_t i = 0; ary[i]; i++) {
		ASSERT_EQ(v.at(i), ary[i]);
	}
}

TEST_F(vector, assign_input_iterator2)
{
	char               ary[] = "1234";
	std::istringstream str(ary);
	ft::vector<char>   v;

	v.assign(InputIter(str), InputIter());
	EXPECT_EQ(v.size(), strlen(ary));
	EXPECT_EQ(v.capacity(), strlen(ary));
	for (size_t i = 0; ary[i]; i++) {
		ASSERT_EQ(v.at(i), ary[i]);
	}
}

TEST_F(vector, insert_input_iter)
{
	char               ary[] = "1234";
	std::istringstream str(ary);
	ft::vector<char>   v;

	v.insert(v.end(), InputIter(str), InputIter());
	EXPECT_EQ(v.size(), strlen(ary));
	EXPECT_EQ(v.capacity(), strlen(ary));
	for (size_t i = 0; ary[i]; i++) {
		ASSERT_EQ(v.at(i), ary[i]);
	}
}
