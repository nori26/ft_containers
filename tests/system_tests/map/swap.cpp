#include "gtest.h"

#include <algorithm>
#include <climits>
#include <typeinfo>

#include "allocator.hpp"
#include "cmp.hpp"
#include "data.hpp"

#ifdef FT_TEST
  #include "map.hpp"
#else
  #include <map>
namespace ft = std;
#endif

namespace ftc = ft_containers;
typedef ft::pair<const ftc::Data, ftc::Data> ValueType;

typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator<ValueType> >  Map;
typedef ft::map<ftc::Data, ftc::Data, MapCmp<ftc::Data>, ftc::Allocator2<ValueType> > Map2;
typedef ftc::Allocator<ValueType>::ExceptionOn AllocExceptionOn;

#define ARRAY_SIZE(ary) (sizeof(ary) / sizeof(ary[0]))

TEST(map, swap_ret_type)
{
	Map m1;
	Map m2;

	EXPECT_EQ(typeid(void), typeid(m1.swap(m2)));
}

TEST(map, swap_empty)
{
	Map            m1;
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	Map            m2;
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
}

TEST(map, swap)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_self)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	m1.swap(m1);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m1_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap2)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap3)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_empty_specialize)
{
	Map            m1;
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	Map            m2;
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
}

TEST(map, swap_specialize2)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_specialize3)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_specialize)
{
	ValueType      a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map            m1(a1, a1 + ARRAY_SIZE(a1));
	void          *m1_old_alloc = m1.get_allocator().get_id();
	Map::size_type m1_old_size  = m1.size();

	ValueType      a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map            m2(a2, a2 + ARRAY_SIZE(a2));
	void          *m2_old_alloc = m2.get_allocator().get_id();
	Map::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_empty_exception)
{
	Map              m1;
	Map              m2;
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(m1.swap(m2));
}

TEST(map, swap_exception)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(m1.swap(m2));
}

TEST(map, swap_exception2)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(m1.swap(m2));
}

TEST(map, swap_exception3)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(m1.swap(m2));
}

TEST(map, swap_empty_specialize_exception)
{
	Map              m1;
	Map              m2;
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(m1, m2));
}

TEST(map, swap_specialize_exception)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(m1, m2));
}

TEST(map, swap_specialize_exception2)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(m1, m2));
}

TEST(map, swap_specialize_exception3)
{
	ValueType        a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	ValueType        a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map              m1(a1, a1 + ARRAY_SIZE(a1));
	Map              m2(a2, a2 + ARRAY_SIZE(a2));
	ftc::ExceptionOn e(1);
	AllocExceptionOn e2(1);

	EXPECT_NO_THROW(std::swap(m1, m2));
}

TEST(map, swap_empty_alloc2)
{
	Map2            m1;
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	Map2            m2;
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
}

TEST(map, swap_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_self_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	m1.swap(m1);
	EXPECT_EQ(m1.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m1.size(), m1_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap2_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap3_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	m1.swap(m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_empty_specialize_alloc2)
{
	Map2            m1;
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	Map2            m2;
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
}

TEST(map, swap_specialize2_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_specialize3_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}

TEST(map, swap_specialize_alloc2)
{
	ValueType       a1[] = {ValueType(1, 1), ValueType(2, 2), ValueType(3, 3)};
	Map2            m1(a1, a1 + ARRAY_SIZE(a1));
	void           *m1_old_alloc = m1.get_allocator().get_id();
	Map2::size_type m1_old_size  = m1.size();

	ValueType       a2[] = {ValueType(4, 4), ValueType(5, 5), ValueType(6, 6)};
	Map2            m2(a2, a2 + ARRAY_SIZE(a2));
	void           *m2_old_alloc = m2.get_allocator().get_id();
	Map2::size_type m2_old_size  = m2.size();

	std::swap(m1, m2);
	EXPECT_EQ(m1.get_allocator().get_id(), m2_old_alloc);
	EXPECT_EQ(m1.size(), m2_old_size);
	Map::iterator it = m1.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a2) || it != m1.end(); i++) {
		EXPECT_EQ(*it++, a2[i]);
	}

	EXPECT_EQ(m2.get_allocator().get_id(), m1_old_alloc);
	EXPECT_EQ(m2.size(), m1_old_size);
	it = m2.begin();
	for (size_t i = 0; i < ARRAY_SIZE(a1) || it != m2.end(); i++) {
		EXPECT_EQ(*it++, a1[i]);
	}
}
