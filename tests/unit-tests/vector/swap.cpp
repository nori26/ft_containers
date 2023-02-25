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

TEST_F(vector, swap_ret_type)
{
	Vector v1;
	Vector v2;

	EXPECT_EQ(typeid(void), typeid(v1.swap(v2)));
}

TEST_F(vector, swap_empty)
{
	Vector            v1;
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	Vector            v2;
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	v1.swap(v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
}

TEST_F(vector, swap)
{
	ftc::Data         a1[] = {1, 2, 3};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5, 6};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	v1.swap(v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap_self)
{
	ftc::Data         a1[] = {1, 2, 3};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	v1.swap(v1);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v1_old_size);
	EXPECT_EQ(v1.capacity(), v1_old_cap);
	EXPECT_EQ(v1.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v1[i], a1[i]);
	}
}

TEST_F(vector, swap2)
{
	ftc::Data         a1[] = {1, 2};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5, 6};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	v1.swap(v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap3)
{
	ftc::Data         a1[] = {1, 2, 3};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	v1.swap(v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap_empty_specialize)
{
	Vector            v1;
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	Vector            v2;
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	std::swap(v1, v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
}

TEST_F(vector, swap_specialize2)
{
	ftc::Data         a1[] = {1, 2};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5, 6};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	std::swap(v1, v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap_specialize3)
{
	ftc::Data         a1[] = {1, 2, 3};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	std::swap(v1, v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap_specialize)
{
	ftc::Data         a1[] = {1, 2, 3};
	Vector            v1(a1, a1 + ARRAY_SIZE(a1));
	void             *v1_old_alloc = v1.get_allocator().get_id();
	Vector::size_type v1_old_size  = v1.size();
	Vector::size_type v1_old_cap   = v1.capacity();
	ftc::Data        *v1_old_data  = v1.data();

	ftc::Data         a2[] = {4, 5, 6};
	Vector            v2(a2, a2 + ARRAY_SIZE(a2));
	void             *v2_old_alloc = v2.get_allocator().get_id();
	Vector::size_type v2_old_size  = v2.size();
	Vector::size_type v2_old_cap   = v2.capacity();
	ftc::Data        *v2_old_data  = v2.data();

	std::swap(v1, v2);
	EXPECT_EQ(v1.get_allocator().get_id(), v1_old_alloc);
	EXPECT_EQ(v1.size(), v2_old_size);
	EXPECT_EQ(v1.capacity(), v2_old_cap);
	EXPECT_EQ(v1.data(), v2_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a2); i++) {
		EXPECT_EQ(v1[i], a2[i]);
	}

	EXPECT_EQ(v2.get_allocator().get_id(), v2_old_alloc);
	EXPECT_EQ(v2.size(), v1_old_size);
	EXPECT_EQ(v2.capacity(), v1_old_cap);
	EXPECT_EQ(v2.data(), v1_old_data);
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(v2[i], a1[i]);
	}
}

TEST_F(vector, swap_empty_exception)
{
	Vector           v1;
	Vector           v2;
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(v1.swap(v2));
}

TEST_F(vector, swap_exception)
{
	ftc::Data        a1[] = {1, 2, 3};
	ftc::Data        a2[] = {4, 5, 6};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(v1.swap(v2));
}

TEST_F(vector, swap_exception2)
{
	ftc::Data        a1[] = {1, 2};
	ftc::Data        a2[] = {4, 5, 6};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(v1.swap(v2));
}

TEST_F(vector, swap_exception3)
{
	ftc::Data        a1[] = {1, 2, 3};
	ftc::Data        a2[] = {4, 5};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(v1.swap(v2));
}

TEST_F(vector, swap_empty_specialize_exception)
{
	Vector           v1;
	Vector           v2;
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(v1, v2));
}

TEST_F(vector, swap_specialize_exception)
{
	ftc::Data        a1[] = {1, 2, 3};
	ftc::Data        a2[] = {4, 5, 6};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(v1, v2));
}

TEST_F(vector, swap_specialize_exception2)
{
	ftc::Data        a1[] = {1, 2};
	ftc::Data        a2[] = {4, 5, 6};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(v1, v2));
}

TEST_F(vector, swap_specialize_exception3)
{
	ftc::Data        a1[] = {1, 2, 3};
	ftc::Data        a2[] = {4, 5};
	Vector           v1(a1, a1 + ARRAY_SIZE(a1));
	Vector           v2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(v1, v2));
}
