#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>

#include "rb_tree.hpp"
#include "utility.hpp"

namespace ft
{
	template <typename Key, typename Mapped, typename Compare>
	class map_value_compare;
	template <typename Key, typename Value>
	class map_key_of_value;

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
		typedef map_value_compare<key_type, mapped_type, key_compare>       tree_compare;
		typedef map_key_of_value<key_type, value_type>                      key_of_value;
		typedef rb_tree<key_type, value_type, key_of_value, tree_compare, allocator_type> tree_type;

	  public:
		typedef typename tree_type::iterator               iterator;
		typedef typename tree_type::const_iterator         const_iterator;
		typedef typename tree_type::reverse_iterator       reverse_iterator;
		typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
		// typedef typename tree_type::size_type       size_type;
		// typedef typename tree_type::difference_type difference_type;

	  private:
		tree_type tree;

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

	  public:
		map() : tree() {}

		// explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type())
		// 	: tree(comp, alloc)
		// {}
		void insert(const value_type &v)
		{
			tree.insert(v);
		}

		iterator begin()
		{
			return tree.begin();
		}

		const_iterator begin() const
		{
			return tree.begin();
		}

		iterator end()
		{
			return tree.end();
		}

		const_iterator end() const
		{
			return tree.end();
		}

		reverse_iterator rbegin()
		{
			return tree.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return tree.rbegin();
		}

		reverse_iterator rend()
		{
			return tree.rend();
		}

		const_reverse_iterator rend() const
		{
			return tree.rend();
		}
	};

	template <typename Key, typename Mapped, typename Compare>
	class map_value_compare
	{
	  private:
		typedef Key                                   key_type;
		typedef Mapped                                mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare                               key_compare;

	  private:
		key_compare cmp_;

	  public:
		map_value_compare() : cmp_() {}

		explicit map_value_compare(const key_compare &c) : cmp_(c) {}

		bool operator()(const value_type &a, const value_type &b) const
		{
			return cmp_(a.first, b.first);
		}

		bool operator()(const value_type &a, const key_type &b) const
		{
			return cmp_(a.first, b);
		}

		bool operator()(const key_type &a, const value_type &b) const
		{
			return cmp_(a, b.first);
		}
	};

	template <typename Key, typename Value>
	class map_key_of_value
	{
	  public:
		const Key &operator()(const Value &v) const
		{
			return v.first;
		}
	};

} // namespace ft

#endif
