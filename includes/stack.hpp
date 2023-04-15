#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = vector<T> >
	class stack
	{
	  public:
		typedef Container                                container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type       size_type;

	  protected:
		container_type c;

	  public:
		stack() : c() {}

		stack(const container_type &container) : c(container) {}

		stack(const stack &other) : c(other.c) {}

		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}

		void push(const value_type &value)
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		template <typename T1, typename T2>
		friend bool operator==(const stack<T1, T2> &rhs, const stack<T1, T2> &lhs);
		template <typename T1, typename T2>
		friend bool operator<(const stack<T1, T2> &rhs, const stack<T1, T2> &lhs);
	};

	template <typename T, typename Container>
	inline bool operator==(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return rhs.c == lhs.c;
	}

	template <typename T, typename Container>
	inline bool operator!=(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return !(rhs == lhs);
	}

	template <typename T, typename Container>
	inline bool operator<(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return rhs.c < lhs.c;
	}

	template <typename T, typename Container>
	inline bool operator>(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return lhs < rhs;
	}

	template <typename T, typename Container>
	inline bool operator<=(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Container>
	inline bool operator>=(const stack<T, Container> &rhs, const stack<T, Container> &lhs)
	{
		return !(rhs < lhs);
	}
} // namespace ft

#endif
