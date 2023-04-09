#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <algorithm>
#include <cassert> // TODO ifdef
#include <iostream>
#include <iterator>
#include <memory>

#include "reverse_iterator.hpp"
#include "utility.hpp"

namespace ft
{
	template <typename Value>
	class rb_tree_iterator;

	template <typename Value>
	class rb_tree_const_iterator;

	template <typename NodeType>
	class rb_tree_generator;

	template <typename Value>
	class rb_tree_node
	{
	  public:
		enum color_type {
			RED,
			BLACK,
		};

	  private:
		typedef Value value_type;
		// アドレス演算子のオーバーロードを回避するための型
		typedef value_type value_ptr_type[1];

		value_ptr_type value_ptr_;
		color_type     color_;
		rb_tree_node  *parent_;
		rb_tree_node  *left_;
		rb_tree_node  *right_;

	  public:
		rb_tree_node(color_type c = BLACK) : value_ptr_(), color_(c), parent_(), left_(), right_()
		{}

		value_type &value()
		{
			return value_ptr_[0];
		}

		value_type *value_ptr()
		{
			return value_ptr_;
		}

		rb_tree_node *&parent()
		{
			return parent_;
		}

		rb_tree_node *&left()
		{
			return left_;
		}

		rb_tree_node *&right()
		{
			return right_;
		}

		color_type &color()
		{
			return color_;
		}

		const value_type &value() const
		{
			return value_ptr_[0];
		}

		const value_type *value_ptr() const
		{
			return value_ptr_;
		}

		const rb_tree_node *parent() const
		{
			return parent_;
		}

		const rb_tree_node *left() const
		{
			return left_;
		}

		const rb_tree_node *right() const
		{
			return right_;
		}

		const color_type &color() const
		{
			return color_;
		}

		void link_left(rb_tree_node *new_left)
		{
			left_ = new_left;
			if (new_left) {
				new_left->parent() = this;
			}
		}

		void link_right(rb_tree_node *new_right)
		{
			right_ = new_right;
			if (new_right) {
				new_right->parent() = this;
			}
		}

		rb_tree_node *max()
		{
			rb_tree_node *node = this;

			while (node->right()) {
				node = node->right();
			}
			return node;
		}

		rb_tree_node *min()
		{
			rb_tree_node *node = this;

			while (node->left()) {
				node = node->left();
			}
			return node;
		}

		const rb_tree_node *max() const
		{
			const rb_tree_node *node = this;

			while (node->right()) {
				node = node->right();
			}
			return node;
		}

		const rb_tree_node *min() const
		{
			const rb_tree_node *node = this;

			while (node->left()) {
				node = node->left();
			}
			return node;
		}
	};

	template <
		typename Key,
		typename Value,
		typename KeyOfValue,
		typename Compare,
		typename Allocator>
	class rb_tree
	{
		// protected for visualize
	  protected:
		typedef rb_tree_node<Value> node_type;
		typedef Compare             value_compare;
		typedef KeyOfValue          key_of_value;

	  private:
		typedef rb_tree_generator<node_type> generator;

	  public:
		typedef Key                                                   key_type;
		typedef Value                                                 value_type;
		typedef Allocator                                             allocator_type;
		typedef size_t                                                size_type;
		typedef ptrdiff_t                                             difference_type;
		typedef typename node_type::color_type                        color_type;
		typedef typename Allocator::template rebind<node_type>::other node_allocator;
		// template 曖昧青解消子でrebindがテンプレートクラスであることを明示する
		// template がない場合、< は小なり演算子として解釈される
		typedef rb_tree_iterator<value_type>         iterator;
		typedef rb_tree_const_iterator<value_type>   const_iterator;
		typedef ft::reverse_iterator<iterator>       reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	  private:
		class node_manager
		{
			rb_tree &tree_;
			class node_creator
			{
				rb_tree   &tree_;
				node_type *node_;

			  public:
				node_creator(rb_tree &tree) : tree_(tree), node_() {}

				node_type *create(const value_type &v)
				{
					node_ = tree_.node_allocator_.allocate(1);
					construct_node(node_, v);
					node_type *ret = node_;
					node_          = NULL;
					return ret;
				}

