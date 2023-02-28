#include "gtest.h"

#include <limits>
#include <memory>
#include <typeinfo>

#include "allocator.hpp"
#include "data.hpp"
#include "type_utils.hpp"
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

TEST_F(vector, iterator_types)
{
	typedef ft::iterator_traits<Vector::iterator> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(ftc::Data), typeid(Traits::value_type));
	EXPECT_EQ(typeid(ftc::Data *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(ftc::Data &), typeid(Traits::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(Traits::iterator_category));

	EXPECT_FALSE(ftc::is_reference<Traits::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<Traits::reference>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<Traits::value_type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_pointer<Traits::pointer>::type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_reference<Traits::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::iterator_category>::value);
}

TEST_F(vector, iterator_types_const)
{
	typedef ft::iterator_traits<Vector::const_iterator> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(const ftc::Data), typeid(Traits::value_type));
	EXPECT_EQ(typeid(const ftc::Data *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(ftc::Data &), typeid(Traits::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(Traits::iterator_category));

	EXPECT_FALSE(ftc::is_reference<Traits::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::pointer>::value);
	EXPECT_TRUE(ftc::is_reference<Traits::reference>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<Traits::value_type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_pointer<Traits::pointer>::type>::value);
	EXPECT_TRUE(ftc::is_const<ftc::remove_reference<Traits::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::iterator_category>::value);
}

	EXPECT_EQ(v.begin(), v.end());
}

