#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	  public:
		typedef T              *pointer;
		typedef pointer         iterator;
		typedef const iterator  const_iterator;
		typedef T              &reference;
		typedef const reference const_reference;
		typedef std::size_t     size_type;

		pointer   first_;
		pointer   last_;
		pointer   reserved_last_;
		Allocator allocator_;

	  public:
		vector() : first_(NULL), last_(NULL), reserved_last_(NULL), allocator_() {}


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
	};
} // namespace ft

#endif