				// nodeのdestroyはしない
				// valueのコンストラクトで例外が投げられたときのみnodeのdeallocateに到達する
				~node_creator()
				{
					if (node_ == NULL) {
						return;
					}
					tree_.node_allocator_.deallocate(node_, 1);
				}

			  private:
				void construct_node(node_type *n, const value_type &v)
				{
					n->parent() = NULL;
					n->left()   = NULL;
					n->right()  = NULL;
					n->color()  = node_type::RED;
					tree_.get_allocator().construct(n->value_ptr(), v);
				}
			};

		  public:
			node_manager(rb_tree &tree) : tree_(tree) {}

			node_type *create(const value_type &v)
			{
				return node_creator(tree_).create(v);
			}

			void destroy(node_type *n)
			{
				if (n == NULL) {
					return;
				}
				tree_.node_allocator_.destroy(n);
				tree_.node_allocator_.deallocate(n, 1);
			}
		};

	  protected:
		node_type   end_;
		node_type *&root_;

	  private:
		node_manager   node_manager_;
		node_allocator node_allocator_;
		value_compare  cmp_;
		key_of_value   get_key_;
		node_type     *min_;
		size_type      size_;

	  public:
		rb_tree()
			: end_(node_type::BLACK),
			  root_(end_.left()),
			  node_manager_(*this),
			  node_allocator_(),
			  cmp_(),
			  get_key_(),
			  min_(),
			  size_()
		{
			init_structure();
		}

		explicit rb_tree(const value_compare &cmp, const allocator_type &alloc = allocator_type())
			: end_(node_type::BLACK),
			  root_(end_.left()),
			  node_manager_(*this),
			  node_allocator_(alloc),
			  cmp_(cmp),
			  get_key_(),
			  min_(),
			  size_()
		{
			init_structure();
		}

		rb_tree(const rb_tree &other)
			: end_(node_type::BLACK),
			  root_(end_.left()),
			  node_manager_(*this),
			  node_allocator_(other.node_allocator_),
			  cmp_(),
			  get_key_(),
			  min_(),
			  size_()
		{
			init_structure();
			*this = other;
		}

	  private:
		void init_structure()
		{
			end_.right() = reinterpret_cast<node_type *>(-1);
			min_         = &end_;
		}

	  public:
		rb_tree &operator=(const rb_tree &rhs)
		{
			if (&rhs == this) {
				return *this;
			}
			rb_tree t(rhs.value_cmp(), node_allocator_);

			t.insert(rhs.begin(), rhs.end());
			swap(t);
			return *this;
		}

		~rb_tree()
		{
			clear();
		}

		const value_compare &value_cmp() const
		{
			return cmp_;
		}

		void swap(rb_tree &t)
		{
			if (node_allocator_ != t.node_allocator_) {
				std::swap(node_allocator_, t.node_allocator_);
			}
			std::swap(cmp_, t.cmp_);
			std::swap(size_, t.size_);
			std::swap(root_, t.root_);
			end_.link_left(root_);
			t.end_.link_left(t.root_);
			std::swap(min_, t.min_);
			if (min_ == &t.end_) {
				min_ = &end_;
			}
			if (t.min_ == &end_) {
				t.min_ = &t.end_;
			}
		}

		iterator find(const key_type &key)
		{
			iterator it = lower_bound(key);

			if (it == end() || value_cmp()(key, *it)) {
				return end();
			}
			return it;
		}

		const_iterator find(const key_type &key) const
		{
			const_iterator it = lower_bound(key);

			if (it == end() || value_cmp()(key, *it)) {
				return end();
			}
			return it;
		}

		iterator lower_bound(const key_type &key)
		{
			return lower_bound(root_, &end_, key);
		}

		const_iterator lower_bound(const key_type &key) const
		{
			return lower_bound(root_, &end_, key);
		}

		iterator upper_bound(const key_type &key)
		{
			return upper_bound(root_, &end_, key);
		}

		const_iterator upper_bound(const key_type &key) const
		{
			return upper_bound(root_, &end_, key);
		}

