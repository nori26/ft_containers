#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <memory>
#include <stdexcept>

#include "utility.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		// TODO allocatorから？
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
			destroy(begin(), end());
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
		void push_back(const value_type &value)
		{
			expand_buf_if_needed();
			construct_at_end(value);
		}

		void resize(size_type count, value_type value = value_type())
		{
			(void)count;
			(void)value;
		}

		void reserve(size_type new_cap)
		{
			if (new_cap > max_size()) {
				throw std::length_error("vector::reserve");
			}
			if (new_cap <= capacity()) {
				return;
			}
			vector<value_type, allocator_type> v(allocator_, new_cap);
			v.construct_at_end(begin(), end());
			swap(v);
		}

		iterator insert(iterator pos, const value_type &value)
		{
			(void)pos;
			(void)value;
		}

		void insert(iterator pos, size_type count, const T &value)
		{
			(void)pos;
			(void)count;
			(void)value;
		}

		template <class InputIt>
		void insert(iterator pos, InputIt first, InputIt last)
		{
			(void)pos;
			(void)first;
			(void)last;
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

		const value_type *data() const
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
			return std::min<size_type>(alloc_max, difference_max);
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

		void destroy(pointer ptr)
		{
			allocator_.destroy(ptr);
		}

		void destroy(iterator first, iterator last)
		{
			while (first != last) {
				destroy(first);
				first++;
			}
		}

		void construct_at_end(const_reference value)
		{
			allocator_.construct(last_, value);
			last_++;
		}

		void construct_at_end(iterator first, iterator last)
		{
			for (; first != last; first++) {
				construct_at_end(*first);
			}
		}

		void swap(vector<value_type, allocator_type> &v)
		{
			ft::swap(allocator_, v.allocator_);
			ft::swap(first_, v.first_);
			ft::swap(last_, v.last_);
			ft::swap(reserved_last_, v.reserved_last_);
		}

		void expand_buf_if_needed()
		{
			if (size() < capacity()) {
				return ;
			}
			size_type new_cap;
			if (capacity() == 0) {
				new_cap = 1;
			} else if (capacity() > max_size() / 2) {
				new_cap = max_size();
			} else {
				new_cap = capacity() * 2;
			}
			reserve(new_cap);
		}
	};
} // namespace ft

#endif
