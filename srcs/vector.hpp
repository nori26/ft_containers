#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		typedef T *pointer;

		pointer   first_;
		pointer   last_;
		pointer   reserved_last_;
		Allocator allocator_;

	  public:
		vector() : first_(NULL), last_(NULL), reserved_last_(NULL), allocator_(std::allocator<T>())
		{}

	};
} // namespace ft

#endif
