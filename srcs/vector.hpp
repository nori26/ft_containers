#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		// TODO allocatorから？
	  public:
		typedef T          *pointer;
		typedef T          *iterator;
		typedef const T    *const_iterator;
		typedef T          &reference;
		typedef const T    &const_reference;
		typedef std::size_t size_type;

		pointer   first_;
		pointer   last_;
		pointer   reserved_last_;
		Allocator allocator_;

	  public:
		vector() : first_(NULL), last_(NULL), reserved_last_(NULL), allocator_() {}

		vector(const vector &other)
		{
			*this = other;
		}

		void push_back(const T &value)
		{
			(void)value;
		}

		void resize(size_type count, T value = T())
		{
			(void)count;
			(void)value;
		}

		void reserve(size_type new_cap)
		{
			(void)new_cap;
		}

		iterator insert(iterator pos, const T &value)
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

		const T *data() const
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

		void construct(pointer ptr, const_reference value)
		{
			allocator_.construct(ptr, value);
		}

		void construct(pointer dest, pointer src, size_type size)
		{
			for (size_type i = 0; i < size; i++) {
				construct(dest + i, src[i]);
			}
		}

	};
} // namespace ft

#endif
