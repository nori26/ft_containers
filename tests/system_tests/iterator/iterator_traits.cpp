#include "gtest.h"

#include <typeinfo>

#include "data.hpp"
#include "type_utils.hpp"

#ifdef FT_TEST
  #include "iterator.hpp"
#else
  #include <iterator>
namespace ft = std;
#endif

namespace ftc = ft_containers;

class TraitsTest
{
  public:
	typedef int difference_type;
	typedef int value_type;
	typedef int pointer;
	typedef int reference;
	typedef int iterator_category;
};

TEST(iterator_traits, basic)
{
	typedef ft::iterator_traits<TraitsTest> Traits;

	EXPECT_EQ(typeid(int), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(int), typeid(Traits::value_type));
	EXPECT_EQ(typeid(int), typeid(Traits::pointer));
	EXPECT_EQ(typeid(int), typeid(Traits::reference));
	EXPECT_EQ(typeid(int), typeid(Traits::iterator_category));

	EXPECT_FALSE(ftc::is_reference<Traits::value_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::pointer>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::reference>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_reference<Traits::iterator_category>::value);

	EXPECT_FALSE(ftc::is_const<Traits::value_type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_pointer<Traits::pointer>::type>::value);
	EXPECT_FALSE(ftc::is_const<ftc::remove_reference<Traits::reference>::type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::difference_type>::value);
	EXPECT_FALSE(ftc::is_const<Traits::iterator_category>::value);
}

TEST(iterator_traits, ptr_specialization)
{
	typedef ft::iterator_traits<TraitsTest *> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(TraitsTest), typeid(Traits::value_type));
	EXPECT_EQ(typeid(TraitsTest *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(TraitsTest &), typeid(Traits::reference));
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

TEST(iterator_traits, const_ptr_specialization)
{
	typedef ft::iterator_traits<const TraitsTest *> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(const TraitsTest), typeid(Traits::value_type));
	EXPECT_EQ(typeid(const TraitsTest *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(TraitsTest &), typeid(Traits::reference));
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
