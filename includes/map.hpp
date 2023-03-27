#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

#include "rb_tree.hpp"
#include "utility.hpp"

namespace ft
{
	template <
		typename Key,
		typename Mapped,
		typename Compare   = std::less<Key>,
		typename Allocator = std::allocator<ft::pair<const Key, Mapped> > >
	class map
	{
	  public:
		typedef Key                                      key_type;
		typedef Mapped                                   mapped_type;
		typedef ft::pair<const key_type, mapped_type>    value_type;
		typedef Compare                                  key_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;

	  private:
		typedef rb_tree<key_type, mapped_type> tree_type;

		//   public:
		// 	typedef typename tree_type::iterator        iterator;
		// 	typedef typename tree_type::const_iterator  const_iterator;
		// 	typedef typename tree_type::size_type       size_type;
		// 	typedef typename tree_type::difference_type difference_type;

	  public:
		class value_compare
		{
			// mapからはインスタンス化可能
			friend class map;

		  public:
			// 関数アダプタが要求する型
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			typedef bool       result_type;

		  protected:
			key_compare comp;

			// コピー初期化以外のインスタン化を制限
			value_compare(key_compare c) : comp(c) {}

		  public:
			bool operator()(const value_type &a, const value_type &b) const
			{
				return comp(a.first, b.first);
			}
		};

	  private:
		rb_tree<key_type, mapped_type> tree;

	  public:
		map() : tree() {}
	};
} // namespace ft

#endif
