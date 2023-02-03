#ifndef INIT_VECTOR_HPP
#define INIT_VECTOR_HPP

namespace ft_containers
{
	template <class vector_type, class iterator>
	void initv(vector_type &v, iterator first, iterator last)
	{
		v.reserve(last - first);
		initv_no_reserve(v, first, last);
	}

	template <class vector_type, class iterator>
	void initv_no_reserve(vector_type &v, iterator first, iterator last)
	{
		for (; first != last; first++) {
			v.push_back(*first);
		}
	}
} // namespace ft_containers

#endif
