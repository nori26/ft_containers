#include "gtest.h"

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

TEST_F(vector, elem_access_ret_type)
{
	Vector v;
	v.push_back(1);

	EXPECT_EQ(typeid(Vector::reference), typeid(v[0]));      // あんま意味ない
	EXPECT_EQ(typeid(Vector::reference), typeid(v.at(0)));   // あんま意味ない
	EXPECT_EQ(typeid(Vector::reference), typeid(v.back()));  // あんま意味ない
	EXPECT_EQ(typeid(Vector::reference), typeid(v.front())); // あんま意味ない
	EXPECT_EQ(typeid(Vector::pointer), typeid(v.data()));    // あんま意味ない

	ftc::Data        &ref1 = v[0];
	ftc::Data        &ref2 = v.at(0);
	ftc::Data        &ref3 = v.back();
	ftc::Data        &ref4 = v.front();
	ftc::Data *const &p    = v.data();
	ftc::Data *const &p2   = v.data();
	EXPECT_EQ(&ref1, &v[0]);
	EXPECT_EQ(&ref2, &v.at(0));
	EXPECT_EQ(&ref3, &v.back());
	EXPECT_EQ(&ref4, &v.front());
	EXPECT_NE(&p, &p2);
}

TEST_F(vector, elem_access_ret_type_const)
{
	const Vector v(1, 1);

	EXPECT_EQ(typeid(Vector::const_reference), typeid(v[0]));      // あんま意味ない
	EXPECT_EQ(typeid(Vector::const_reference), typeid(v.at(0)));   // あんま意味ない
	EXPECT_EQ(typeid(Vector::const_reference), typeid(v.back()));  // あんま意味ない
	EXPECT_EQ(typeid(Vector::const_reference), typeid(v.front())); // あんま意味ない
	EXPECT_EQ(typeid(Vector::const_pointer), typeid(v.data()));    // あんま意味ない

	const ftc::Data        &ref1 = v[0];
	const ftc::Data        &ref2 = v.at(0);
	const ftc::Data        &ref3 = v.back();
	const ftc::Data        &ref4 = v.front();
	const ftc::Data *const &p    = v.data();
	const ftc::Data *const &p2   = v.data();
	EXPECT_EQ(&ref1, &v[0]);
	EXPECT_EQ(&ref2, &v.at(0));
	EXPECT_EQ(&ref3, &v.back());
	EXPECT_EQ(&ref4, &v.front());
	EXPECT_NE(&p, &p2);
}

TEST_F(vector, at_empty)
{
	Vector v;

	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	EXPECT_THROW(v.at(0), std::out_of_range);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_TRUE(v.empty());
}

TEST_F(vector, at)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v.at(i), a[i]);
	}
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_THROW(v.at(ARRAY_SIZE(a)), std::out_of_range);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	v.at(0) = 10;
	EXPECT_EQ(v.at(0), 10);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, at_empty_const)
{
	const Vector v;

	EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST_F(vector, at_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v.at(i), a[i]);
	}
	EXPECT_THROW(v.at(ARRAY_SIZE(a)), std::out_of_range);
}

TEST_F(vector, operator_brackets)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	ftc::Data        *p   = v.data();
	Vector::size_type cap = v.capacity();
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v[i], a[i]);
	}
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	v[0] = 10;
	EXPECT_EQ(v[0], 10);
	EXPECT_EQ(v.data(), p);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, operator_brackets_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(v[i], a[i]);
	}
}

TEST_F(vector, data_empty)
{
	Vector v;

	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
	EXPECT_EQ(v.size(), 0U);
	EXPECT_EQ(v.capacity(), 0U);
}

TEST_F(vector, data_empty_const)
{
	const Vector v;

	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
}

TEST_F(vector, data)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	Vector::size_type cap = v.capacity();
	ftc::Data        *p   = v.data();
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(p[i], a[i]);
	}
	p[0] = 10;
	EXPECT_EQ(v[0], 10);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, data_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	const ftc::Data *p = v.data();
	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_EQ(p[i], a[i]);
	}
}

TEST_F(vector, front)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v(a, a + ARRAY_SIZE(a));

	Vector::size_type cap = v.capacity();
	ftc::Data        *p   = v.data();
	EXPECT_EQ(v.front(), a[0]);
	v.front() = 10;
	EXPECT_EQ(v.front(), 10);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v.data(), p);
}

TEST_F(vector, front_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	Vector::size_type cap = v.capacity();
	EXPECT_EQ(v.front(), a[0]);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, back)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v(a, a + ARRAY_SIZE(a));

	Vector::size_type cap = v.capacity();
	ftc::Data        *p   = v.data();
	EXPECT_EQ(v.back(), a[ARRAY_SIZE(a) - 1]);
	v.back() = 10;
	EXPECT_EQ(v.back(), 10);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
	EXPECT_EQ(v.data(), p);
}

TEST_F(vector, back_const)
{
	ftc::Data    a[] = {0, 1, 2, 3};
	const Vector v(a, a + ARRAY_SIZE(a));

	Vector::size_type cap = v.capacity();
	EXPECT_EQ(v.back(), a[ARRAY_SIZE(a) - 1]);
	EXPECT_EQ(v.capacity(), cap);
	EXPECT_EQ(v.size(), ARRAY_SIZE(a));
}

TEST_F(vector, at_empty_exception)
{
	Vector           v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST_F(vector, at_exception)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;
	ftc::initv(v, a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_NO_THROW(v.at(i));
	}
	EXPECT_THROW(v.at(ARRAY_SIZE(a)), std::out_of_range);
}

TEST_F(vector, at_empty_const_exception)
{
	const Vector     v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_THROW(v.at(0), std::out_of_range);
}

TEST_F(vector, at_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_NO_THROW(v.at(i));
	}
	EXPECT_THROW(v.at(ARRAY_SIZE(a)), std::out_of_range);
}

TEST_F(vector, operator_brackets_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	Vector           v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_NO_THROW(v[i]);
	}
}

TEST_F(vector, operator_brackets_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	for (size_t i = 0; i < ARRAY_SIZE(a); i++) {
		EXPECT_NO_THROW(v[i]);
	}
}

TEST_F(vector, data_empty_exception)
{
	Vector           v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
}

TEST_F(vector, data_empty_const_exception)
{
	const Vector     v;
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_EQ(v.data(), (ftc::Data *)NULL);
}

TEST_F(vector, data_exception)
{
	ftc::Data a[] = {0, 1, 2, 3};
	Vector    v;

	ftc::initv(v, a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.data());
}

TEST_F(vector, data_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.data());
}

TEST_F(vector, front_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	Vector           v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.front());
}

TEST_F(vector, front_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.front());
}

TEST_F(vector, back_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	Vector           v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.back());
}

TEST_F(vector, back_const_exception)
{
	ftc::Data        a[] = {0, 1, 2, 3};
	const Vector     v(a, a + ARRAY_SIZE(a));
	AllocExceptionOn e(1);
	ftc::ExceptionOn e2(1);

	EXPECT_NO_THROW(v.back());
}
