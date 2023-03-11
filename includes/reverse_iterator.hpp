#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iterator>

#include "iterator_traits.hpp"

namespace ft
{
	template <typename Iter>
	class reverse_iterator : public std::iterator<
								 typename iterator_traits<Iter>::iterator_category,
								 typename iterator_traits<Iter>::value_type,
								 typename iterator_traits<Iter>::difference_type,
								 typename iterator_traits<Iter>::pointer,
								 typename iterator_traits<Iter>::reference>
	{
	  private:
		typedef iterator_traits<Iter> traits;

		// 定義内で使用するものだけtypedef
		// std::iteratorにも定義されているが、非修飾名としては使用できない
		// (非依存名なので定義時点で名前探索される)
	  public:
		typedef Iter                             iterator_type;
		typedef typename traits::difference_type difference_type;
		typedef typename traits::pointer         pointer;
		typedef typename traits::reference       reference;

		// stlはprotectedだけどなんでわからん
	  private:
		iterator_type current_;

	  public:
		reverse_iterator() : current_() {}

		explicit reverse_iterator(const iterator_type &it) : current_(it) {}

		template <typename T>
		reverse_iterator(const reverse_iterator<T> &other) : current_(other.base())
		{}

		iterator_type base() const
		{
			return current_;
		}

		reverse_iterator &operator=(const reverse_iterator &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			current_ = rhs.current_;
			return *this;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			current_ -= n;
			return *this;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			current_ += n;
			return *this;
		}

		reverse_iterator &operator++()
		{
			--current_;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			return reverse_iterator(current_--);
		}

		reverse_iterator &operator--()
		{
			++current_;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			return reverse_iterator(current_++);
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		// BidirectionalIteratorにはoperator-がないので、operator--で実装
		reference operator*() const
		{
			return *--iterator_type(current_);
		}

		pointer operator->() const
		{
			return &operator*();
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(current_ - n);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current_ + n);
		}
	};

	// template <typename T>
	// bool operator==(const T &, const T &) {return true;}
	// みたいな定義と衝突するので、
	// 全ての比較演算子、operator-について2種類の関数テンプレートをこのスコープに定義する必要がある
	// template引数を2つ取る方は、constとnon-constの演算に使用される
	template <typename Iterator>
	inline bool
	operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator>
	inline bool
	operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator>
	inline bool
	operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename Iterator>
	inline bool
	operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return rhs < lhs;
	}

	template <typename Iterator>
	inline bool
	operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator>
	inline bool
	operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator1, typename Iterator2>
	inline bool
	operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator>
	inline reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &it
	)
	{
		return reverse_iterator<Iterator>(it.base() - n);
	}

	template <typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs)
	{
		return rhs.base() - lhs.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline typename reverse_iterator<Iterator1>::difference_type
	operator-(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
	{
		return rhs.base() - lhs.base();
	}
} // namespace ft
#endif
