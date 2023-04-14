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
		struct rebind
		{
			typedef Allocator<U> other;
		};
		class ExceptionOn
		{
		  private:
			bool tmp_;
			int  tmp_rate_;

		  public:
			ExceptionOn(int rate = 3)
			{
				tmp_            = exception_on_;
				exception_on_   = true;
				tmp_rate_       = exception_rate_;
				exception_rate_ = rate;
			}
			~ExceptionOn()
			{
				exception_on_   = tmp_;
				exception_rate_ = tmp_rate_;
			}
		};

	  private:
		static bool exception_on_;
		static int  exception_rate_;

	  public:
		void *id;

	  public:
		Allocator() : std::allocator<T>(), id(this)
		{
			ThrowRandom(__func__);
		}

		template <typename Type>
		Allocator(const Allocator<Type> &other) : std::allocator<T>(other)
		{
			ThrowRandom(__func__);
			id = other.id;
		}

		Allocator &operator=(const Allocator &rhs)
		{
			ThrowRandom(__func__);
			if (&rhs == this) {
				return *this;
			}
			std::allocator<T>::operator=(rhs);
			id = rhs.id;
			return *this;
		}

		T *allocate(std::size_t n, const void *hint = 0)
		{
			ThrowRandom(__func__);
			return std::allocator<T>::allocate(n, hint);
		}

		void deallocate(T *p, std::size_t n)
		{
			// ThrowRandom(__func__);
			std::allocator<T>::deallocate(p, n);
		}

		void construct(T *p, const T &val)
		{
			ThrowRandom(__func__);
			std::allocator<T>::construct(p, val);
		}

		void destroy(T *p)
		{
			// ThrowRandom(__func__);
			std::allocator<T>::destroy(p);
		}

		void *get_id() const
		{
			return id;
		}

	  private:
		void ThrowRandom(const std::string &msg)
		{
			if (exception_on_ && lottery(exception_rate_)) {
				throw std::runtime_error("alloc random throw: " + msg);
			}
		}
	};

	template <class T>
	class Allocator2 : public Allocator<T>
	{
	  public:
		template <typename U>
		struct rebind
		{
			typedef Allocator2<U> other;
		};
		Allocator2() : Allocator<T>() {}

		template <typename Type>
		Allocator2(const Allocator<Type> &other) : Allocator<T>(other)
		{}
	};

	template <typename T>
	inline bool operator==(const Allocator2<T> &lhs, const Allocator2<T> &rhs)
	{
		(void)lhs, (void)rhs;
		return false;
	}

	template <typename T1, typename T2>
	inline bool operator==(const Allocator2<T1> &lhs, const Allocator2<T2> &rhs)
	{
		(void)lhs, (void)rhs;
		return false;
	}

	template <typename T>
	inline bool operator!=(const Allocator2<T> &lhs, const Allocator2<T> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename T2>
	inline bool operator!=(const Allocator2<T1> &lhs, const Allocator2<T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	bool Allocator<T>::exception_on_ = false;
	template <class T>
	int Allocator<T>::exception_rate_ = 3;
} // namespace ft_containers

#endif