	  private:
		iterator lower_bound(node_type *current, node_type *latest_greater_eq, const key_type &key)
		{
			while (current) {
				if (!value_cmp()(current->value(), key)) {
					latest_greater_eq = current;
					current           = current->left();
				} else {
					current = current->right();
				}
			}
			return iterator(latest_greater_eq);
		}

		const_iterator lower_bound(
			const node_type *current, const node_type *latest_greater_eq, const key_type &key
		) const
		{
			while (current) {
				if (!value_cmp()(current->value(), key)) {
					latest_greater_eq = current;
					current           = current->left();
				} else {
					current = current->right();
				}
			}
			return const_iterator(latest_greater_eq);
		}

		iterator upper_bound(node_type *current, node_type *latest_greater, const key_type &key)
		{
			while (current) {
				if (value_cmp()(key, current->value())) {
					latest_greater = current;
					current        = current->left();
				} else {
					current = current->right();
				}
			}
			return iterator(latest_greater);
		}

		const_iterator upper_bound(
			const node_type *current, const node_type *latest_greater, const key_type &key
		) const
		{
			while (current) {
				if (value_cmp()(key, current->value())) {
					latest_greater = current;
					current        = current->left();
				} else {
					current = current->right();
				}
			}
			return const_iterator(latest_greater);
		}

	  public:
		// multimapのような同一キーを許容する構造でも流用できるように、lb, ubでrangeを取る
		// ++itよりもubの方が木を遡ることがない分、平均的にはたぶん少し速いかも
		ft::pair<iterator, iterator> equal_range(const Key &key)
		{
			node_type *saved   = &end_;
			node_type *current = root_;

			while (current) {
				if (value_cmp()(key, current->value())) {
					saved   = current;
					current = current->left();
				} else if (value_cmp()(current->value(), key)) {
					current = current->right();
				} else {
					iterator lb = lower_bound(current, saved, key);
					iterator ub = upper_bound(current->right(), saved, key);
					return ft::make_pair(lb, ub);
				}
			}
			return ft::make_pair(iterator(saved), iterator(saved));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			const node_type *saved   = &end_;
			const node_type *current = root_;

			while (current) {
				if (value_cmp()(key, current->value())) {
					saved   = current;
					current = current->left();
				} else if (value_cmp()(current->value(), key)) {
					current = current->right();
				} else {
					const_iterator lb = lower_bound(current, saved, key);
					const_iterator ub = upper_bound(current->right(), saved, key);
					return ft::make_pair(lb, ub);
				}
			}
			return ft::make_pair(const_iterator(saved), const_iterator(saved));
		}

		size_type count(const Key &key) const
		{
			ft::pair<const_iterator, const_iterator> its = equal_range(key);
			return std::distance(its.first, its.second);
		}

		// TODO あとでhint付に変えるかも
		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (; first != last; ++first) {
				insert(*first);
			}
		}

		pair<iterator, bool> insert(const value_type &value)
		{
			ft::pair<node_type *, node_type **> nodes  = find_pos(get_key_(value));
			node_type                          *parent = nodes.first;
			node_type                         **child  = nodes.second;

			if (*child) {
				return ft::make_pair(*child, false);
			}
			node_type *pos     = node_manager_.create(value);
			*child             = pos;
			(*child)->parent() = parent;
			balance_for_insert(pos);
			if (generator(pos).next() == min_) {
				min_ = pos;
			}
			size_++;
			return ft::make_pair(pos, true);
		}

		void erase(const key_type &key)
		{
			node_type *pos = *find_pos(key).second;
			node_type *parent;
			node_type *child;

			if (pos == NULL) {
				return;
			}
			if (pos == min_) {
				min_ = generator(min_).next();
			}
			if (pos->left()) {
				swap_node(pos, pos->left()->max());
				child  = pos->left();
				parent = pos->parent();
			} else {
				child  = pos->right();
				parent = pos->parent();
			}
			promote_child(pos, child);
			balance_for_erase(parent, child, pos);
			node_manager_.destroy(pos);
			size_--;
		}

		allocator_type get_allocator() const
		{
			return allocator_type(node_allocator_);
		}

