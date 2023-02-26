#include "gtest.h"

#include <limits>
#include <memory>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
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

TEST_F(vector, get_allocator_ret_type)
{
	Vector                           v;
	const ftc::Allocator<ftc::Data> &a1 = v.get_allocator();
	const ftc::Allocator<ftc::Data> &a2 = v.get_allocator();

	EXPECT_NE(&a1, &a2);
	EXPECT_EQ(typeid(ftc::Allocator<ftc::Data>), typeid(v.get_allocator()));
}

TEST_F(vector, get_allocator)
{
	ftc::Allocator<ftc::Data> a;
	const Vector              v(a);

	EXPECT_EQ(v.get_allocator().get_id(), a.get_id());
}

TEST_F(vector, iterator)
{
	Vector v;
	EXPECT_EQ(v.begin(), v.end());
}


TEST_F(vector, types)
{
	EXPECT_EQ(typeid(Vector::allocator_type), typeid(ftc::Allocator<ftc::Data>));
	EXPECT_EQ(typeid(Vector::pointer), typeid(ftc::Data *));
	EXPECT_EQ(typeid(Vector::const_pointer), typeid(const ftc::Data *));
	EXPECT_EQ(typeid(Vector::value_type), typeid(ftc::Data));
	EXPECT_EQ(typeid(Vector::reference), typeid(ftc::Data &));             // あんま意味ない
	EXPECT_EQ(typeid(Vector::const_reference), typeid(const ftc::Data &)); // あんま意味ない
	EXPECT_EQ(typeid(Vector::size_type), typeid(std::size_t));
	EXPECT_EQ(typeid(Vector::difference_type), typeid(std::ptrdiff_t));
}
