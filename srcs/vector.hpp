#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
	  private:
		typedef T *pointer;

	  public:
		typedef std::size_t size_type;

		pointer   first_;
		pointer   last_;
		pointer   reserved_last_;
		Allocator allocator_;

	  public:
		vector() : first_(NULL), last_(NULL), reserved_last_(NULL), allocator_(std::allocator<T>())
		{}

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
