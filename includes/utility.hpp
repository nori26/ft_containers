#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type  first;
		second_type second;

		pair() : first(), second() {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		template <typename U1, typename U2>
		pair(const pair<U1, U2> &p) : first(p.first), second(p.second)
		{}

		pair &operator=(const pair &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			first  = rhs.first;
			second = rhs.second;
			return *this;
		}
	};

	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return a.first == b.first && a.second == b.second;
	}

	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return !(a == b);
	}

	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
	}

	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return b < a;
	}

	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return !(b < a);
	}

	template <typename T1, typename T2>
	bool operator>=(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return !(a < b);
	}

	// パラメータが参照型の場合、配列がポインタに変換されない
	// pairのコンストラクタでコピー初期化に失敗するため、値で受け取る
	template <typename T1, typename T2>
	inline pair<T1, T2> make_pair(T1 a, T2 b)
	{
		return pair<T1, T2>(a, b);
	}
} // namespace ft

#endif
