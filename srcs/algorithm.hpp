#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft
{
	template <class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, (void)++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate cmp)
	{
		for (; first1 != last1; ++first1, (void)++first2) {
			if (!bool(cmp(*first1, *first2))) {
				return false;
			}
		}
		return true;
	}
} // namespace ft

#endif
