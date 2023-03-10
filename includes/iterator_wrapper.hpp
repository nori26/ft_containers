#ifndef ITERATOR_WRAPPER_HPP
#define ITERATOR_WRAPPER_HPP

#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <typename Itr, typename Container>
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

		// clang-format off
		// for T* -> const T*
		template <typename T>
		iterator_wrapper(
			const iterator_wrapper
			<
				T,
				typename enable_if
				<
					is_convertible<T, Itr>::value,
					Container
				>::type
			> &other
		)
			: itr_(other.base())
		{}
		// clang-format on

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

		iterator_wrapper operator+(difference_type n) const
		{
			return iterator_wrapper(itr_ + n);
		}

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
	template <typename Iterator, typename Container>
	inline bool operator==(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator==(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return lhs.base() == rhs.base();
	}

	template <typename Iterator, typename Container>
	inline bool operator!=(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator!=(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return !(lhs == rhs);
	}

	template <typename Iterator, typename Container>
	inline bool operator<(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator<(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return lhs.base() < rhs.base();
	}

	template <typename Iterator, typename Container>
	inline bool operator>(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return rhs < lhs;
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator>(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return rhs < lhs;
	}

	template <typename Iterator, typename Container>
	inline bool operator<=(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator<=(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return !(lhs > rhs);
	}

	template <typename Iterator, typename Container>
	inline bool operator>=(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline bool operator>=(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return !(lhs < rhs);
	}

	template <typename Iterator, typename Container>
	inline iterator_wrapper<Iterator, Container> operator+(
		typename iterator_wrapper<Iterator, Container>::difference_type n,
		const iterator_wrapper<Iterator, Container>                    &it
	)
	{
		return iterator_wrapper<Iterator, Container>(it.base() + n);
	}

	template <typename Iterator, typename Container>
	inline typename iterator_wrapper<Iterator, Container>::difference_type operator-(
		const iterator_wrapper<Iterator, Container> &lhs,
		const iterator_wrapper<Iterator, Container> &rhs
	)
	{
		return lhs.base() - rhs.base();
	}

	template <typename Iterator1, typename Iterator2, typename Container>
	inline typename iterator_wrapper<Iterator1, Container>::difference_type operator-(
		const iterator_wrapper<Iterator1, Container> &lhs,
		const iterator_wrapper<Iterator2, Container> &rhs
	)
	{
		return lhs.base() - rhs.base();
	}
} // namespace ft

#endif
