#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>

#include "utility.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	  public:
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::value_type      value_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef pointer                                  iterator;
		typedef const_pointer                            const_iterator;

	  private:
		typedef vector<value_type, allocator_type> instance_type;

	  private:
		pointer   first_;
		pointer   last_;
		pointer   reserved_last_;
		Allocator allocator_;

	  public:
		vector() : first_(NULL), last_(NULL), reserved_last_(NULL), allocator_() {}

		explicit vector(const Allocator &alloc)
			: first_(NULL), last_(NULL), reserved_last_(NULL), allocator_(alloc)
		{}

		vector(const vector &other)
		{
			*this = other;
		}

		~vector()
		{
			destroy_at_end(size());
			deallocate(first_, size());
		}

	  private:
		vector(const Allocator &alloc, size_type cap)
			: first_(NULL), last_(NULL), reserved_last_(NULL), allocator_(alloc)
		{
			if (cap == 0) {
				return;
			}
			first_         = allocate(cap);
			last_          = first_;
			reserved_last_ = first_ + cap;
		}

	  public:
		allocator_type get_allocator() const
		{
			return allocator_;
		}

		void push_back(const value_type &value)
		{
			reserve(recommend_capacity(size() + 1));
			construct_at_end(value);
		}

		void resize(size_type new_size, value_type value = value_type())
		{
			if (new_size < size()) {
				destroy_at_end(size() - new_size);
			} else if (new_size > size()) {
				reserve(recommend_capacity(new_size));
				construct_at_end(new_size - size(), value);
			}
		}

		void reserve(size_type new_cap)
		{
			if (new_cap > max_size()) {
				throw std::length_error("vector::reserve");
			}
			if (new_cap <= capacity()) {
				return;
			}
			instance_type v(allocator_, new_cap);
			v.construct_at_end(begin(), end());
			swap(v);
		}

		iterator insert(iterator pos, const value_type &value)
		{
			difference_type offset_from_begin = pos - begin();
			insert(pos, 1, value);
			return begin() + offset_from_begin;
		}

		void insert(iterator pos, size_type count, const T &value)
		{
			if (count > max_size() - size()) {
				throw std::length_error("vector");
			}
			if (count == 0) {
				return;
			}
			if (count > capacity() - size()) {
				size_type     new_cap = recommend_capacity(size() + count);
				instance_type v(allocator_, new_cap);
				v.construct_at_end(begin(), pos);
				v.construct_at_end(count, value);
				v.construct_at_end(pos, end());
				swap(v);
				return;
			}
			difference_type initialized_size_from_pos = end() - pos;
			iterator        old_end                   = end();
			// = は無くてもいいが、insert_size == 0 が事前にreturnされていないと、
			// std::copy_backward(pos, old_end, old_end); となって未定義
			if (static_cast<difference_type>(count) >= initialized_size_from_pos) {
				size_type uninitialized_count = count - initialized_size_from_pos;
				construct_at_end(uninitialized_count, value);
				construct_at_end(pos, old_end);
				copy_n(pos, initialized_size_from_pos, value);
			} else {
				iterator uninitialized_first_of_pos = end() - count;
				construct_at_end(uninitialized_first_of_pos, end());
				std::copy_backward(pos, uninitialized_first_of_pos, old_end);
				copy_n(pos, count, value);
			}
		}

		// sizeof(InputIt::difference_type) <= sizeof(difference_type) &&
		// sizeof(inputIt::difference_type) <= sizeof(size_type)
		// を期待しているが、STLもそうなっているように見えたので諦めた
		template <class InputIt>
		void insert(iterator pos, InputIt first, InputIt last)
		{
			difference_type insert_size = std::distance(first, last);
			if (insert_size <= 0) {
				return;
			}
			if (insert_size > reserved_last_ - last_) {
				size_type     new_cap = recommend_capacity(size() + insert_size);
				instance_type v(allocator_, new_cap);
				v.construct_at_end(begin(), pos);
				v.construct_at_end(first, last);
				v.construct_at_end(pos, end());
				swap(v);
				return;
			}
			difference_type initialized_size_from_pos = end() - pos;
			iterator        old_end                   = end();
			// = は無くてもいいが、insert_size == 0 が事前にreturnされていないと、
			// std::copy_backward(pos, old_end, old_end); となって未定義
			if (insert_size >= initialized_size_from_pos) {
				InputIt uninitialized_first_of_insert = first;
				std::advance(uninitialized_first_of_insert, initialized_size_from_pos);
				construct_at_end(uninitialized_first_of_insert, last);
				construct_at_end(pos, old_end);
				std::copy(first, uninitialized_first_of_insert, pos);
			} else {
				iterator uninitialized_first_of_pos = end() - insert_size;
				construct_at_end(uninitialized_first_of_pos, end());
				std::copy_backward(pos, uninitialized_first_of_pos, old_end);
				std::copy(first, last, pos);
			}
		}

		// The iterator pos must be valid and dereferenceable.
		// Thus the end() iterator (which is valid, but is not dereferenceable)
		// cannot be used as a value for pos.
		iterator erase(iterator pos)
		{
			difference_type offset = pos - begin();
			std::copy(pos + 1, end(), pos);
			destroy_at_end();
			return begin() + offset;
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type offset = first - begin();
			std::copy(last, end(), first);
			destroy_at_end(last - first);
			return begin() + offset;
		}

		void clear()
		{
			erase(begin(), end());
		}

		vector &operator=(const vector &other)
		{
			if (&other == this) {
				return *this;
			}
			// allocator_; // deallocate
			// allocator_ = other.allocator_;
			return *this;
		}

		reference at(size_type pos)
		{
			if (pos < size()) {
				return first_[pos];
			} else {
				throw std::out_of_range("vector");
			}
		}

		const_reference at(size_type pos) const
		{
			if (pos < size()) {
				return first_[pos];
			} else {
				throw std::out_of_range("vector");
			}
		}

		reference operator[](size_type pos)
		{
			return first_[pos];
		}

		const_reference operator[](size_type pos) const
		{
			return first_[pos];
		}

		size_type size() const
		{
			return last_ - first_;
		}

		size_type capacity() const
		{
			return reserved_last_ - first_;
		}

		pointer data()
		{
			return first_;
		}

		const_pointer data() const
		{
			return first_;
		}

		bool empty() const
		{
			return size() == 0;
		}

		iterator begin()
		{
			return first_;
		}

		const_iterator begin() const
		{
			return first_;
		}

		iterator end()
		{
			return last_;
		}

		const_iterator end() const
		{
			return last_;
		}

		size_type max_size()
		{
			const size_type alloc_max      = allocator_.max_size();
			const size_type difference_max = std::numeric_limits<difference_type>::max();
			return std::min(alloc_max, difference_max);
		}

	  private:
		pointer allocate(size_type n)
		{
			return allocator_.allocate(n);
		}

		void deallocate(pointer p, size_type n)
		{
			allocator_.deallocate(p, n);
		}

		void destroy_at_end()
		{
			if (empty()) {
				return;
			}
			allocator_.destroy(last_ - 1); // TODO &back()
			last_--;
		}

		void destroy_at_end(size_type size)
		{
			for (size_type i = 0; i < size; i++) {
				destroy_at_end();
			}
		}

		void construct_at_end(const_reference value)
		{
			allocator_.construct(last_, value);
			last_++;
		}

		template <class InputIt>
		void construct_at_end(InputIt first, InputIt last)
		{
			for (; first != last; first++) {
				construct_at_end(*first);
			}
		}

		void construct_at_end(size_type n, const_reference value)
		{
			for (size_type i = 0; i < n; i++) {
				construct_at_end(value);
			}
		}

		void copy_n(iterator pos, size_type n, const_reference value)
		{
			for (size_type i = 0; i < n; i++, (void)pos++) {
				*pos = value;
			}
		}

		void swap(instance_type &v)
		{
			ft::swap(allocator_, v.allocator_);
			ft::swap(first_, v.first_);
			ft::swap(last_, v.last_);
			ft::swap(reserved_last_, v.reserved_last_);
		}

		size_type recommend_capacity(size_type new_size)
		{
			if (new_size <= capacity()) {
				return capacity();
			}
			if (new_size > max_size()) {
				throw std::length_error("vector");
			}
			if (capacity() > max_size() / 2) {
				return max_size();
			}
			return std::max(new_size, capacity() * 2);
		}
	};
} // namespace ft

#endif
