#include "gtest.h"

#include <set>
#include <string>
#include <typeinfo>
#include <vector>

#include "cmp.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "iterator.hpp"
#else
  #include <iterator>
namespace ft = std;
#endif

namespace ftc = ft_containers;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

template <typename T>
typename ft::iterator_traits<T>::difference_type get_difference_type()
{
	static typename ft::iterator_traits<T>::difference_type var;
	return var;
}

template <typename T>
typename ft::iterator_traits<T>::value_type get_value_type()
{
	static typename ft::iterator_traits<T>::value_type var;
	return var;
}

template <typename T>
typename ft::iterator_traits<T>::pointer get_pointer()
{
	static typename ft::iterator_traits<T>::pointer var;
	return var;
}

template <typename T>
typename ft::iterator_traits<T>::reference get_reference()
{
	static typename ft::iterator_traits<T>::value_type var;
	static typename ft::iterator_traits<T>::reference  ref = var;
	return ref;
}

template <typename T>
typename ft::iterator_traits<T>::iterator_category get_iterator_category()
{
	static typename ft::iterator_traits<T>::iterator_category var;
	return var;
}

class TraitsTest
{
  public:
	typedef int difference_type;
	typedef int value_type;
	typedef int pointer;
	typedef int reference;
	typedef int iterator_category;

	void const_f() const {}
};

TEST(iterator_traits, basic)
{
	typedef ft::iterator_traits<TraitsTest> Traits;

	EXPECT_EQ(typeid(int), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(int), typeid(Traits::value_type));
	EXPECT_EQ(typeid(int), typeid(Traits::pointer));
	EXPECT_EQ(typeid(int), typeid(Traits::reference));
	EXPECT_EQ(typeid(int), typeid(Traits::iterator_category));

	const int &i  = get_difference_type<TraitsTest>();
	const int &i2 = get_difference_type<TraitsTest>();
	const int &j  = get_value_type<TraitsTest>();
	const int &j2 = get_value_type<TraitsTest>();
	const int &k  = get_pointer<TraitsTest>();
	const int &k2 = get_pointer<TraitsTest>();
	const int &l  = get_reference<TraitsTest>();
	const int &l2 = get_reference<TraitsTest>();
	const int &m  = get_iterator_category<TraitsTest>();
	const int &m2 = get_iterator_category<TraitsTest>();

	EXPECT_NE(&i, &i2);
	EXPECT_NE(&j, &j2);
	EXPECT_NE(&k, &k2);
	EXPECT_NE(&l, &l2);
	EXPECT_NE(&m, &m2);
}

TEST(iterator_traits, ptr_specialization)
{
	typedef ft::iterator_traits<TraitsTest *> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(TraitsTest), typeid(Traits::value_type));
	EXPECT_EQ(typeid(TraitsTest *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(TraitsTest &), typeid(Traits::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(Traits::iterator_category));

	const std::ptrdiff_t                  &diff  = get_difference_type<TraitsTest *>();
	const std::ptrdiff_t                  &diff2 = get_difference_type<TraitsTest *>();
	const TraitsTest                      &val   = get_value_type<TraitsTest *>();
	const TraitsTest                      &val2  = get_value_type<TraitsTest *>();
	const TraitsTest *const               &ptr   = get_pointer<TraitsTest *>();
	const TraitsTest *const               &ptr2  = get_pointer<TraitsTest *>();
	TraitsTest                            &ref   = get_reference<TraitsTest *>();
	TraitsTest                            &ref2  = get_reference<TraitsTest *>();
	const std::random_access_iterator_tag &cat   = get_iterator_category<TraitsTest *>();
	const std::random_access_iterator_tag &cat2  = get_iterator_category<TraitsTest *>();

	EXPECT_NE(&diff, &diff2);
	EXPECT_NE(&val, &val2);
	EXPECT_NE(&ptr, &ptr2);
	EXPECT_EQ(&ref, &ref2);
	EXPECT_NE(&cat, &cat2);

	Traits::value_type v;
	Traits::pointer    p = &v;
	Traits::reference  r = v;

	v  = Traits::value_type();
	r  = Traits::value_type();
	*p = Traits::value_type();
}

TEST(iterator_traits, const_ptr_specialization)
{
	typedef ft::iterator_traits<const TraitsTest *> Traits;

	EXPECT_EQ(typeid(std::ptrdiff_t), typeid(Traits::difference_type));
	EXPECT_EQ(typeid(const TraitsTest), typeid(Traits::value_type));
	EXPECT_EQ(typeid(const TraitsTest *), typeid(Traits::pointer));
	EXPECT_EQ(typeid(TraitsTest &), typeid(Traits::reference));
	EXPECT_EQ(typeid(std::random_access_iterator_tag), typeid(Traits::iterator_category));

	const std::ptrdiff_t                  &diff  = get_difference_type<const TraitsTest *>();
	const std::ptrdiff_t                  &diff2 = get_difference_type<const TraitsTest *>();
	const TraitsTest                      &val   = get_value_type<const TraitsTest *>();
	const TraitsTest                      &val2  = get_value_type<const TraitsTest *>();
	const TraitsTest *const               &ptr   = get_pointer<const TraitsTest *>();
	const TraitsTest *const               &ptr2  = get_pointer<const TraitsTest *>();
	const TraitsTest                      &ref   = get_reference<const TraitsTest *>();
	const TraitsTest                      &ref2  = get_reference<const TraitsTest *>();
	const std::random_access_iterator_tag &cat   = get_iterator_category<const TraitsTest *>();
	const std::random_access_iterator_tag &cat2  = get_iterator_category<const TraitsTest *>();

	EXPECT_NE(&diff, &diff2);
	EXPECT_NE(&val, &val2);
	EXPECT_NE(&ptr, &ptr2);
	EXPECT_EQ(&ref, &ref2);
	EXPECT_NE(&cat, &cat2);

	Traits::value_type v;
	Traits::pointer    p = &v;
	Traits::reference  r = v;

	v  = Traits::value_type();
	r.const_f();
	p->const_f();
}