		size_type max_size() const
		{
			return node_allocator_.max_size();
		}

		bool empty() const
		{
			return size() == 0;
		}

		size_type size() const
		{
			return size_;
		}

		void clear()
		{
			delete_subtree(root_);
			root_ = NULL;
			min_  = &end_;
			size_ = 0;
		}

		iterator begin()
		{
			return iterator(min_);
		}

		const_iterator begin() const
		{
			return const_iterator(min_);
		}

		iterator end()
		{
			return iterator(&end_);
		}

		const_iterator end() const
		{
			return const_iterator(&end_);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

	  private:
		ft::pair<node_type *, node_type **> find_pos(const key_type &key)
		{
			node_type  *parent = &end_;
			node_type **child  = &end_.left();

			while (*child) {
				value_type &value = (*child)->value();
				if (value_cmp()(key, value)) {
					parent = *child;
					child  = &(*child)->left();
				} else if (value_cmp()(value, key)) {
					parent = *child;
					child  = &(*child)->right();
				} else {
					break;
				}
			}
			return ft::make_pair(parent, child);
		}

		void balance_for_insert(node_type *top)
		{
			for (; top != &end_; top = top->parent()) {
				if (is_red(top)) {
					continue;
				}
				node_type *left  = top->left();
				node_type *right = top->right();
				if (is_red(left) && is_red(right) &&
					(has_red_child(left) || has_red_child(right))) {
					top->color()   = node_type::RED;
					left->color()  = node_type::BLACK;
					right->color() = node_type::BLACK;
					continue;
				}
				if (is_red(left)) {
					balance_left_for_insert(top);
				} else {
					balance_right_for_insert(top);
				}
				break;
			}
			root_->color() = node_type::BLACK;
		}

		void balance_left_for_insert(node_type *top)
		{
			if (is_red(top->left()->right())) {
				rotate_left(top->left());
			}
			if (is_red(top->left()->left())) {
				top                   = rotate_right(top);
				top->right()->color() = node_type::RED;
				top->color()          = node_type::BLACK;
			}
		}

		void balance_right_for_insert(node_type *top)
		{
			if (is_red(top->right()->left())) {
				rotate_left(top->right());
			}
			if (is_red(top->right()->right())) {
				top                  = rotate_left(top);
				top->left()->color() = node_type::RED;
				top->color()         = node_type::BLACK;
			}
		}

		// childがNULLの場合もあるのでparentを受け取る
		// grand_parentがend_の可能性もあるのでポインタで比較
		void promote_child(node_type *parent, node_type *child)
		{
			assert(parent && parent->parent());
			node_type *grand_parent = parent->parent();

			if (grand_parent->left() == parent) {
				grand_parent->link_left(child);
			} else if (grand_parent->right() == parent) {
				grand_parent->link_right(child);
			}
		}

		void balance_for_erase(node_type *parent, node_type *target, node_type *detached)
		{
			if (is_red(detached)) {
				return;
			}
			for (bool is_balanced = false; parent != &end_ && !is_balanced;
				 target = parent, parent = parent->parent()) {
				if (target == parent->left()) {
					is_balanced = balance_left_for_erase(parent);
				} else {
					is_balanced = balance_right_for_erase(parent);
				}
			}
			if (root_) {
				root_->color() = node_type::BLACK;
			}
		}

		// 左部分木の黒高さが低い状態なので(topがend_でない場合)、
		// 暗黙的に右部分木には一つ以上の黒があると期待できる
		bool balance_left_for_erase(node_type *top)
		{
			assert(top != &end_ && top->right());
			node_type *right = top->right();

			if (is_red(top->left())) {
				top->left()->color() = node_type::BLACK;
				return true;
			}
			if (is_red(top) && !has_red_child(right)) {
				top->color()   = node_type::BLACK;
				right->color() = node_type::RED;
				return true;
			}
			if (is_red(right)) {
				top                  = rotate_left(top);
				top->color()         = node_type::BLACK;
				top->left()->color() = node_type::RED;
				top                  = top->left();
				right                = top->right();
			}
			if (is_red(right->left()) && is_black(right->right())) {
				right                   = rotate_right(right);
				right->color()          = node_type::BLACK;
				right->right()->color() = node_type::RED;
			}
			if (is_red(right->right())) {
				color_type old        = top->color();
				top                   = rotate_left(top);
				top->color()          = old;
				top->left()->color()  = node_type::BLACK;
				top->right()->color() = node_type::BLACK;
				return true;
			} else {
				right->color() = node_type::RED;
				return false;
			}
		}

		bool balance_right_for_erase(node_type *top)
		{
			assert(top->left());
			node_type *left = top->left();

			if (is_red(top->right())) {
				top->right()->color() = node_type::BLACK;
				return true;
			}
			if (is_red(top) && !has_red_child(left)) {
				top->color()  = node_type::BLACK;
				left->color() = node_type::RED;
				return true;
			}
			if (is_red(left)) {
				top                   = rotate_right(top);
				top->color()          = node_type::BLACK;
				top->right()->color() = node_type::RED;
				top                   = top->right();
				left                  = top->left();
			}
			if (is_red(left->right()) && is_black(left->left())) {
				left                   = rotate_left(left);
				left->color()          = node_type::BLACK;
				left->right()->color() = node_type::RED;
			}
			if (is_red(left->left())) {
				color_type old        = top->color();
				top                   = rotate_right(top);
				top->color()          = old;
				top->left()->color()  = node_type::BLACK;
				top->right()->color() = node_type::BLACK;
				return true;
			} else {
				left->color() = node_type::RED;
				return false;
			}
		}

		void swap_node(node_type *a, node_type *b)
		{
			if (a->parent() == b) {
				swap_node_with_parent(a);
			} else if (b->parent() == a) {
				swap_node_with_parent(b);
			} else {
				node_type *a_parent = a->parent();
				node_type *a_left   = a->left();
				node_type *a_right  = a->right();

				if (b->parent()->left() == b) {
					b->parent()->link_left(a);
				} else {
					b->parent()->link_right(a);
				}
				if (a_parent->left() == a) {
					a_parent->link_left(b);
				} else {
					a_parent->link_right(b);
				}
				a->link_left(b->left());
				a->link_right(b->right());
				b->link_left(a_left);
				b->link_right(a_right);
				std::swap(a->color(), b->color());
			}
		}

		void swap_node_with_parent(node_type *child)
		{
			node_type *parent = child->parent();
			node_type *left   = child->left();
			node_type *right  = child->right();

			promote_child(parent, child);
			if (parent->left() == child) {
				child->link_left(parent);
				child->link_right(parent->right());
			} else if (parent->right() == child) {
				child->link_right(parent);
				child->link_left(parent->left());
			}
			parent->link_left(left);
			parent->link_right(right);
			std::swap(parent->color(), child->color());
		}

		bool has_red_child(node_type *n)
		{
			return is_red(n->left()) || is_red(n->right());
		}

		bool is_black(node_type *n)
		{
			return n == NULL || n->color() == node_type::BLACK;
		}

		bool is_red(node_type *n)
		{
			return !is_black(n);
		}

		node_type *rotate_left(node_type *top)
		{
			if (top == NULL || top->right() == NULL) {
				return top;
			}
			node_type *new_top  = top->right();
			node_type *new_left = top;
			node_type *isolated = new_top->left();

			promote_child(top, new_top);
			new_top->link_left(new_left);
			new_left->link_right(isolated);
			return new_top;
		}

		node_type *rotate_right(node_type *top)
		{
			if (top == NULL || top->left() == NULL) {
				return top;
			}
			node_type *new_top   = top->left();
			node_type *new_right = top;
			node_type *isolated  = new_top->right();

			promote_child(top, new_top);
			new_top->link_right(new_right);
			new_right->link_left(isolated);
			return new_top;
		}

		void delete_subtree(node_type *n)
		{
			if (n == NULL) {
				return;
			}
			node_type *left  = n->left();
			node_type *right = n->right();
			node_manager_.destroy(n);
			delete_subtree(left);
			delete_subtree(right);
		}
	};

