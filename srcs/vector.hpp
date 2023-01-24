#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <limits>
#include <memory>

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

		~vector()
		{
			destroy(begin(), end());
			deallocate(first_, size());
		}

		void push_back(const value_type &value)
		{
			if (size() == capacity()) {
				size_type new_cap = capacity() == 0 ? 1 : capacity() * 2;
				pointer   new_ptr = allocate(new_cap);
				construct(new_ptr, first_, size());
				destroy(begin(), end()); //TODO 例外安全
				deallocate(first_, size());
				last_          = new_ptr + size();
				first_         = new_ptr;
				reserved_last_ = first_ + new_cap;
			}
			construct(first_ + size(), value);
			last_++;
		}

		void resize(size_type count, value_type value = value_type())
		{
			(void)count;
			(void)value;
		}

		void reserve(size_type new_cap)
		{
			(void)new_cap;
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
