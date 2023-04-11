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
		typename Allocator = std::allocator<pair<const Key, Mapped> > >
	class map
	{
	  public:
		typedef Key                                      key_type;
		typedef Mapped                                   mapped_type;
		typedef pair<const key_type, mapped_type>        value_type;
		typedef Compare                                  key_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;

	  private:
		typedef map_value_compare<key_type, mapped_type, key_compare> tree_compare;
		typedef rb_tree<key_type, value_type, tree_compare, allocator_type> tree_type;

	  public:
		typedef typename tree_type::iterator               iterator;
		typedef typename tree_type::const_iterator         const_iterator;
		typedef typename tree_type::reverse_iterator       reverse_iterator;
		typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
		typedef typename tree_type::size_type              size_type;
		typedef typename tree_type::difference_type        difference_type;

	  private:
		tree_type tree_;

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
		map() : tree_() {}

		explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type())
			: tree_(tree_compare(comp), alloc)
		{}

		template <class InputIt>
		map(InputIt          first,
			InputIt          last,
			const Compare   &comp  = Compare(),
			const Allocator &alloc = Allocator())
			: tree_(tree_compare(comp), alloc)
		{
			insert(first, last);
		}

		map(const map &other) : tree_(other.tree_) {}

		// std::swap(tree_, other.tree_)では、
		// tree側でstd::swapがオーバーロードされていない場合O(1)にならない
		void swap(map &other)
		{
			tree_.swap(other.tree_);
		}

		map &operator=(const map &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			tree_ = rhs.tree_;
			return *this;
		}

		pair<iterator, bool> insert(const value_type &value)
		{
			return tree_.insert(value);
		}

		iterator insert(iterator hint, const value_type &value)
		{
			return tree_.insert(hint, value);
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			tree_.insert(first, last);
		}

		iterator erase(iterator pos)
		{
			return tree_.erase(pos);
		}

		iterator erase(iterator first, iterator last)
		{
			return tree_.erase(first, last);
		}

		size_type erase(const key_type &key)
		{
			return tree_.erase(key);
		}

		iterator find(const key_type &key)
		{
			return tree_.find(key);
		}

		const_iterator find(const key_type &key) const
		{
			return tree_.find(key);
		}

		iterator lower_bound(const key_type &key)
		{
			return tree_.lower_bound(key);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			return tree_.lower_bound(key);
		}

		iterator upper_bound(const key_type &key)
		{
			return tree_.upper_bound(key);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			return tree_.upper_bound(key);
		}

		pair<iterator, iterator> equal_range(const Key &key)
		{
			return tree_.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			return tree_.equal_range(key);
		}

		size_type count(const Key &key) const
		{
			return tree_.count(key);
		}

		// treeのget_allocatorが返す方に依存しない && 非explicitを期待しないように、明示的に変換する
		allocator_type get_allocator() const
		{
			return allocator_type(tree_.get_allocator());
		}

		key_compare key_comp() const
		{
			return tree_.value_cmp().key_comp();
		}

		// this->key_comp()を呼び出すと無駄なコピーが起きそうな気配を感じて呼び出してない(実験サボり)
		value_compare value_comp() const
		{
			return value_compare(tree_.value_cmp().key_comp());
		}

		size_type max_size() const
		{
			return tree_.max_size();
		}

		bool empty() const
		{
			return tree_.empty();
		}

		size_type size() const
		{
			return tree_.size();
		}

		void clear()
		{
			tree_.clear();
		}

		// TODO
		mapped_type &operator[](const key_type &key)
		{
			(void)key;
			return begin()->second;
		}

		iterator begin()
		{
			return tree_.begin();
		}

		const_iterator begin() const
		{
			return tree_.begin();
		}

		iterator end()
		{
			return tree_.end();
		}

		const_iterator end() const
		{
			return tree_.end();
		}

		reverse_iterator rbegin()
		{
			return tree_.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return tree_.rbegin();
		}

		reverse_iterator rend()
		{
			return tree_.rend();
		}

		const_reverse_iterator rend() const
		{
			return tree_.rend();
		}
	};

	template <typename Key, typename Mapped, typename Compare>
	class map_value_compare
	{
	  private:
		typedef Key                               key_type;
		typedef Mapped                            mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare                           key_compare;

	  private:
		key_compare cmp_;

	  public:
		map_value_compare() : cmp_() {}

		explicit map_value_compare(const key_compare &c) : cmp_(c) {}

		const key_compare &key_comp() const
		{
			return cmp_;
		}

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
} // namespace ft

#endif
