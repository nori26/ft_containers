#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <memory>

#include "lottery.hpp"

namespace ft_containers
{
	template <class T>
	class Allocator : public std::allocator<T>
	{
	  public:
		template <typename U>
		struct rebind {
			typedef Allocator<U> other;
		};

	  public:
		Allocator() : std::allocator<T>()
		{
			ThrowRandom(__func__);
		}

		T *allocate(std::size_t n, const void *hint = 0)
		{
			ThrowRandom(__func__);
			return std::allocator<T>::allocate(n, hint);
		}

		void deallocate(T *p, std::size_t n)
		{
			ThrowRandom(__func__);
			std::allocator<T>::deallocate(p, n);
		}

		void construct(T *p, const T &val)
		{
			ThrowRandom(__func__);
			std::allocator<T>::construct(p, val);
		}

		void destroy(T *p)
		{
			ThrowRandom(__func__);
			std::allocator<T>::destroy(p);
		}

	  private:
		void ThrowRandom(const std::string &msg)
		{
			if (lottery()) {
				throw std::runtime_error("alloc random throw: " + msg);
			}
		}
	};
} // namespace ft_containers

#endif
