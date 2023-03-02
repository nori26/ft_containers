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
		iterator_wrapper() : itr_() {}

		explicit iterator_wrapper(const iterator_type &itr) : itr_(itr) {}

		// TODO enable_if for non-const ptr -> const ptr?
		iterator_wrapper(const iterator_wrapper &other) : itr_(other.itr_) {}

		iterator_type base() const
		{
			return itr_;
		}

		iterator_wrapper &operator=(const iterator_wrapper &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			itr_ = rhs.itr_;
			return *this;
		}

		iterator_wrapper &operator+=(difference_type n)
		{
			itr_ += n;
			return *this;
		}

		iterator_wrapper &operator-=(difference_type n)
		{
			itr_ -= n;
			return *this;
		}

		iterator_wrapper &operator++()
		{
			++itr_;
			return *this;
		}

		iterator_wrapper operator++(int)
		{
			return iterator_wrapper(itr_++);
		}

		iterator_wrapper &operator--()
		{
			--itr_;
			return *this;
		}

		iterator_wrapper operator--(int)
		{
			return iterator_wrapper(itr_--);
		}

		// TODO signed test
		reference operator[](difference_type n) const
		{
			return itr_[n];
		}

		reference operator*() const
		{
			return *itr_;
		}

		pointer operator->() const
		{
			return itr_;
		}

		// TODO signed test
		iterator_wrapper operator+(difference_type n) const
		{
			return iterator_wrapper(itr_ + n);
		}

		// TODO signed test
		iterator_wrapper operator-(difference_type n) const
		{
			return iterator_wrapper(itr_ - n);
		}
	};

	// template <typename T>
	// bool operator==(const T &, const T &) {return true;}
	// みたいな定義と衝突するので、
	// 全ての比較演算子、operator-について2種類の関数テンプレートをこのスコープに定義する必要がある
	// template引数を2つ取る方は、constとnon-constの演算に使用される
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

	template <typename Iterator>
	inline iterator_wrapper<Iterator> operator+(
		typename iterator_wrapper<Iterator>::difference_type n, const iterator_wrapper<Iterator> &it
	)
	{
		return iterator_wrapper<Iterator>(it.base() + n);
	}

	template <typename Iterator>
	inline typename iterator_wrapper<Iterator>::difference_type
	operator-(const iterator_wrapper<Iterator> &lhs, const iterator_wrapper<Iterator> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline typename iterator_wrapper<Iterator1>::difference_type
	operator-(const iterator_wrapper<Iterator1> &lhs, const iterator_wrapper<Iterator2> &rhs)
	{
		return lhs.base() - rhs.base();
	}
} // namespace ft

#endif
