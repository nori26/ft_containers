#ifndef ITERATOR_WRAPPER_HPP
#define ITERATOR_WRAPPER_HPP

#include "iterator.hpp"

namespace ft
{
	template <typename Itr>
	class iterator_wrapper
	{
	  private:
		typedef iterator_traits<Itr> traits;

	  public:
		typedef Itr                                iterator_type;
		typedef typename traits::value_type        value_type;
		typedef typename traits::difference_type   difference_type;
		typedef typename traits::pointer           pointer;
		typedef typename traits::reference         reference;
		typedef typename traits::iterator_category iterator_category;

	  private:
		iterator_type itr_;

	  public:
		iterator_wrapper(const iterator_type &itr = iterator_type()) : itr_(itr) {}

		// TODO enable_if for non-const ptr -> const ptr?
		iterator_wrapper(const iterator_wrapper &other) : itr_(other.itr_) {}

		~iterator_wrapper() {}

		iterator_type &operator=(const iterator_type &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			itr_ = rhs.itr_;
			return *this;
		}

		iterator_type base() const
		{
			return itr_;
		}

		// operator+(const iterator_wrapper &rhs) {}
		// operator+(const iterator_wrapper &rhs) {}
		// operator+=(const iterator_wrapper &rhs) {}

		// operator-(const iterator_wrapper &rhs) {}
		// operator-(const iterator_wrapper &rhs) {}
		// operator-=(const iterator_wrapper &rhs) {}

		// operator++(const iterator_wrapper &rhs) {}
		// operator++(const iterator_wrapper &rhs) {}
		// operator--(const iterator_wrapper &rhs) {}
		// operator--(const iterator_wrapper &rhs) {}

		// operator[](const iterator_wrapper &rhs) {}
		// operator*(const iterator_wrapper &rhs) {}
		// operator->(const iterator_wrapper &rhs) {}
	};

	// template <typename T>
	// bool operator==(const T &, const T &) {return true;}
	// みたいな定義と衝突するので、
	// 全ての比較演算子について2種類の関数テンプレートを定義した
	template <typename Iterator>
	inline bool
	operator==(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator==(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	inline bool
	operator!=(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator!=(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator>
	inline bool
	operator<(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator<(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator>
	inline bool
	operator>(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator>(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Iterator>
	inline bool
	operator<=(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator<=(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator>
	inline bool
	operator>=(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator>=(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

} // namespace ft

#endif