	template <typename NodeType>
	class rb_tree_generator
	{
		typedef NodeType node_type;

	  private:
		node_type *base;

	  public:
		rb_tree_generator() : base() {}

		explicit rb_tree_generator(node_type *n) : base(n) {}

		node_type *next()
		{
			base = next(base);
			return base;
		}

		node_type *prev()
		{
			base = prev(base);
			return base;
		}

		static node_type *next(node_type *node)
		{
			if (node->right()) {
				node = node->right()->min();
			} else {
				node_type *parent = node->parent();

				while (node != parent->left()) {
					node   = parent;
					parent = parent->parent();
				}
				node = parent;
			}
			return node;
		}

		static node_type *prev(node_type *node)
		{
			if (node->left()) {
				node = node->left()->max();
			} else {
				node_type *parent = node->parent();

				while (node != parent->right()) {
					node   = parent;
					parent = parent->parent();
				}
				node = parent;
			}
			return node;
		}
	};

	template <typename>
	class rb_tree_const_iterator;

	template <typename Value>
	class rb_tree_iterator
	{
		template <typename>
		friend class rb_tree_const_iterator;

	  public:
		typedef Value                           value_type;
		typedef Value                          &reference;
		typedef Value                          *pointer;
		typedef ptrdiff_t                       difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	  private:
		typedef rb_tree_node<Value>           node_type;
		typedef rb_tree_generator<node_type>  generator;
		typedef rb_tree_iterator              iterator_type;
		typedef rb_tree_const_iterator<Value> const_iterator_type;

	  private:
		node_type *base;

	  public:
		rb_tree_iterator() : base() {}

		explicit rb_tree_iterator(node_type *n) : base(n) {}

		reference operator*() const
		{
			return base->value();
		}

		pointer operator->() const
		{
			return base->value_ptr();
		}

		iterator_type &operator++()
		{
			base = generator(base).next();
			return *this;
		}

		iterator_type operator++(int)
		{
			iterator_type &self = *this;
			iterator_type  copy = self;

			++self;
			return copy;
		}

		iterator_type &operator--()
		{
			base = generator(base).prev();
			return *this;
		}

		iterator_type operator--(int)
		{
			iterator_type &self = *this;
			iterator_type  copy = self;

			--self;
			return copy;
		}

		// 非メンバで定義すると実引数推定で除外されて
		// non_const -> const_iteratorの暗黙の変換が発生しない
		bool operator==(const const_iterator_type &rhs) const
		{
			return base == rhs.base;
		}

		bool operator!=(const const_iterator_type &rhs) const
		{
			return base != rhs.base;
		}
	};

	template <typename Value>
	class rb_tree_const_iterator
	{
		template <typename>
		friend class rb_tree_iterator;

	  public:
		typedef Value                           value_type;
		typedef const Value                    &reference;
		typedef const Value                    *pointer;
		typedef ptrdiff_t                       difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

	  private:
		typedef const rb_tree_node<Value>    node_type;
		typedef rb_tree_const_iterator       iterator_type;
		typedef rb_tree_generator<node_type> generator;
		typedef rb_tree_iterator<Value>      non_const_iterator_type;

	  private:
		node_type *base;

	  public:
		rb_tree_const_iterator() : base() {}

		explicit rb_tree_const_iterator(node_type *n) : base(n) {}

		rb_tree_const_iterator(const non_const_iterator_type &it) : base(it.base) {}

		reference operator*() const
		{
			return base->value();
		}

		pointer operator->() const
		{
			return base->value_ptr();
		}

		iterator_type &operator++()
		{
			base = generator(base).next();
			return *this;
		}

		iterator_type operator++(int)
		{
			iterator_type &self = *this;
			iterator_type  copy = self;

			++self;
			return copy;
		}

		iterator_type &operator--()
		{
			base = generator(base).prev();
			return *this;
		}

		iterator_type operator--(int)
		{
			iterator_type &self = *this;
			iterator_type  copy = self;

			--self;
			return copy;
		}

		bool operator==(const iterator_type &rhs) const
		{
			return base == rhs.base;
		}

		bool operator!=(const iterator_type &rhs) const
		{
			return base != rhs.base;
		}
	};
} // namespace ft

#endif
